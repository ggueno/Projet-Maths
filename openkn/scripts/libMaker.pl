#!/usr/bin/perl -w
#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team	  
# libMaker.pl created in 10 2008.
# Mail : biri@univ-mlv.fr					 
#													  
# This file is part of the OpenKraken.
#
# The OpenKraken-image is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-image is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.	If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/




use strict;

#getting lib name
my ($libname) = @ARGV;
if (!$libname) {
	print "usage :	libMaker.pl libname\n";
	exit(1);
}
$libname = lc($libname);
my $classname = ucfirst($libname);
my $preheader = uc($libname);

#Creating lib Directory
my $libdir = "OpenKN-".lc($libname);
mkdir $libdir or die "Unable to create $libdir";
mkdir $libdir."/src/" or die "Unable to create $libdir";
mkdir $libdir."/doc/" or die "Unable to create $libdir";
mkdir $libdir."/doc/images/" or die "Unable to create $libdir";
mkdir $libdir."/samples/" or die "Unable to create $libdir";
mkdir $libdir."/tests/" or die "Unable to create $libdir";
mkdir $libdir."/build/" or die "Unable to create $libdir";

#date 
(my $sec,my $min,my $hour,my $mday,my $mon,my $year,my $wday,my $yday,my $isdst) = localtime(time);
$year+=1900;
$mon++;

#
# Top cmake file
#

my $topcmake = q%#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team	  
# CMakeLists.txt created in @month@ @year@.
# Mail : biri@univ-mlv.fr					 
#													  
# This file is part of the OpenKraken-@libname@.
#
# The OpenKraken-@libname@ is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-@libname@ is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.	If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKraken-@libname@

#Required version
cmake_minimum_required (VERSION 2.4.0 FATAL_ERROR)

#Check for external librairies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/cmakefindfiles")
set(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES} ".so" ".a" ".lib" ".dll")
set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "lib" "")

STRING(REGEX REPLACE ":" ";" TMP_INCLUDE_PATH "$ENV{LIBRARY_PATH}")
STRING(REGEX REPLACE ":" ";" TMP_LD_LIBRARY_PATH "$ENV{LD_LIBRARY_PATH}")
STRING(REGEX REPLACE ":" ";" TMP_OPENKN_FIND_LIBRARY_PATH "$ENV{OPENKN_FIND_LIBRARY_PATH}")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/usr/lib64/" "/usr/lib/" "/usr/local/lib64" "/usr/local/lib/" "C:/windows/system32" "C:/windows/system64" "${TMP_LIBRARY_PATH}" "${TMP_LD_LIBRARY_PATH}" "${TMP_OPENKN_FIND_LIBRARY_PATH}")

STRING(REGEX REPLACE ":" ";"  TMP_INCLUDE_PATH  "$ENV{INCLUDE_PATH}")
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/usr/include/" "/usr/local/include/" "${TMP_INCLUDE_PATH}" )

#Project name
project (OpenKN-@libname@)

#Version
set (OpenKN-@libname@_MAJOR 0)
set (OpenKN-@libname@_MINOR 0)
set (OpenKN-@libname@_PATCH 0)
set (OpenKN-@libname@_VERSION ${OpenKN-@libname@_MAJOR}.${OpenKN-@libname@_MINOR}.${OpenKN-@libname@_PATCH})
message (STATUS "*** Building OpenKN-@libname@ ${OpenKN-@libname@_VERSION} ***")

#Checks
include (CheckIncludeFileCXX)

#Flags
set(CMAKE_CXX_FLAGS "-Wall -W -pedantic")
SET(CMAKE_BUILD_TYPE debug)

#Sub directories
add_subdirectory (src)
add_subdirectory (doc)


#Archives generator
set (CPACK_GENERATOR "TGZ")
set (CPACK_PACKAGE_FILE_NAME OpenKN-@libname@-${OpenKN-controller_VERSION})
set (CPACK_IGNORE_FILES "~$" ".bz2$" ".gz$")
set (CPACK_SOURCE_GENERATOR "TBZ2")
set (CPACK_SOURCE_PACKAGE_FILE_NAME libOpenKN-@libname@-${OpenKN-@libname@_VERSION})
set (CPACK_SOURCE_IGNORE_FILES "~$" ".bz2$" ".gz$")
include (CPack)

