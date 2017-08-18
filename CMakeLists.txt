cmake_minimum_required(VERSION 3.8)
project(FaddeevaM)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/Mathematica" ${CMAKE_MODULE_PATH})

# Set this to the correct path of your Mathematica installation or comment it out if it can be found automatically!
set(Mathematica_ROOT_DIR "/usr/local/Wolfram/Mathematica/11.1" CACHE STRING "Root dir of Mathematica")

find_package(Mathematica COMPONENTS WolframLibrary)

set(CMAKE_C_STANDARD 99)

message("${CMAKE_PROJECT_NAME}/LibraryResources/${Mathematica_SYSTEM_ID}")
message("${CMAKE_SOURCE_DIR}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/LibraryResources/${Mathematica_SYSTEM_ID}")
include_directories(${Mathematica_INCLUDE_DIRS})
set(SOURCE_FILES FaddeevaM/LibraryResources/Source/Faddeeva.c FaddeevaM/LibraryResources/Source/Faddeeva.h FaddeevaM/LibraryResources/Source/MMAFaddeeva.c)
add_library(FaddeevaM SHARED ${SOURCE_FILES})


