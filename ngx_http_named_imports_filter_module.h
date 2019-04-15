/**
 * @file ngx_http_named_imports_filter_module.h
 *
 * Copyright (c) 2019 Cloudware S.A. All rights reserved.
 *
 * This file is part of nginx_named_imports.
 *
 * nginx_named_imports is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * nginx_named_imports  is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with nginx_named_imports.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#ifndef CLOUDWARE_NGX_HTTP_NAMED_IMPORTS_FILTER_MODULE_H_
#define CLOUDWARE_NGX_HTTP_NAMED_IMPORTS_FILTER_MODULE_H_

extern "C" {
    #include <ngx_config.h>
    #include <ngx_core.h>
    #include <ngx_http.h>
    #include <ngx_errno.h>
}

#ifdef __APPLE__
#pragma mark - module loc_conf_t
#endif

/**
 * @brief Module configuration structure, applicable to a location scope
 */
typedef struct {
    ngx_flag_t enable;          //!< flag that enables the module
    ngx_str_t  module_prefix;   //!< Path that is pre-pended to a named import
} ngx_http_named_imports_filter_module_loc_conf_t;

extern ngx_module_t ngx_http_named_imports_filter_module;

#endif // CLOUDWARE_NGX_HTTP_NAMED_IMPORTS_FILTER_MODULE_H_