if(DEFINED ENV{OPENKN_DIR})
if(NOT "$ENV{OPENKN_DIR}" STREQUAL "")
SET(CMAKE_INSTALL_PREFIX "$ENV{OPENKN_DIR}")
endif(NOT "$ENV{OPENKN_DIR}" STREQUAL "")
endif(DEFINED ENV{OPENKN_DIR})
message (STATUS "*** Install target directory defined as ${CMAKE_INSTALL_PREFIX} ***")
%;

$topcmake =~ s/\@libname\@/$libname/g;
$topcmake =~ s/\@month\@/$mon/g;
$topcmake =~ s/\@year\@/$year/g;

open (FILE,">".$libdir."/CMakeLists.txt") or die "Unable to create : $libdir/CMakeLists.txt";
print FILE $topcmake;
close(FILE);

#
# Other top files
#
my $topfiles = q%#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team	  
# @topfile@ created in @month@ @year@.
# Mail : biri@univ-mlv.fr					 
#													  
# This file is part of the OpenKraken-@libname@.
#
# The OpenKraken-@libname@ is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-@libname@ is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.	If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/
%;
$topfiles =~ s/\@libname\@/$libname/g;
$topfiles =~ s/\@month\@/$mon/g;
$topfiles =~ s/\@year\@/$year/g;

my $topfile = $topfiles;
$topfile =~ s/\@topfile\@/AUTHORS/g;
open (FILE,">".$libdir."/AUTHORS") or die "Unable to create : $libdir/AUTHORS";
print FILE $topfile;
close(FILE);

$topfile = $topfiles;
$topfile =~ s/\@topfile\@/Changelog/g;
open (FILE,">".$libdir."/Changelog") or die "Unable to create : $libdir/Changelog";
print FILE $topfile;
close(FILE);


$topfile = $topfiles;
$topfile =~ s/\@topfile\@/INSTALL/g;
open (FILE,">".$libdir."/INSTALL") or die "Unable to create : $libdir/INSTALL";
print FILE $topfile;
close(FILE);

$topfile = $topfiles;
$topfile =~ s/\@topfile\@/README/g;
open (FILE,">".$libdir."/README") or die "Unable to create : $libdir/README";
print FILE $topfile;
close(FILE);

#
# doc cmake file
#

my $doccmake = q%#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team	  
# doc/CMakeLists.txt created in @month@ @year@.
# Mail : biri@univ-mlv.fr					 
#													  
# This file is part of the OpenKraken-@libname@.
#
# The OpenKraken-@libname@ is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-@libname@ is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.	If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

find_package (Doxygen)

if(DOXYGEN_FOUND)
  configure_file (${OpenKN-@libname@_SOURCE_DIR}/doc/Doxyfile-html.cmake ${OpenKN-@libname@_BINARY_DIR}/doc/Doxyfile-html)
  add_custom_target (html ${DOXYGEN_EXECUTABLE} ${OpenKN-@libname@_BINARY_DIR}/doc/Doxyfile-html)
endif (DOXYGEN_FOUND)
%;

$doccmake =~ s/\@libname\@/$libname/g;
$doccmake =~ s/\@month\@/$mon/g;
$doccmake =~ s/\@year\@/$year/g;

open (FILE,">".$libdir."/doc/CMakeLists.txt") or die "Unable to create : $libdir/doc/CMakeLists.txt";
print FILE $doccmake;
close(FILE);

my $doccmake2 = q%#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team	  
# doc/Doxyfile-html.cmake created in @month@ @year@.
# Mail : biri@univ-mlv.fr					 
#													  
# This file is part of the OpenKraken-@libname@.
#
# The OpenKraken-@libname@ is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-@libname@ is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.	If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#---------------------------------------------------------------------------
# Project related configuration options
#---------------------------------------------------------------------------
DOXYFILE_ENCODING	   = UTF-8
PROJECT_NAME		   = libOpenKN-@libname@
PROJECT_NUMBER		   = 
OUTPUT_DIRECTORY	   = doc-doxygen
CREATE_SUBDIRS		   = NO
OUTPUT_LANGUAGE		   = English
BRIEF_MEMBER_DESC	   = YES
REPEAT_BRIEF		   = YES
ABBREVIATE_BRIEF	   = "The $name class" \
						 "The $name widget" \
						 "The $name file" \
						 is \
						 provides \
						 specifies \
						 contains \
						 represents \
						 a \
						 an \
						 the
