#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team
# doc/CMakeLists.txt created in 11 2008.
# Mail : biri@univ-mlv.fr
#
# This file is part of the OpenKraken-math.
#
# The OpenKraken-math is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-math is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

find_package(Doxygen)

if(DOXYGEN_FOUND)
  configure_file (${OpenKN-math_SOURCE_DIR}/doc/Doxyfile-html.cmake ${OpenKN-math_BINARY_DIR}/doc/Doxyfile-html)
  add_custom_target (html ${DOXYGEN_EXECUTABLE} ${OpenKN-math_BINARY_DIR}/doc/Doxyfile-html)
endif (DOXYGEN_FOUND)
