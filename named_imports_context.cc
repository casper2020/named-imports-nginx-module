
#line 1 "named_imports_context.rl"
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


#line 63 "named_imports_context.rl"



#line 36 "named_imports_context.cc"
static const char _fix_es6_imports_actions[] = {
	0, 1, 2, 2, 0, 2, 2, 1, 
	2
};

static const char _fix_es6_imports_key_offsets[] = {
	0, 1, 5, 7, 9, 11, 13, 15, 
	28, 42, 45, 50, 58, 62, 74, 87, 
	100, 113, 125, 126
};

static const char _fix_es6_imports_trans_keys[] = {
	10, 32, 105, 9, 10, 10, 109, 10, 
	112, 10, 111, 10, 114, 10, 116, 9, 
	10, 32, 34, 39, 44, 125, 48, 57, 
	65, 90, 97, 123, 9, 10, 32, 34, 
	39, 44, 102, 125, 48, 57, 65, 90, 
	97, 123, 10, 33, 126, 10, 34, 39, 
	33, 126, 9, 10, 32, 34, 39, 59, 
	33, 126, 9, 10, 32, 59, 9, 10, 
	32, 44, 102, 125, 48, 57, 65, 90, 
	97, 123, 9, 10, 32, 44, 102, 114, 
	125, 48, 57, 65, 90, 97, 123, 9, 
	10, 32, 44, 102, 111, 125, 48, 57, 
	65, 90, 97, 123, 9, 10, 32, 44, 
	102, 109, 125, 48, 57, 65, 90, 97, 
	123, 9, 10, 32, 44, 102, 125, 48, 
	57, 65, 90, 97, 123, 10, 10, 34, 
	39, 33, 126, 0
};

static const char _fix_es6_imports_single_lengths[] = {
	1, 2, 2, 2, 2, 2, 2, 7, 
	8, 1, 3, 6, 4, 6, 7, 7, 
	7, 6, 1, 3
};

static const char _fix_es6_imports_range_lengths[] = {
	0, 1, 0, 0, 0, 0, 0, 3, 
	3, 1, 1, 1, 0, 3, 3, 3, 
	3, 3, 0, 1
};

static const unsigned char _fix_es6_imports_index_offsets[] = {
	0, 2, 6, 9, 12, 15, 18, 21, 
	32, 44, 47, 52, 60, 65, 75, 86, 
	97, 108, 118, 120
};

static const char _fix_es6_imports_indicies[] = {
	1, 0, 1, 2, 1, 0, 1, 3, 
	0, 1, 4, 0, 1, 5, 0, 1, 
	6, 0, 1, 7, 0, 8, 1, 8, 
	9, 9, 10, 10, 10, 10, 10, 0, 
	8, 1, 8, 9, 9, 10, 11, 10, 
	10, 10, 10, 0, 1, 12, 0, 1, 
	14, 14, 13, 0, 15, 1, 15, 14, 
	14, 16, 13, 0, 15, 1, 15, 17, 
	0, 10, 1, 10, 10, 11, 10, 10, 
	10, 10, 0, 10, 1, 10, 10, 11, 
	18, 10, 10, 10, 10, 0, 10, 1, 
	10, 10, 11, 19, 10, 10, 10, 10, 
	0, 10, 1, 10, 10, 11, 20, 10, 
	10, 10, 10, 0, 8, 1, 8, 10, 
	11, 10, 10, 10, 10, 0, 1, 0, 
	1, 14, 14, 13, 0, 0
};

static const char _fix_es6_imports_trans_targs[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 
	8, 9, 13, 14, 10, 10, 11, 12, 
	19, 18, 15, 16, 17
};

static const char _fix_es6_imports_trans_actions[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 3, 1, 6, 1, 
	1, 1, 1, 1, 1
};

static const int fix_es6_imports_start = 0;
static const int fix_es6_imports_first_final = 18;
static const int fix_es6_imports_error = -1;

static const int fix_es6_imports_en_main = 0;


#line 66 "named_imports_context.rl"

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
    
#line 143 "named_imports_context.cc"
	{
	(  cs_) = fix_es6_imports_start;
	}

#line 84 "named_imports_context.rl"
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
    u_char* input         = a_buffer->pos;
    size_t  input_length  = a_buffer->last - a_buffer->pos;
    char*   p             = (char*) input;
    char*   pe            = p + input_length;
    char*   eof           = NULL;
    size_t  output_length = input_length * 1.3f;
    u_char* output        = (u_char*) ngx_pcalloc(request_->pool, output_length);
    u_char* last          = output + output_length;

    if ( nullptr == output ) {
        return false;
    }
    a_buffer->pos   = output;
    a_buffer->start = output;

    
#line 179 "named_imports_context.cc"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_keys = _fix_es6_imports_trans_keys + _fix_es6_imports_key_offsets[(  cs_)];
	_trans = _fix_es6_imports_index_offsets[(  cs_)];

	_klen = _fix_es6_imports_single_lengths[(  cs_)];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _fix_es6_imports_range_lengths[(  cs_)];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _fix_es6_imports_indicies[_trans];
	(  cs_) = _fix_es6_imports_trans_targs[_trans];

	if ( _fix_es6_imports_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _fix_es6_imports_actions + _fix_es6_imports_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 33 "named_imports_context.rl"
	{
      if ( ! ((*p) == '.' || (*p) == '/') ) {
        if ( output < (last - prefix_.length()) ) {
            strcpy((char*) output, prefix_.c_str());
            output += prefix_.length();
        } else {
            return false;
        }
      }
    }
	break;
	case 1:
#line 44 "named_imports_context.rl"
	{
      /* not used yet */
    }
	break;
	case 2:
#line 48 "named_imports_context.rl"
	{
      if ( output < last ) {
        *(output++) = (*p);
      } else {
        return false;
      }
    }
	break;
#line 280 "named_imports_context.cc"
		}
	}

_again:
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	}

#line 114 "named_imports_context.rl"

    a_buffer->last = output;
    a_buffer->end  = output;

    ngx_pfree(request_->pool, input);

    return true;
}