ALWAYS_DETAILED_SEC	   = NO
INLINE_INHERITED_MEMB  = NO
FULL_PATH_NAMES		   = YES
STRIP_FROM_PATH		   = @OpenKN-@libname@_BINARY_DIR@/doc/
STRIP_FROM_INC_PATH	   = 
SHORT_NAMES			   = NO
JAVADOC_AUTOBRIEF	   = YES
QT_AUTOBRIEF		   = YES
MULTILINE_CPP_IS_BRIEF = YES
DETAILS_AT_TOP		   = NO
INHERIT_DOCS		   = YES
SEPARATE_MEMBER_PAGES  = NO
TAB_SIZE			   = 8
ALIASES				   = 
OPTIMIZE_OUTPUT_FOR_C  = NO
OPTIMIZE_OUTPUT_JAVA   = NO
OPTIMIZE_FOR_FORTRAN   = NO
OPTIMIZE_OUTPUT_VHDL   = NO
BUILTIN_STL_SUPPORT	   = NO
CPP_CLI_SUPPORT		   = NO
SIP_SUPPORT			   = NO
IDL_PROPERTY_SUPPORT   = YES
DISTRIBUTE_GROUP_DOC   = NO
SUBGROUPING			   = YES
TYPEDEF_HIDES_STRUCT   = NO
#---------------------------------------------------------------------------
# Build related configuration options
#---------------------------------------------------------------------------
EXTRACT_ALL			   = YES
EXTRACT_PRIVATE		   = NO
EXTRACT_STATIC		   = YES
EXTRACT_LOCAL_CLASSES  = YES
EXTRACT_LOCAL_METHODS  = YES
EXTRACT_ANON_NSPACES   = NO
HIDE_UNDOC_MEMBERS	   = NO
HIDE_UNDOC_CLASSES	   = NO
HIDE_FRIEND_COMPOUNDS  = NO
HIDE_IN_BODY_DOCS	   = NO
INTERNAL_DOCS		   = NO
CASE_SENSE_NAMES	   = YES
HIDE_SCOPE_NAMES	   = NO
SHOW_INCLUDE_FILES	   = YES
INLINE_INFO			   = YES
SORT_MEMBER_DOCS	   = YES
SORT_BRIEF_DOCS		   = NO
SORT_GROUP_NAMES	   = NO
SORT_BY_SCOPE_NAME	   = NO
GENERATE_TODOLIST	   = YES
GENERATE_TESTLIST	   = YES
GENERATE_BUGLIST	   = YES
GENERATE_DEPRECATEDLIST= YES
ENABLED_SECTIONS	   = 
MAX_INITIALIZER_LINES  = 30
SHOW_USED_FILES		   = YES
SHOW_DIRECTORIES	   = NO
SHOW_FILES			   = YES
SHOW_NAMESPACES		   = YES
FILE_VERSION_FILTER	   = 
#---------------------------------------------------------------------------
# configuration options related to warning and progress messages
#---------------------------------------------------------------------------
QUIET				   = NO
WARNINGS			   = YES
WARN_IF_UNDOCUMENTED   = YES
WARN_IF_DOC_ERROR	   = YES
WARN_NO_PARAMDOC	   = NO
WARN_FORMAT			   = "$file:$line: $text"
WARN_LOGFILE		   = 
#---------------------------------------------------------------------------
# configuration options related to the input files
#---------------------------------------------------------------------------
INPUT				   = @OpenKN-@libname@_SOURCE_DIR@/src @OpenKN-@libname@_SOURCE_DIR@/doc
INPUT_ENCODING		   = UTF-8
FILE_PATTERNS		   = *.c \
						 *.cc \
						 *.cxx \
						 *.cpp \
						 *.c++ \
						 *.d \
						 *.java \
						 *.ii \
						 *.ixx \
						 *.ipp \
						 *.i++ \
						 *.inl \
						 *.h \
						 *.hh \
						 *.hxx \
						 *.hpp \
						 *.h++ \
						 *.idl \
						 *.odl \
						 *.cs \
						 *.php \
						 *.php3 \
						 *.inc \
						 *.m \
						 *.mm \
						 *.dox \
						 *.py \
						 *.f90 \
						 *.f \
						 *.vhd \
						 *.vhdl \
						 *.C \
						 *.CC \
						 *.C++ \
						 *.II \
						 *.I++ \
						 *.H \
						 *.HH \
						 *.H++ \
						 *.CS \
						 *.PHP \
						 *.PHP3 \
						 *.M \
						 *.MM \
						 *.PY \
						 *.F90 \
						 *.F \
						 *.VHD \
						 *.VHDL
