
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


#line 75 "named_imports_context.rl"



#line 36 "named_imports_context.cc"
static const char _fix_es6_imports_actions[] = {
	0, 1, 2, 2, 0, 2, 2, 1, 
	2
};

static const short _fix_es6_imports_key_offsets[] = {
	0, 2, 3, 5, 7, 9, 11, 13, 
	30, 48, 67, 70, 75, 83, 87, 103, 
	120, 137, 154, 171, 187, 204, 221, 238, 
	255, 272, 273
};

static const char _fix_es6_imports_trans_keys[] = {
	10, 105, 10, 10, 109, 10, 112, 10, 
	111, 10, 114, 10, 116, 10, 32, 34, 
	36, 39, 42, 44, 95, 125, 9, 13, 
	48, 57, 65, 90, 97, 123, 10, 32, 
	34, 36, 39, 42, 44, 95, 102, 125, 
	9, 13, 48, 57, 65, 90, 97, 123, 
	10, 32, 34, 36, 39, 42, 44, 95, 
	102, 105, 125, 9, 13, 48, 57, 65, 
	90, 97, 123, 10, 33, 126, 10, 34, 
	39, 33, 126, 9, 10, 32, 34, 39, 
	59, 33, 126, 9, 10, 32, 59, 10, 
	32, 36, 42, 44, 95, 102, 125, 9, 
	13, 48, 57, 65, 90, 97, 123, 10, 
	32, 36, 42, 44, 95, 102, 105, 125, 
	9, 13, 48, 57, 65, 90, 97, 123, 
	10, 32, 36, 42, 44, 95, 102, 114, 
	125, 9, 13, 48, 57, 65, 90, 97, 
	123, 10, 32, 36, 42, 44, 95, 102, 
	111, 125, 9, 13, 48, 57, 65, 90, 
	97, 123, 10, 32, 36, 42, 44, 95, 
	102, 109, 125, 9, 13, 48, 57, 65, 
	90, 97, 123, 10, 32, 36, 42, 44, 
	95, 102, 125, 9, 13, 48, 57, 65, 
	90, 97, 123, 10, 32, 36, 42, 44, 
	95, 102, 109, 125, 9, 13, 48, 57, 
	65, 90, 97, 123, 10, 32, 36, 42, 
	44, 95, 102, 112, 125, 9, 13, 48, 
	57, 65, 90, 97, 123, 10, 32, 36, 
	42, 44, 95, 102, 111, 125, 9, 13, 
	48, 57, 65, 90, 97, 123, 10, 32, 
	36, 42, 44, 95, 102, 114, 125, 9, 
	13, 48, 57, 65, 90, 97, 123, 10, 
	32, 36, 42, 44, 95, 102, 116, 125, 
	9, 13, 48, 57, 65, 90, 97, 123, 
	10, 10, 34, 39, 33, 126, 0
};

static const char _fix_es6_imports_single_lengths[] = {
	2, 1, 2, 2, 2, 2, 2, 9, 
	10, 11, 1, 3, 6, 4, 8, 9, 
	9, 9, 9, 8, 9, 9, 9, 9, 
	9, 1, 3
};

static const char _fix_es6_imports_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 4, 
	4, 4, 1, 1, 1, 0, 4, 4, 
	4, 4, 4, 4, 4, 4, 4, 4, 
	4, 0, 1
};

static const short _fix_es6_imports_index_offsets[] = {
	0, 3, 5, 8, 11, 14, 17, 20, 
	34, 49, 65, 68, 73, 81, 86, 99, 
	113, 127, 141, 155, 168, 182, 196, 210, 
	224, 238, 240
};

static const char _fix_es6_imports_indicies[] = {
	1, 2, 0, 1, 0, 1, 3, 0, 
	1, 4, 0, 1, 5, 0, 1, 6, 
	0, 1, 7, 0, 9, 8, 10, 11, 
	10, 11, 11, 11, 11, 8, 11, 11, 
	11, 0, 9, 8, 10, 11, 10, 11, 
	11, 11, 12, 11, 8, 11, 11, 11, 
	0, 9, 8, 10, 11, 10, 11, 11, 
	11, 12, 13, 11, 8, 11, 11, 11, 
	0, 1, 14, 0, 1, 16, 16, 15, 
	0, 17, 1, 17, 16, 16, 18, 15, 
	0, 17, 1, 17, 19, 0, 20, 11, 
	11, 11, 11, 11, 12, 11, 11, 11, 
	11, 11, 0, 20, 11, 11, 11, 11, 
	11, 12, 13, 11, 11, 11, 11, 11, 
	0, 20, 11, 11, 11, 11, 11, 12, 
	21, 11, 11, 11, 11, 11, 0, 20, 
	11, 11, 11, 11, 11, 12, 22, 11, 
	11, 11, 11, 11, 0, 20, 11, 11, 
	11, 11, 11, 12, 23, 11, 11, 11, 
	11, 11, 0, 9, 8, 11, 11, 11, 
	11, 12, 11, 8, 11, 11, 11, 0, 
	20, 11, 11, 11, 11, 11, 12, 24, 
	11, 11, 11, 11, 11, 0, 20, 11, 
	11, 11, 11, 11, 12, 25, 11, 11, 
	11, 11, 11, 0, 20, 11, 11, 11, 
	11, 11, 12, 26, 11, 11, 11, 11, 
	11, 0, 20, 11, 11, 11, 11, 11, 
	12, 27, 11, 11, 11, 11, 11, 0, 
	20, 11, 11, 11, 11, 11, 12, 8, 
	11, 11, 11, 11, 11, 0, 1, 0, 
	1, 16, 16, 15, 0, 0
};

static const char _fix_es6_imports_trans_targs[] = {
	1, 0, 2, 3, 4, 5, 6, 7, 
	8, 9, 10, 14, 16, 20, 11, 11, 
	12, 13, 26, 25, 15, 17, 18, 19, 
	21, 22, 23, 24
};

static const char _fix_es6_imports_trans_actions[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 3, 1, 
	6, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1
};

static const int fix_es6_imports_start = 0;
static const int fix_es6_imports_first_final = 25;
static const int fix_es6_imports_error = -1;

static const int fix_es6_imports_en_main = 0;


#line 78 "named_imports_context.rl"

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
    
#line 179 "named_imports_context.cc"
	{
	(  cs_) = fix_es6_imports_start;
	}

#line 93 "named_imports_context.rl"
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

    
#line 215 "named_imports_context.cc"
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
        ext_[0] = ext_[1] = ext_[2] = ext_[3]= 0;
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
#line 45 "named_imports_context.rl"
	{
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
	break;
	case 2:
#line 57 "named_imports_context.rl"
	{
        ext_[0] = ext_[1];
        ext_[1] = ext_[2];
        ext_[2] = (*p);
        if ( output < last ) {
            *(output++) = (*p);
        } else {
            return false;
        }
    }
	break;
#line 328 "named_imports_context.cc"
		}
	}

_again:
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	}

#line 123 "named_imports_context.rl"

    a_buffer->last = output;
    a_buffer->end  = output;

    ngx_pfree(request_->pool, input);

    return true;
}