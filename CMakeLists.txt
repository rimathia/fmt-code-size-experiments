cmake_minimum_required(VERSION 3.1...3.15)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(thirdpartystring
        VERSION 0.1
        DESCRIPTION "example for using fmt with a custom string"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(fmt)

add_subdirectory(benchmark)

add_subdirectory(memory_buffer)

add_subdirectory(nonstdstring)

add_subdirectory(usefmt_buf32grow2)
add_subdirectory(usefmt_buf512grow2)
add_subdirectory(usefmt_buf1024grow2)
add_subdirectory(usefmt_directpushback)
add_subdirectory(usefmt_erasedbuffer)
add_subdirectory(usefmt_erasedpushback)
add_subdirectory(usefmt_originalfmt)
add_subdirectory(usefmt_singlealloc)

add_subdirectory(microbenchmarks)
add_subdirectory(examples)

add_subdirectory(plots)