RECURSIVE			   = YES
EXCLUDE				   = 
EXCLUDE_SYMLINKS	   = NO
EXCLUDE_PATTERNS	   = 
EXCLUDE_SYMBOLS		   = 
EXAMPLE_PATH		   = 
EXAMPLE_PATTERNS	   = *
EXAMPLE_RECURSIVE	   = NO
IMAGE_PATH			   = @OpenKN-controller_SOURCE_DIR@/doc/images/
INPUT_FILTER		   = 
FILTER_PATTERNS		   = 
FILTER_SOURCE_FILES	   = NO
#---------------------------------------------------------------------------
# configuration options related to source browsing
#---------------------------------------------------------------------------
SOURCE_BROWSER		   = YES
INLINE_SOURCES		   = NO
STRIP_CODE_COMMENTS	   = YES
REFERENCED_BY_RELATION = NO
REFERENCES_RELATION	   = NO
REFERENCES_LINK_SOURCE = YES
USE_HTAGS			   = NO
VERBATIM_HEADERS	   = NO
#---------------------------------------------------------------------------
# configuration options related to the alphabetical class index
#---------------------------------------------------------------------------
ALPHABETICAL_INDEX	   = NO
COLS_IN_ALPHA_INDEX	   = 5
IGNORE_PREFIX		   = 
#---------------------------------------------------------------------------
# configuration options related to the HTML output
#---------------------------------------------------------------------------
GENERATE_HTML		   = YES
HTML_OUTPUT			   = html
HTML_FILE_EXTENSION	   = .html
HTML_HEADER			   = 
HTML_FOOTER			   = 
HTML_STYLESHEET		   = 
HTML_ALIGN_MEMBERS	   = YES
GENERATE_HTMLHELP	   = NO
GENERATE_DOCSET		   = NO
DOCSET_FEEDNAME		   = "Doxygen generated docs"
DOCSET_BUNDLE_ID	   = org.doxygen.Project
HTML_DYNAMIC_SECTIONS  = NO
CHM_FILE			   = 
HHC_LOCATION		   = 
GENERATE_CHI		   = NO
CHM_INDEX_ENCODING	   = 
BINARY_TOC			   = NO
TOC_EXPAND			   = NO
DISABLE_INDEX		   = NO
ENUM_VALUES_PER_LINE   = 4
GENERATE_TREEVIEW	   = NONE
TREEVIEW_WIDTH		   = 250
FORMULA_FONTSIZE	   = 10
#---------------------------------------------------------------------------
# configuration options related to the LaTeX output
#---------------------------------------------------------------------------
GENERATE_LATEX		   = NO
LATEX_OUTPUT		   = latex
LATEX_CMD_NAME		   = latex
MAKEINDEX_CMD_NAME	   = makeindex
COMPACT_LATEX		   = NO
PAPER_TYPE			   = a4wide
EXTRA_PACKAGES		   = 
LATEX_HEADER		   = 
PDF_HYPERLINKS		   = YES
USE_PDFLATEX		   = YES
LATEX_BATCHMODE		   = NO
LATEX_HIDE_INDICES	   = NO
#---------------------------------------------------------------------------
# configuration options related to the RTF output
#---------------------------------------------------------------------------
GENERATE_RTF		   = NO
RTF_OUTPUT			   = rtf
COMPACT_RTF			   = NO
RTF_HYPERLINKS		   = NO
RTF_STYLESHEET_FILE	   = 
RTF_EXTENSIONS_FILE	   = 
#---------------------------------------------------------------------------
# configuration options related to the man page output
#---------------------------------------------------------------------------
GENERATE_MAN		   = NO
MAN_OUTPUT			   = man
MAN_EXTENSION		   = .3
MAN_LINKS			   = NO
#---------------------------------------------------------------------------
# configuration options related to the XML output
#---------------------------------------------------------------------------
GENERATE_XML		   = NO
XML_OUTPUT			   = xml
XML_SCHEMA			   = 
XML_DTD				   = 
XML_PROGRAMLISTING	   = YES
#---------------------------------------------------------------------------
# configuration options for the AutoGen Definitions output
#---------------------------------------------------------------------------
GENERATE_AUTOGEN_DEF   = NO
#---------------------------------------------------------------------------
# configuration options related to the Perl module output
#---------------------------------------------------------------------------
GENERATE_PERLMOD	   = NO
PERLMOD_LATEX		   = NO
PERLMOD_PRETTY		   = YES
PERLMOD_MAKEVAR_PREFIX = 
#---------------------------------------------------------------------------
# Configuration options related to the preprocessor	  
#---------------------------------------------------------------------------
ENABLE_PREPROCESSING   = YES
MACRO_EXPANSION		   = NO
EXPAND_ONLY_PREDEF	   = NO
SEARCH_INCLUDES		   = YES
INCLUDE_PATH		   = 
INCLUDE_FILE_PATTERNS  = 
PREDEFINED			   = 
EXPAND_AS_DEFINED	   = 
SKIP_FUNCTION_MACROS   = YES
#---------------------------------------------------------------------------
# Configuration::additions related to external references	
#---------------------------------------------------------------------------
TAGFILES			   = 
GENERATE_TAGFILE	   = 
ALLEXTERNALS		   = NO
EXTERNAL_GROUPS		   = YES
PERL_PATH			   = /usr/bin/perl
#---------------------------------------------------------------------------
# Configuration options related to the dot tool	  
#---------------------------------------------------------------------------
CLASS_DIAGRAMS		   = NO
MSCGEN_PATH			   = 
HIDE_UNDOC_RELATIONS   = NO
HAVE_DOT			   = YES
DOT_FONTNAME		   = FreeSans
DOT_FONTPATH		   = 
CLASS_GRAPH			   = YES
COLLABORATION_GRAPH	   = YES
GROUP_GRAPHS		   = YES
UML_LOOK			   = NO
TEMPLATE_RELATIONS	   = NO
INCLUDE_GRAPH		   = YES
INCLUDED_BY_GRAPH	   = YES
CALL_GRAPH			   = NO
CALLER_GRAPH		   = NO
GRAPHICAL_HIERARCHY	   = YES
DIRECTORY_GRAPH		   = YES
DOT_IMAGE_FORMAT	   = png
DOT_PATH			   = 
DOTFILE_DIRS		   = 
DOT_GRAPH_MAX_NODES	   = 50
MAX_DOT_GRAPH_DEPTH	   = 1000
DOT_TRANSPARENT		   = YES
DOT_MULTI_TARGETS	   = NO
GENERATE_LEGEND		   = YES
DOT_CLEANUP			   = YES
#---------------------------------------------------------------------------
# Configuration::additions related to the search engine	  
#---------------------------------------------------------------------------
SEARCHENGINE		   = NO
%;

