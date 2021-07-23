/**
 * @file named_import_context.h
 *
 * Copyright (c) 2010-2016 Neto Ranito & Seabra LDA. All rights reserved.
 *
 * This file is part of casper.
 *
 * casper is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * casper  is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with casper.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#include "named_imports_context.h"

#pragma clang diagnostic pop

/**
 * @brief builds the context object
 *
 * @param a_r the nginx request
 * @param a_prefix path where the modules are, defaults to node_modules
 */
NamedImportsContext::NamedImportsContext (ngx_http_request_t* a_r, const char* a_prefix)
{
    request_      = a_r;
    copying_      = false;
    cloning_      = false;
    lastStart_    = nullptr;
    module_[0]    = 0;
    comment_      = false;
    previousChar_ = 0;
    singleLine_   = false;
    
    snprintf(prefix_, sizeof(prefix_), "%s", a_prefix);
    
    // grap the location of files in the filesystem (web root)
    ngx_http_core_loc_conf_t* clcf = (ngx_http_core_loc_conf_t * ) ngx_http_get_module_loc_conf(a_r, ngx_http_core_module);
    rootlen_ = snprintf(root_, sizeof(root_), "%*.*s", (int) clcf->root.len, (int) clcf->root.len, clcf->root.data);
    
    InitParse();
}

%%{
    machine fix_es6_imports;
    variable cs  cs_;
    
    action copy {
        if ( comment_ ) {
            if ( singleLine_ ) {
                if ( fc == '\n' || fc == '\r' ) {
                    comment_ = false;
                    singleLine_ = false;
                }
            } else {
                if ( previousChar_ == '*' && fc == '/' ) {
                    comment_ = false;
                }
            }
        } else {
            if ( previousChar_ == '/' ) {
                if ( fc == '*' ) {
                    comment_ = true;
                    singleLine_ = false;
                } else if ( fc == '/' ) {
                    comment_ = true;
                    singleLine_ = true;
                }
            }
        }
        if ( cloning_ && (copying_ || comment_) ) {
            if ( output >= a_buffer->end ) {
                output = Realloc(a_buffer, output);
            }
            *(output++) = fc;
        }
        previousChar_ = fc;
    }
    
    action module_start {
        bare_      = &module_[0];
        bare_[0]   = 0;
        copying_   = false;
        lastStart_ = cloning_ ? output : (u_char*) fpc;
    }
    
    action module_end {
        *(bare_) = 0;
        const char* mod = ResolveModule();
        if ( comment_ == false && cloning_ == false && strcmp(mod, module_ ) != 0 ) {;
            output   = Realloc(a_buffer, lastStart_ != nullptr ? lastStart_ : a_buffer->pos );
            cloning_ = true;
            if ( output == nullptr ) {
                return false;
            }
        }
        
        if ( cloning_ == true ) {
            if ( comment_ == false ) {
                if ( modlen_ == 0 ) {
                    strcpy((char*) output, module_);
                    output  += strlen(module_);
                    ngx_log_error(NGX_LOG_ERR, request_->connection->log, 0, "   Bare module '%s' NOT RESOLVED\n", module_);
                } else {
                    strcpy((char*) output, mod);
                    output  += modlen_;
                    ngx_log_error(NGX_LOG_INFO, request_->connection->log, 0, "   Bare module '%s' => '%s'\n", module_, mod);
                }
            }
            copying_ = true;
        }
        lastStart_ = nullptr;
    }
    
    name          = [a-zA-Z_$][a-zA-Z0-9_$]* | '*';
    item          = name (space* 'as' space* name)?;
    items         = ('{' space* item (space* ',' space* item space* ','? space*)* space* '}') | item;
    quote         = ( '\'' | '"' );
    module_name   = (alnum | '_' | '-' | '/' | '@' | '.' )+ ${ if ( bare_ < baremax ) *(bare_++) = fc; };
    module        = (quote %module_start module_name %module_end quote);
    main        := ( (zlen | any*) ('import' | 'export') space* (items space* 'from' space*)? module space* ';') $copy;
}%%

%% write data;

/**
 * @brief Incremental parser initialization.
 */
void NamedImportsContext::InitParse ()
{
    %% write init;
}

/**
 * @brief Parse a slice of the stream.
 *
 * @param a_buffer parse and/or copy a file slice
 *
 * @return The parsing result:
 *         @li true on success
 *         @li false on failure.
 */
bool NamedImportsContext::ParseSlice (ngx_buf_t* a_buffer)
{
    u_char* input   = a_buffer->pos;
    char*   p       = (char*) input;
    char*   pe      = p + (a_buffer->last - a_buffer->pos);
    char*   eof     = pe;
    u_char* output  = nullptr;
    char*   baremax = &module_[sizeof(module_)-1];

    lastStart_  = nullptr;
    
    if ( cloning_ ) {
        output = Realloc(a_buffer, input);
        if ( output == nullptr ) {
            return false;
        }
    }
    
    %% write exec;

    if ( cloning_ ) {
        a_buffer->last = output;
        ngx_pfree(request_->pool, input);  // free the original buffer data
    } else {
        if ( lastStart_ != nullptr ) {
            a_buffer->last = lastStart_;
        }
    }
    
    (void) fix_es6_imports_first_final;
    (void) fix_es6_imports_error;
    (void) fix_es6_imports_en_main;

    return true;
}

