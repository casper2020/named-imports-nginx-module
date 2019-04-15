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

#include "named_imports_context.h"

%%{
    machine fix_es6_imports;

    variable cs  cs_;

    action start_module {
      if ( ! (fc == '.' || fc == '/') ) {
        strcpy((char*) output, prefix_.c_str());
        output += prefix_.length();
      }
    }

    action end_module {
      /* not used yet */
    }

    action cpchr {
      *(output++) = fc;
    }

    quote       = ( '\'' | '"' );
    ws          = [ \t];
    imports     = (alnum | '{' | '}' | ',' | ws)+;
    module_name = (alnum | punct)+;
    module      = quote %start_module module_name %end_module quote;
    main        := (any* [\n] ws* 'import' ws* ( imports ws* 'from' ws+)? module ws* ';') $cpchr;

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
 *
 * @return The initialization result:
 *         @li True on success
 *         @li False on failure.
 */
void NamedImportsContext::InitParse ()
{
    %% write init;
}

/**
 * @brief Parse a slice of the stream.
 *
 * @param a_json The JSON string to be parsed.
 * @param a_length   The size of the JSON string.
 *
 * @return The parsing result:
 *         @li True on success
 *         @li False on failure.
 */
bool NamedImportsContext::ParseSlice (ngx_buf_t* a_buffer)
{
    u_char* input        = a_buffer->pos;
    size_t  input_length = a_buffer->last - a_buffer->pos;
    char*   p            = (char*) input;
    char*   pe           = p + input_length;
    char*   eof          = NULL;
    u_char* output       = (u_char*) ngx_pcalloc(request_->pool, input_length * 2);

    printf("  Input len %d\n", input_length);
    if ( nullptr == output ) {
        return false;
    }
    a_buffer->pos   = output;
    a_buffer->start = output;

    //output_   = a_output;
    //out_size_ = a_out_size;

    %% write exec;

    a_buffer->last = output;
    a_buffer->end  = output;

    printf("  Output %d\n", output - a_buffer->pos);

    return true;
}