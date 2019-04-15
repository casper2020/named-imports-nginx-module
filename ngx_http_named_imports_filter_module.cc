/**
 * @file ngx_http_named_imports_filter_module.cc
 *
 * Copyright (c) 2010-2016 Neto Ranito & Seabra LDA. All rights reserved.
 *
 * This file is part of named-imports-nginx-module.
 *
 * named-imports-nginx-module is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * named-imports-nginx-module  is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with named-imports-nginx-module.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ngx_http_named_imports_filter_module.h"
#include "named_imports_context.h"

#include <sys/stat.h>

#ifdef __APPLE__
#pragma mark -
#pragma mark - Module - Forward declarations
#pragma mark -
#endif

static void*     ngx_http_named_imports_filter_module_create_loc_conf (ngx_conf_t* a_cf);
static char*     ngx_http_named_imports_filter_module_merge_loc_conf  (ngx_conf_t* a_cf, void* a_parent, void* a_child);
static ngx_int_t ngx_http_named_imports_filter_module_filter_init     (ngx_conf_t* a_cf);
static ngx_int_t ngx_http_named_imports_filter_module_body_filter     (ngx_http_request_t* a_r, ngx_chain_t* a_in);
static ngx_int_t ngx_http_named_imports_filter_module_header_filter   (ngx_http_request_t* a_r);

#ifdef __APPLE__
#pragma mark -
#pragma mark - Module definition data
#pragma mark -
#endif

/*
 * Module data
 */
static ngx_http_output_body_filter_pt    ngx_http_next_body_filter;
static ngx_http_output_header_filter_pt  ngx_http_next_header_filter;
static int                               enabled_counter = 0;

/**
 * @brief This struct defines the configuration command handlers
 */
static ngx_command_t ngx_http_named_imports_filter_module_commands[] = {
    {
        ngx_string("nginx_named_imports"),                                      /* directive name */
        NGX_HTTP_LOC_CONF | NGX_CONF_FLAG,                                      /* legal on location context and takes a boolean ("on" or "off") */
        ngx_conf_set_flag_slot,                                                 /* translates "on" or "off" to 1 or 0 */
        NGX_HTTP_LOC_CONF_OFFSET,                                               /* value saved on the location struct configuration ... */
        offsetof(ngx_http_named_imports_filter_module_loc_conf_t, enable), /* ... on the 'enable' element */
        NULL
    },
    {
        ngx_string("module_prefix"),
        NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1,
        ngx_conf_set_str_slot,
        NGX_HTTP_LOC_CONF_OFFSET,
        offsetof(ngx_http_named_imports_filter_module_loc_conf_t, module_prefix),
        NULL
    },
    ngx_null_command
};

/**
 * @brief The casper-nginx-broker 'jwt encoder' module context setup data.
 */
static ngx_http_module_t ngx_http_named_imports_filter_module_ctx = {
    NULL,                                                   /* preconfiguration              */
    ngx_http_named_imports_filter_module_filter_init,       /* postconfiguration             */
    NULL,                                                   /* create main configuration     */
    NULL,                                                   /* init main configuration       */
    NULL,                                                   /* create server configuration   */
    NULL,                                                   /* merge server configuration    */
    ngx_http_named_imports_filter_module_create_loc_conf,   /* create location configuration */
    ngx_http_named_imports_filter_module_merge_loc_conf     /* merge location configuration  */
};

/**
 * @brief The casper-nginx-broker 'jwt encoder' module setup data.
 */
ngx_module_t ngx_http_named_imports_filter_module = {
    NGX_MODULE_V1,
    &ngx_http_named_imports_filter_module_ctx,      /* module context    */
    ngx_http_named_imports_filter_module_commands,  /* module directives */
    NGX_HTTP_MODULE,                                     /* module type       */
    NULL,                                                /* init master       */
    NULL,                                                /* init module       */
    NULL,                                                /* init process      */
    NULL,                                                /* init thread       */
    NULL,                                                /* exit thread       */
    NULL,                                                /* exit process      */
    NULL,                                                /* exit master       */
    NGX_MODULE_V1_PADDING
};

#ifdef __APPLE__
#pragma mark -
#pragma mark - Configuration and initialization
#pragma mark -
#endif

/**
 * @brief Alocate the module configuration structure.
 *
 * @param a_cf
 */