$doccmake2 =~ s/\@libname\@/$libname/g;
$doccmake2 =~ s/\@month\@/$mon/g;
$doccmake2 =~ s/\@year\@/$year/g;

open (FILE,">".$libdir."/doc/Doxyfile-html.cmake") or die "Unable to create : $libdir/doc/Doxyfile-html.cmake";
print FILE $doccmake2;
close(FILE);


my $HOWTObuildcmake = q%#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team	  
# HOWTO-build created in @month@ @year@.
# Mail : biri@univ-mlv.fr					 
#													  
# This file is part of the OpenKraken-@libname@.
#
# The OpenKraken-@libname@ is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-@libname@ is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKraken-@libname@ HOWTO-build

***
Simple build
***
To start configuration and generation of makefiles, go to source directory and run:

cmake .
make
make install

The dot means that it should use current directory as a root of the build. If configuration will end without errors CMake will also generate makefiles, otherwise it will show some errors. The problems usually lie in not being able to set some variables automatically - in that case you can specify them manually. 


***
Out-of-source build - Recommended
***

This build option is good especially for developers as it allows building several different configurations with the same sources. E.g. you can build either debug / release version, use dynamic / static linking and more options. To use out-of-source build just create a directory where it will get built - nothing complicated:

cd build
cmake ..
make
make install