/**
 * @brief Check if the path exists and is a plain file
 *
 * @return true it's file, false nope
 */
bool NamedImportsContext::IsFile (const char* a_name)
{
    struct stat buffer;
    
    if ( stat(a_name, &buffer) != 0 ) {
        return false;
    }
    if ( (buffer.st_mode & S_IFDIR) != 0 ) {
        return false;
    }
    return (buffer.st_mode & (S_IFREG | S_IFLNK)) != 0;
}

/**
 * @brief 1st level of module resolution
 */
const char* NamedImportsContext::ResolveModule ()
{
    // if the file does not end in JS add the extension
    modlen_ = snprintf(path_, sizeof(path_), "%s", module_);
    if ( strcmp(path_ + modlen_ - 3 , ".js") != 0 ) {
        modlen_ += 3;
        strcat(path_, ".js");
    }
    
    // ... if the path is relative we are done no need to transform ...
    if ( path_[0] == '.' || path_[0] == '/' ) {
        return path_;
    }
    
    // ... search for a file under <root>/<prefix>/<bare module> ...
    modlen_ = snprintf(path_, sizeof(path_), "%s%s%s", root_, prefix_, module_);
    if ( IsFile(path_) ) {
        modlen_ -= rootlen_;
        return path_ + rootlen_;
    }

    // ... search for a file under <root>/<prefix>/<bare module> with .js extension ...
    modlen_ = snprintf(path_, sizeof(path_), "%s%s%s.js", root_, prefix_, module_);
    if ( IsFile(path_) ) {
        modlen_ -= rootlen_;
        return path_ + rootlen_;
    }

    // ... search for a file under <root>/<prefix>/<bare module>/<bare module>.js  ...
    modlen_ = snprintf(path_, sizeof(path_), "%s%s%s/%s.js", root_, prefix_, module_, module_);
    if ( IsFile(path_) ) {
        modlen_ -= rootlen_;
        return path_ + rootlen_;
    }
    
    // ... not resolved, try the can opener on package.json
    return RetrieveFromPackageJson();
}

/**
 *  Increase the capacity of an ngxinx buffer copying the existing bytes up to the mark
 *
 *  @param a_buffer a ngxinx buffer
 *  @param a_mark the original bytes will be copied from the begining of the buffer upto this mark
 */
u_char* NamedImportsContext::Realloc (ngx_buf_t* a_buffer, u_char* a_mark)
{
    size_t length  = (u_char*) a_mark - a_buffer->pos;
    size_t olength = MAX(FILENAME_MAX * 2, (a_buffer->end - a_buffer->start) * 2);
    u_char* buffer = (u_char*) ngx_pcalloc(request_->pool, olength + 1);
    if ( buffer == nullptr ) {
        return nullptr;
    }

    memcpy(buffer, a_buffer->pos, length);
    a_buffer->start = buffer;
    a_buffer->pos   = buffer;
    a_buffer->last  = buffer + length;
    a_buffer->end   = buffer + olength;
    return buffer + length;
}

/*
 * Pseudo json parser that extracts the module and jxnext:main from the module package.json
 */

%%{
    machine get_entry_point;
    
    ws          = [ \t];
    module_name = (alnum | '_' | '-' | '/' | '@' | '.' )+ ${ if (idx < max) name[idx++] = fc; };
    module      = '"module"'      ws* ':' ws* '"' %{ name = modname; idx = 0; } module_name %{ name[idx] = 0; } '"';
    jsnext_main = '"jsnext:main"' ws* ':' ws* '"' %{ name = jsnext;  idx = 0; } module_name %{ name[idx] = 0; } '"';
    main        := any* (module | jsnext_main ) any*;

}%%

%%write data nofinal;

/**
 * @Brief opens the directory package.json to lookup the module entry point
 *
 * @returns name of javascript entry point or an empty string if none is found
 */
const char* NamedImportsContext::RetrieveFromPackageJson ()
{
    modlen_ = snprintf(path_, sizeof(path_), "%s%s%s/package.json", root_, prefix_, module_);
    if ( IsFile(path_) == false ) {
        modlen_ = 0;
        return "";
    }
    int fd = open(path_, O_RDONLY);
    if ( -1 == fd ) {
        modlen_ = 0;
        return "";
    }
    struct stat s;
    if ( 0 != fstat (fd, &s) ) {
        modlen_ = 0;
        return "";
    }
    size_t size = s.st_size;
    char*  json = (char *) mmap (0, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if ( MAP_FAILED == json ) {
        return "";
    }
    // ... setup ragel variables ..
    int          cs;
    char const*  p    = json;
    char const*  pe   = json + size;
    const size_t max  = 200;
    int          idx  = 0;
    char*        name = nullptr;
    char         modname[max+1];
    char         jsnext[max+1];

    modname[0] = 0;
    jsnext[0]  = 0;
    
    %% write init;
    %% write exec;

    munmap(json, size);
    close(fd);
    
    if ( p == pe ) {
        if ( modname[0] ) {
            modlen_ = snprintf(path_, sizeof(path_), "%s%s/%s", prefix_, module_, modname);
            return path_;
        }
        if ( jsnext[0] ) {
            modlen_ = snprintf(path_, sizeof(path_), "%s%s/%s", prefix_, module_, jsnext);
            return path_;
        }
    }

    (void) get_entry_point_error;
    (void) get_entry_point_en_main;
    modlen_ = 0;
    return "";
}
