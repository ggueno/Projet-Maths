
include(LibFindMacros)

set(LIBNAME OpenKN-math)

if(NOT ${LIBNAME}_FIND_QUIETLY)
message(STATUS "Looking for ${LIBNAME}...")
endif(NOT ${LIBNAME}_FIND_QUIETLY)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(${LIBNAME}_PKGCONF ${LIBNAME})

# Include dir
find_path(${LIBNAME}_INCLUDE_DIR NAMES OpenKN/math/Vector.hpp PATHS ${${LIBNAME}_PKGCONF_INCLUDE_DIRS} ${CMAKE_INCLUDE_PATH})

# Finally the library itself
find_library(${LIBNAME}_LIBRARY NAMES ${LIBNAME} PATHS ${${LIBNAME}_PKGCONF_LIBRARY_DIRS} ${CMAKE_LIBRARY_PATH})

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(${LIBNAME}_PROCESS_INCLUDES ${LIBNAME}_INCLUDE_DIR)
set(${LIBNAME}_PROCESS_LIBS ${LIBNAME}_LIBRARY)
libfind_process(${LIBNAME})

message(STATUS "${${LIBNAME}_VERSION_MAJOR}...")

if (${LIBNAME}_INCLUDE_DIRS AND ${LIBNAME}_LIBRARIES)
set(LIBS ${LIBS} ${${LIBNAME}_LIBRARIES})
include_directories(${${LIBNAME}_INCLUDE_DIRS})
else (${LIBNAME}_INCLUDE_DIRS AND ${LIBNAME}_LIBRARIES)
endif (${LIBNAME}_INCLUDE_DIRS AND ${LIBNAME}_LIBRARIES)