Another benefit is that it's easy to delete the whole build just by deleting its directory.
%;

$HOWTObuildcmake =~ s/\@libname\@/$libname/g;
$HOWTObuildcmake =~ s/\@classname\@/$classname/g;
$HOWTObuildcmake =~ s/\@month\@/$mon/g;
$HOWTObuildcmake =~ s/\@year\@/$year/g;

open (FILE,">".$libdir."/doc/HOWTO-build") or die "Unable to create : $libdir/doc/HOWTO-build";
print FILE $HOWTObuildcmake;
close(FILE);

my $HOWTOdoccmake = q%#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team	  
# HOWTO-doc created in @month@ @year@.
# Mail : biri@univ-mlv.fr					 
#													  
# This file is part of the OpenKraken-@libname@.
#
# The OpenKraken-@libname@ is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-@libname@ is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKraken-@libname@ HOWTO-doc

***
Generating documentation
***

1. First generate cmake files like you did in build
2. make html
3. the doc is generated in ./doc/doc-doxygen/html
%;

$HOWTOdoccmake =~ s/\@libname\@/$libname/g;
$HOWTOdoccmake =~ s/\@classname\@/$classname/g;
$HOWTOdoccmake =~ s/\@month\@/$mon/g;
$HOWTOdoccmake =~ s/\@year\@/$year/g;

open (FILE,">".$libdir."/doc/HOWTO-doc") or die "Unable to create : $libdir/doc/HOWTO-doc";
print FILE $HOWTOdoccmake;
close(FILE);


my $HOWTOtestcmake = q%#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team	  
# HOWTO-test created in @month@ @year@.
# Mail : biri@univ-mlv.fr					 
#													  
# This file is part of the OpenKraken-@libname@.
#
# The OpenKraken-@libname@ is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-@libname@ is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKraken-@libname@ HOWTO-test

***
Simple test
***

0. Ensure you have the whole OpenKraken directory, otherwise you won't have CxxTest.
1. compile and install libOpenKN-@libname@ (see HOWTO-build)
2. cd libOpenKN-@libname@/tests/
3. make
4. enjoy \o/
%;

$HOWTOtestcmake =~ s/\@libname\@/$libname/g;
$HOWTOtestcmake =~ s/\@classname\@/$classname/g;
$HOWTOtestcmake =~ s/\@month\@/$mon/g;
$HOWTOtestcmake =~ s/\@year\@/$year/g;

open (FILE,">".$libdir."/doc/HOWTO-test") or die "Unable to create : $libdir/doc/HOWTO-test";
print FILE $HOWTOtestcmake;
close(FILE);

my $HOWTOsamplescmake = q%#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team	  
# HOWTO-samples created in @month@ @year@.
# Mail : biri@univ-mlv.fr					 
#													  
# This file is part of the OpenKraken-@libname@.
#
# The OpenKraken-@libname@ is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-@libname@ is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKraken-@libname@ HOWTO-samples

***
Samples
***

0. Ensure you have the whole OpenKraken directory, otherwise you won't have CxxTest.
1. compile and install libOpenKN-@libname@ (see HOWTO-build)
2. cd libOpenKN-@libname@/samples/
3. make (if it exists)
4. enjoy \o/
%;

$HOWTOsamplescmake =~ s/\@libname\@/$libname/g;
$HOWTOsamplescmake =~ s/\@classname\@/$classname/g;
$HOWTOsamplescmake =~ s/\@month\@/$mon/g;
$HOWTOsamplescmake =~ s/\@year\@/$year/g;

open (FILE,">".$libdir."/doc/HOWTO-samples") or die "Unable to create : $libdir/doc/HOWTO-samples";
print FILE $HOWTOsamplescmake;
close(FILE);


#
# src cmake file
#
my $srccmake = q%#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team	  
# CMakeLists.txt created in @month@ @year@.
# Mail : biri@univ-mlv.fr					 
#													  
# This file is part of the OpenKraken-@libname@.
#
# The OpenKraken-@libname@ is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-@libname@ is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.	If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKraken-@libname@ src/


#Includes
include_directories (${OpenKN-@libname@_SOURCE_DIR}/src ${OpenKN-@libname@_BINARY_DIR}/src)


