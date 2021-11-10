gi#
# Copyright (c) 2017-2020 Cloudware S.A. All rights reserved.
#
# This file is part of named-imports-module.
#
# named-imports-module is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# named-imports-module is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with named-imports-module. If not, see <http://www.gnu.org/licenses/>.
#

THIS_DIR := $(abspath $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
ifeq (named-imports-nginx-module, $(shell basename $(THIS_DIR)))
  PACKAGER_DIR := $(abspath $(THIS_DIR)/../casper-packager)
else
  PACKAGER_DIR := $(abspath $(THIS_DIR)/../..)
endif

include $(PACKAGER_DIR)/common/c++/settings.mk

PROJECT_SRC_DIR      := $(ROOT_DIR)/named-imports-nginx-module
EXECUTABLE_NAME      := 
EXECUTABLE_MAIN_SRC  :=
LIBRARY_TYPE         := static
LIBRARY_NAME         := libnamed-imports-nginx-module.a
VERSION              := $(shell cat $(PROJECT_SRC_DIR)/versioning)
CHILD_CWD            := $(THIS_DIR)
CHILD_MAKEFILE       := $(firstword $(MAKEFILE_LIST))

# special case: this lib pulls all dependencies ( acts as a central point of configuration )
PROCESS_DEPENDENCIES := true

############################                                                                                                                                                             # BROKER VARIABLES                                                                                                                                                                       ############################

include $(PROJECT_SRC_DIR)/common.mk

############################
# COMMON REQUIRED VARIABLES
############################

CC_SRC := \
  $(NAMED_IMPORTS_MODULE_CC_SRC)

BISON_SRC := 

RAGEL_SRC := \
  $(NAMED_IMPORTS_MODULE_RL_SRC)

INCLUDE_DIRS := \
  $(NAMED_IMPORTS_MODULE_INCLUDE_DIRS)                         \
 -I ${PACKAGER_DIR}/../casper-nginx-broker/src                 \
 -I ${PACKAGER_DIR}/../casper-nginx-broker/src/nginx/src       \
 -I ${PACKAGER_DIR}/../casper-nginx-broker/src/nginx/src/core  \
 -I ${PACKAGER_DIR}/../casper-nginx-broker/src/nginx/src/event \
 -I ${PACKAGER_DIR}/../casper-nginx-broker/src/nginx/src/http  \
 -I ${PACKAGER_DIR}/../casper-nginx-broker/src/nginx/src/http/v2  \
 -I ${PACKAGER_DIR}/../casper-nginx-broker/src/nginx/src/http/modules \
 -I ${PACKAGER_DIR}/../casper-nginx-broker/src/nginx/src/os/unix \
 -I ${PACKAGER_DIR}/../casper-nginx-broker/src/nginx/objs

OBJECTS := \
  $(BISON_SRC:.yy=.o) \
  $(RAGEL_SRC:.rl=.o) \
  $(CC_SRC:.cc=.o)

include $(PACKAGER_DIR)/common/c++/common.mk

set-dependencies: casper-connectors-dep-on casper-osal-dep-on cppcodec-dep-on zlib-dep-on libbcrypt-dep-on beanstalk-client-dep-on postgresql-dep-on icu-dep-on curl-dep-on jsoncpp-dep-on cppcodec-dep-on hiredis-dep-on

# version
version:
	@echo "NGX_DIR=$(NGX_DIR) | PROJECT_SRC_DIR=$(PROJECT_SRC_DIR) | INCLUDE_DIRS=$(INCLUDE_DIRS)"
	@echo " $(LOG_COMPILING_PREFIX) - patching $(PROJECT_SRC_DIR)/src/ngx/version.h - TODO"
#	@cp -f $(PROJECT_SRC_DIR)/src/ngx/version.tpl.h $(PROJECT_SRC_DIR)/src/ngx/version.h
#	@sed -i.bak s#"x.x.xx"#$(VERSION)#g $(PROJECT_SRC_DIR)/src/ngx/version.h
#	@rm -f $(PROJECT_SRC_DIR)/src/ngx/version.h.bak

all: lib

.SECONDARY:
