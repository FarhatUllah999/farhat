
# Source files
file(GLOB_RECURSE SOURCES src/*.c)
file(GLOB_RECURSE HEADERS include/*.h)

add_library(test3 ${SOURCES} ${HEADERS})
target_include_directories(test3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)