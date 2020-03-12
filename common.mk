#
# Copyright (c) 2010-2016 Neto Ranito & Seabra LDA. All rights reserved.
#
# This file is part of named-imports-nginx-module.
#
# named-imports-nginx-module is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# named-imports-nginx-module is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with named-imports-nginx-module.  If not, see <http://www.gnu.org/licenses/>.
#

THIS_DIR                          := $(abspath $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
NAMED_IMPORTS_MODULE_DIR          := $(THIS_DIR)
NAMED_IMPORTS_MODULE_INCLUDE_DIRS := -I $(NAMED_IMPORTS_MODULE_DIR)/src

### MODULE ###

NAMED_IMPORTS_MODULE_CC_SRC :=
NAMED_IMPORTS_MODULE_RL_SRC := \
	$(NAMED_IMPORTS_MODULE_DIR)/named_imports_context.rl

.SECONDARY:
