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
#include <sstream>

class NamedImportsContext
{
    protected: // data
    
        int                 cs_;                    //!< Ragel state variable
        ngx_http_request_t* request_;               //!< The nginx request we are serving
        char                prefix_[FILENAME_MAX];  //!< holds the bare module name
        bool                copying_;               //!< true when copying input to output one character at a time
        bool                cloning_;               //!< true when the input chain is cloned to allow changes
        char*               bare_;                  //!<  used to collect bare module name char by char across chains
        char                module_[FILENAME_MAX];  //!< holds the bare module name
        size_t              rootlen_;               //!< lenght of the root on the file system
        char                root_[FILENAME_MAX];    //!< holds the path of  the web root on the lenght of the root on the file system
        size_t              modlen_;                //!< lenght of the resolved module
        char                path_[FILENAME_MAX];    //!< buffer to build path names when looking up files on disk
        u_char*             lastStart_;             //!<

    protected: // variables for the old-school comment parser

        bool  comment_;       //!< true when inside a comment
        char  previousChar_;  //!< preceeding char
        bool  singleLine_;    //!< true when scanning a single line comment
    
    public: // methods

        NamedImportsContext (ngx_http_request_t* a_request, const char* a_prefix);

        void* operator new (size_t a_size, void* a_mem) { return a_mem; }

        // Incremental parser interface
        void        InitParse               ();
        bool        ParseSlice              (ngx_buf_t* a_buffer);

    protected: // methods
    
        const char* ResolveModule            ();
        const char* RetrieveFromPackageJson  ();
        bool        IsFile                   (const char* a_name);
        u_char*     Realloc                  (ngx_buf_t* a_buffer, u_char* a_marker);

    
}; // end of class NamedImportsContext
