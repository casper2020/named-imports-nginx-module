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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#include "named_imports_context.h"

#pragma clang diagnostic pop

%%{
    machine fix_es6_imports;

    variable cs  cs_;

    action start_module {
        ext_[0] = ext_[1] = ext_[2] = ext_[3]= 0;
        if ( ! (fc == '.' || fc == '/') ) {
            if ( output < (last - prefix_.length()) ) {
                strcpy((char*) output, prefix_.c_str());
                output += prefix_.length();
            } else {
                return false;
            }
        }
    }

    action add_extension {
        if ( strcmp(ext_, ".js")) {
            if ( output < (last - 3) ) {
                *(output++) = '.';
                *(output++) = 'j';
                *(output++) = 's';
            } else {
                return false;
            }
        }
    }

    action cpchr {
        ext_[0] = ext_[1];
        ext_[1] = ext_[2];
        ext_[2] = fc;
        if ( output < last ) {
            *(output++) = fc;
        } else {
            return false;
        }
    }

    quote       = ( '\'' | '"' );
    ws          = [ \t];
    imports     = (alnum | '{' | '}' | ',' | '_' | '*' | '$' | space)+;
    module_name = (alnum | punct)+;
    module      = quote %start_module module_name %add_extension quote;
    main        := ( (zlen | any* [\n]) 'import' space* ( imports space* 'from' space+)? module ws* ';') $cpchr;

}%%

%% write data;

NamedImportsContext::NamedImportsContext (ngx_http_request_t* a_r, const char* a_prefix)
{
    request_ = a_r;
    prefix_  = a_prefix;
    InitParse();
}

/**
 * @brief Incremental parser initialization.
 */
void NamedImportsContext::InitParse ()
{
    ext_[0] = ext_[1] = ext_[2] = ext_[3]= 0;
    %% write init;
}

/**
 * @brief Parse a slice of the stream.
 *
 * @param a_buffer buffer with part of HTTP body
 *
 * @return The parsing result:
 *         @li true on success
 *         @li false on failure.
 */
bool NamedImportsContext::ParseSlice (ngx_buf_t* a_buffer)
{
    u_char* input         = a_buffer->pos;
    size_t  input_length  = a_buffer->last - a_buffer->pos;
    char*   p             = (char*) input;
    char*   pe            = p + input_length;
    size_t  output_length = input_length * 1.3f;
    u_char* output        = (u_char*) ngx_pcalloc(request_->pool, output_length);
    u_char* last          = output + output_length;

    if ( nullptr == output ) {
        return false;
    }
    a_buffer->pos   = output;
    a_buffer->start = output;

    %% write exec;

    a_buffer->last = output;
    a_buffer->end  = output;

    ngx_pfree(request_->pool, input);

    (void) fix_es6_imports_first_final;
    (void) fix_es6_imports_error;
    (void) fix_es6_imports_en_main;

    return true;
}
