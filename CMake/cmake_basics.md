# Introduction to CMake
CMake is an open-source cross-platform build system generator that allows you to build, test, and package software projects. CMake uses platform-independent configuration files called CMakeLists.txt to define how a project should be built.

A CMakeLists.txt file consists of various commands, variables, and structures that control the build process and project configuration.

# Variables in CMake
## CMAKE_SOURCE_DIR
The root directory of the current CMake project.<br>
Example usage: <br> ${CMAKE_SOURCE_DIR}/src <br>
## CMAKE_BINARY_DIR
The directory where the generated build files reside.<br>
Example usage: <br>${CMAKE_BINARY_DIR}/bin
## CMAKE_CURRENT_SOURCE_DIR
The directory of the current CMakeLists.txt file being processed.<br>
Example usage: <br>${CMAKE_CURRENT_SOURCE_DIR}/subdir
## CMAKE_CURRENT_BINARY_DIR
The directory where the current CMakeLists.txt file generates build files.<br>
Example usage: <br>${CMAKE_CURRENT_BINARY_DIR}/build
## CMAKE_C_STANDARD
Sets the C language standard for the project.<br>
Example usage: <br>
set(CMAKE_C_STANDARD 11)
## CMAKE_CXX_STANDARD
Sets the C++ language standard for the project.<br>
Example usage: <br>
set(CMAKE_CXX_STANDARD 14)
# Common CMake Commands
## cmake_minimum_required
Sets the minimum version of CMake required to build the project.<br>
Example usage: <br>
cmake_minimum_required(VERSION 3.0)
## project
Sets the name and version of the project.<br>
Example usage: <br>
project(MyProject VERSION 1.0)
## add_executable
Creates an executable target from the given source files.<br>
Example usage: <br>
add_executable(my_executable main.c helper.c)
## add_library
Creates a library target from the given source files.<br>
Example usage: <br>
add_library(my_library STATIC file1.c file2.c)
## add_subdirectory
Includes a subdirectory in the build process.<br>
Example usage: <br>
add_subdirectory(subdir)
## target_link_libraries
Links a target with one or more libraries.<br>
Example usage: <br>
target_link_libraries(my_target my_library)
## include_directories
Specifies additional include directories for a target.<br>
Example usage: <br>
include_directories(include_dir)
# Common CMake Structures
## file(GLOB ...)
Collects a list of files matching a pattern into a variable.<br>
Example usage:<br>
file(GLOB SOURCES "*.c")<br>
file(GLOB HEADERS "*.h")<br>
## target_sources
Specifies the source files for a target.<br>
Example usage:<br>
target_sources(my_target PRIVATE source1.c source2.c)<br>
target_sources(my_target PUBLIC header1.h header2.h)<br>
## target_include_directories
Specifies the include directories for a target.<br>
Example usage:<br>
target_include_directories(my_target PUBLIC include_dir)