# cvRetina CMake config file
#
# This file sets the following variables:
# cvRetina_FOUND - Always TRUE.
# cvRetina_INCLUDE_DIRS - Directories containing the cvRetina include files.
# cvRetina_IDL_DIRS - Directories containing the cvRetina IDL files.
# cvRetina_LIBRARIES - Libraries needed to use cvRetina.
# cvRetina_DEFINITIONS - Compiler flags for cvRetina.
# cvRetina_VERSION - The version of cvRetina found.
# cvRetina_VERSION_MAJOR - The major version of cvRetina found.
# cvRetina_VERSION_MINOR - The minor version of cvRetina found.
# cvRetina_VERSION_REVISION - The revision version of cvRetina found.
# cvRetina_VERSION_CANDIDATE - The candidate version of cvRetina found.

message(STATUS "Found cvRetina-1.0.0")
set(cvRetina_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(cvRetina_INCLUDE_DIRS
#    "/usr/local/include/cvretina-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(cvRetina_IDL_DIRS
#    "/usr/local/include/cvretina-1/idl")
set(cvRetina_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(cvRetina_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(cvRetina_LIBRARIES
        "/usr/local/components/lib/libcvretina.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(cvRetina_LIBRARIES
        "/usr/local/components/lib/libcvretina.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(cvRetina_DEFINITIONS ${<dependency>_DEFINITIONS})

set(cvRetina_VERSION 1.0.0)
set(cvRetina_VERSION_MAJOR 1)
set(cvRetina_VERSION_MINOR 0)
set(cvRetina_VERSION_REVISION 0)
set(cvRetina_VERSION_CANDIDATE )

