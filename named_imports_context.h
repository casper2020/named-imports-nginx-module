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

#pragma once

extern "C" {
    #include <stddef.h>
    #include <ngx_core.h>
    #include <ngx_http.h>
}
#include <string>

class NamedImportsContext
{
    protected:
        int                 cs_;
        ngx_http_request_t* request_;
        std::string         prefix_;
        char                ext_[4];

    public:

        NamedImportsContext (ngx_http_request_t* a_request, const char* a_prefix);

        void* operator new (size_t a_size, void* a_mem) { return a_mem; }

        // Incremental parser interface
        void InitParse  ();
        bool ParseSlice (ngx_buf_t* a_buffer); //uint8_t* a_output, size_t a_out_size, const char* a_input, size_t a_in_length);

}; // end of class DataParser
