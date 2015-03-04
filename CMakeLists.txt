cmake_minimum_required(VERSION 2.8.4)
project(vsmc_test)

#set( CMAKE_VERBOSE_MAKEFILE on )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(VSMC_INCLUDE_DIR ENV{VSMC_INCLUDE_DIR} CACHE PATH "Location of vSMC headers")

set(SOURCE_FILES main.cpp)
add_executable(vsmc_test ${SOURCE_FILES})

find_package(HDF5 COMPONENTS CXX)
if (HDF5_FOUND)
    include_directories(${HDF5_INCLUDE_DIRS})
    target_link_libraries(vsmc_test ${HDF5_CXX_LIBRARIES})
endif (HDF5_FOUND)

include_directories(${VSMC_INCLUDE_DIR})