#Cpp Files
SET(CPP_FILES @classname@Exception.cpp)
add_library (OpenKN-@libname@ SHARED ${CPP_FILES})
add_library (OpenKN-@libname@-static STATIC ${CPP_FILES})

#Header Files
SET(HPP_FILES @classname@Exception.hpp)

#Install
install (TARGETS OpenKN-@libname@ DESTINATION lib)
install (TARGETS OpenKN-@libname@-static DESTINATION lib)
install (FILES ${HPP_FILES} DESTINATION include/OpenKN/@libname@)


#static and dynamic with the same name
SET_TARGET_PROPERTIES(OpenKN-@libname@-static PROPERTIES OUTPUT_NAME "OpenKN-@libname@")
SET_TARGET_PROPERTIES(OpenKN-@libname@ PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(OpenKN-@libname@-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
%;


$srccmake =~ s/\@libname\@/$libname/g;
$srccmake =~ s/\@classname\@/$classname/g;
$srccmake =~ s/\@month\@/$mon/g;
$srccmake =~ s/\@year\@/$year/g;

open (FILE,">".$libdir."/src/CMakeLists.txt") or die "Unable to create : $libdir/src/CMakeLists.txt";
print FILE $srccmake;
close(FILE);




#
# Exception header
#
my $excepheader = q%/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * @classname@Exception.hpp created in @month@ @year@.
 * Mail : biri@univ-mlv.fr					  
 *													   
 * This file is part of the OpenKraken-@libname@.
 *
 * The OpenKraken-@libname@ is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-@libname@ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_@preheadername@__@preheadername@EXCEPTION_HPP__
#define __OPENKN_@preheadername@__@preheadername@EXCEPTION_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <exception>

/*
 * Internal Includes
 */

/*
 * Namespace
 */
namespace kn{	

	/*
	 * Class definition
	 */

	/** \brief Exception thrown in case of @libname@ error
	 *
	 */
	class @classname@Exception : std::exception {

		/*
		 * Constructor & destructors
		 */		 
	public:
		/** \brief Constructor with error string and calling function name
		 *	\param err Error string
		 *	\param funcname calling function name
		 */
		@classname@Exception(const std::string& err="", const std::string& funcname="");
		/** \brief Copy Constructor
		 *	\param e Error to clone
		 */
		@classname@Exception(const @classname@Exception & e);
		/** \brief Exception destructor
		 */
		~@classname@Exception() throw() {}
	  
	private :
		/** \brief Concatenated error string 
		 */
		std::string str;
	public :
		/** \brief Getter for str
		 *	\return Concatenated error string
		 */
		inline std::string errorString() const {return str;}
		/** \brief Standard exception function overrinding
		 *	\return Concatenated error string
		 */
		virtual const char* what() const throw() {return str.c_str();}
	};

	/** \brief Operator << for @classname@Exception
	 *	\param stream output stream
	 *	\err @classname@Exception to print
	 *	\return output stream
	 */
	inline std::ostream& operator <<(std::ostream& stream, const @classname@Exception & err){
		return stream << err.errorString();
	}
   

	/*
	 * End of Namespace
	 */
}

/*
 * End of Anti-doublon
 */
#endif
%;
$excepheader =~ s/\@libname\@/$libname/g;
$excepheader =~ s/\@classname\@/$classname/g;
$excepheader =~ s/\@preheadername\@/$preheader/g;
$excepheader =~ s/\@month\@/$mon/g;
$excepheader =~ s/\@year\@/$year/g;

open (FILE,">".$libdir."/src/".$classname."Exception.hpp") or die "Unable to create : $libdir"."/src/".$classname."Exception.hpp";
print FILE $excepheader;
close(FILE);


#
# Exception CPP
#
my $excepcpp = q%/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * @classname@Exception.cpp created in @month@ @year@.
 * Mail : biri@univ-mlv.fr					  
 *													   
 * This file is part of the OpenKraken-@libname@.
 *
 * The OpenKraken-@libname@ is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-@libname@ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/


/*
 * Internal Includes
 */
#include "@classname@Exception.hpp"

/*
 * Namespace
 */
namespace kn{

	/*
	 * Functions definitions
	 */


	@classname@Exception::@classname@Exception(const std::string& err, const std::string& funcname){
	  if(funcname=="" && err=="")
		str = "Error : No message"; 
	  if(funcname!="" && err!="")
		str = "(" + funcname + ") Error : " + err;
	  if(funcname=="" && err!="")
		str = "Error : " + err;
	  if(funcname!="" && err=="") 
		str = "(" + funcname + ") Error : No message";
	}
	
	@classname@Exception::@classname@Exception(const @classname@Exception & e) : std::exception() {
	  str = e.errorString();	  
	}

  /*
   * End of Namespace
   */
}
%;

$excepcpp =~ s/\@libname\@/$libname/g;
$excepcpp =~ s/\@classname\@/$classname/g;
$excepcpp =~ s/\@month\@/$mon/g;
$excepcpp =~ s/\@year\@/$year/g;

open (FILE,">".$libdir."/src/".$classname."Exception.cpp") or die "Unable to create : $libdir"."/src/".$classname."Exception.cpp";
print FILE $excepcpp;
close(FILE);


#
# Test Makefile
#
my $testmakefile = q%#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team	  
# Makefile created in @month@ @year@.
# Mail : biri@univ-mlv.fr					 
#													  
# This file is part of the OpenKraken-@libname@.
#
# The OpenKraken-@libname@ is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-@libname@ is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.	If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#CxxTest exec
CXXTESTGEN=perl ../../tools/cxxtestgen.pl

#Test exec
TESTEXEC=testrunner


#Test suite
TESTSUITE=@classname@ExceptionTest.hpp


all : 
	@echo "Generating libOpenKN-@libname@ test suite"
	@${CXXTESTGEN}	--error-printer -o ${TESTEXEC}.cpp ${TESTSUITE}
	@echo "Compiling libOpenKN-@libname@ test suite"
	@g++ -o ${TESTEXEC}	 ${TESTEXEC}.cpp -I../../tools/ -lOpenKN-@libname@
	@echo "Running libOpenKN-@libname@ test suite"
	@./${TESTEXEC}

.PHONY: clean

clean :
	@echo "Cleaning libOpenKN-@libname@ test suite"
	@rm -Rf testrunner testrunner.cpp
%;

$testmakefile =~ s/\@libname\@/$libname/g;
$testmakefile =~ s/\@classname\@/$classname/g;
$testmakefile =~ s/\@month\@/$mon/g;
$testmakefile =~ s/\@year\@/$year/g;

open (FILE,">".$libdir."/tests/Makefile") or die "Unable to create : $libdir"."/tests/Makefile";
print FILE $testmakefile;
close(FILE);


#
# Test suite for exceptions
#
my $exceptest = q%/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * @classname@ExceptionTest.hpp created in 09 2008.
 * Mail : biri@univ-mlv.fr					  
 *													   
 * This file is part of the OpenKraken-@libname@.
 *
 * The OpenKraken-@libname@ is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-@libname@ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_@preheadername@__@preheadername@EXCEPTIONTEST_HPP__
#define __OPENKN_@preheadername@__@preheadername@EXCEPTIONTEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/@libname@/@classname@Exception.hpp>

/*
 * Class definition
 */

class @classname@ExceptionTest : public CxxTest::TestSuite {
public:
	void testConstructorWithTwoParameters( void ) {
		kn::@classname@Exception e("World!","Hello,");
		TS_ASSERT_EQUALS( e.errorString(), "(Hello,) Error : World!");
	}
  void testOperatorChev( void ) {
	  kn::@classname@Exception e("World!","Hello,");
	  std::stringstream sstr;
	  std::string strref="(Hello,) Error : World!";
	  sstr << e;
	  TS_ASSERT_EQUALS( sstr.str() , strref);
  }
};


/*
 * End of Anti-doublon
 */
#endif
%;

$exceptest =~ s/\@libname\@/$libname/g;
$exceptest =~ s/\@classname\@/$classname/g;
$exceptest =~ s/\@preheadername\@/$preheader/g;
$exceptest =~ s/\@month\@/$mon/g;
$exceptest =~ s/\@year\@/$year/g;

open (FILE,">".$libdir."/tests/".$classname."ExceptionTest.hpp") or die "Unable to create : $libdir"."/tests/".$classname."ExceptionTest.hpp";
print FILE $exceptest;
close(FILE);
