
cmake_minimum_required(VERSION 3.0)
project(cmakefirstproject)

# Set the C standard
set(CMAKE_C_STANDARD 11)

# Include subdirectories
add_subdirectory(subdir1)
add_subdirectory(subdir2)
add_subdirectory(subdir3)

# Add the main executable
add_executable(my_project main.c)

# Link the main executable with the subdirectory targets
target_link_libraries(my_project test1 test2 test3)