static void* ngx_http_named_imports_filter_module_create_loc_conf (ngx_conf_t* a_cf)
{
    ngx_http_named_imports_filter_module_loc_conf_t* conf =
        (ngx_http_named_imports_filter_module_loc_conf_t*) ngx_pcalloc(a_cf->pool, sizeof(ngx_http_named_imports_filter_module_loc_conf_t));
    if ( NULL == conf ) {
        return NGX_CONF_ERROR;
    }

    conf->enable        = NGX_CONF_UNSET;
    conf->module_prefix = ngx_null_string;
    return conf;
}

/**
 * @brief The merge conf callback.
 *
 * @param a_cf
 * @param a_parent
 * @param a_child
 */
static char* ngx_http_named_imports_filter_module_merge_loc_conf (ngx_conf_t* a_cf, void* a_parent, void* a_child)
{
    ngx_http_named_imports_filter_module_loc_conf_t* prev = (ngx_http_named_imports_filter_module_loc_conf_t*) a_parent;
    ngx_http_named_imports_filter_module_loc_conf_t* conf = (ngx_http_named_imports_filter_module_loc_conf_t*) a_child;

    ngx_conf_merge_value    (conf->enable       , prev->enable       ,                0 ); /* 0 - disabled */
    ngx_conf_merge_str_value(conf->module_prefix, prev->module_prefix, "/node_modules/" );

    if ( 1 == conf->enable ) {
      enabled_counter++;
    }
    return (char*) NGX_CONF_OK;
}

/**
 * @brief Filter module boiler plate installation
 *
 * @param a_cf server config
 */
static ngx_int_t ngx_http_named_imports_filter_module_filter_init (ngx_conf_t* a_cf)
{
    // ... bailout if the module is not enabled ...
    if ( enabled_counter == 0 ) {
      return NGX_OK;
    }

    // ... install header and body filters ...
    ngx_http_next_header_filter = ngx_http_top_header_filter;
    ngx_http_top_header_filter  = ngx_http_named_imports_filter_module_header_filter;
    ngx_http_next_body_filter   = ngx_http_top_body_filter;
    ngx_http_top_body_filter    = ngx_http_named_imports_filter_module_body_filter;

    return NGX_OK;
}

#ifdef __APPLE__
#pragma mark - Body filter Handler
#endif


/**
 * @brief Module header filter
 *
 * @param  a_r The http request to modify
 */
static ngx_int_t ngx_http_named_imports_filter_module_header_filter (ngx_http_request_t* a_r)
{
    ngx_http_named_imports_filter_module_loc_conf_t* loc_conf;

    loc_conf = (ngx_http_named_imports_filter_module_loc_conf_t*) ngx_http_get_module_loc_conf(a_r, ngx_http_named_imports_filter_module);

    if ( 1 == loc_conf->enable ) {
        // ... create context and attach to the request ...
        NamedImportsContext* context = (NamedImportsContext*) ngx_pcalloc(a_r->pool, sizeof(NamedImportsContext));
        if ( context == NULL ) {
            return NGX_ERROR;
        }
        new (context) NamedImportsContext(a_r, (const char*) loc_conf->module_prefix.data);
        ngx_http_set_ctx(a_r, context, ngx_http_named_imports_filter_module);

        // ... clear content lenght coz we'll change the body size in the filter ...
        ngx_http_clear_content_length(a_r);
        ngx_http_clear_accept_ranges(a_r);
    }
    return ngx_http_next_header_filter(a_r);
}

/**
 * @brief Module body filter, if encryption is makes an AES pass on the data
 *
 * @param  a_r       The http request to modify
 * @param  a_in      The current buffer chain
 * @return error code or result from the next handler in the chain
 */
static ngx_int_t ngx_http_named_imports_filter_module_body_filter (ngx_http_request_t* a_r, ngx_chain_t* a_in)
{
    ngx_http_named_imports_filter_module_loc_conf_t* loc_conf;

    loc_conf = (ngx_http_named_imports_filter_module_loc_conf_t*) ngx_http_get_module_loc_conf(a_r, ngx_http_named_imports_filter_module);

    if ( 1 == loc_conf->enable ) {
        NamedImportsContext* context = (NamedImportsContext*) ngx_http_get_module_ctx(a_r, ngx_http_named_imports_filter_module);

        if ( nullptr == context ) {
            return NGX_ERROR;
        }
        for ( ngx_chain_t* chain_link = a_in; chain_link != NULL; chain_link = chain_link->next ) {
            if ( context->ParseSlice(chain_link->buf) == false ) {
                return NGX_ERROR;
            }
        }
    }
    return ngx_http_next_body_filter(a_r, a_in);
}
