################################################################################
# Copyright (c) 2014 Krell Institute. All Rights Reserved.
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; either version 2 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc., 59 Temple
# Place, Suite 330, Boston, MA  02111-1307  USA
################################################################################

include(FindPackageHandleStandardArgs)
INCLUDE (CheckSymbolExists)
INCLUDE (CheckFunctionExists)

SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a")


find_path(OpenMPI_INCLUDE_DIR
    NAMES mpi.h
    PATHS /usr /usr/local
    HINTS $ENV{OPENMPI_ROOT}
    HINTS ${OPENMPI_ROOT}
    PATH_SUFFIXES include include/openmpi
    NO_DEFAULT_PATH
    )

find_library(OpenMPI_LIBRARY_SHARED NAMES mpi
    HINTS $ENV{OPENMPI_ROOT}
    HINTS ${OPENMPI_ROOT}
    PATHS /usr /usr/local
    PATH_SUFFIXES lib lib64
    NO_DEFAULT_PATH
    )

find_package_handle_standard_args(
    OpenMPI DEFAULT_MSG
    OpenMPI_LIBRARY_SHARED
    OpenMPI_INCLUDE_DIR
    )

set(OpenMPI_SHARED_LIBRARIES ${OpenMPI_LIBRARY_SHARED})
set(OpenMPI_INCLUDE_DIRS ${OpenMPI_INCLUDE_DIR})
set(OpenMPI_DEFINES "")

message(STATUS "OpenMPI OpenMPI_SHARED_LIBRARIES: " ${OpenMPI_SHARED_LIBRARIES})
message(STATUS "OpenMPI OpenMPI_INCLUDE_DIR: " ${OpenMPI_INCLUDE_DIR})
message(STATUS "OpenMPI OpenMPI_FOUND: " ${OPENMPI_FOUND})
set(OpenMPI_DEFINES "-DHAVE_OPENMPI=${OPENMPI_FOUND}")

GET_FILENAME_COMPONENT(OpenMPI_LIB_DIR ${OpenMPI_LIBRARY_SHARED} PATH )

message(STATUS "OpenMPI OpenMPI_LIB_DIR: " ${OpenMPI_LIB_DIR})


mark_as_advanced(
            OpenMPI_LIBRARY_SHARED 
            OpenMPI_INCLUDE_DIR
            OpenMPI_LIB_DIR
            )
