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

add_library(nonstdstring nonstdstring.cpp include/nonstdstring/nonstdstring.h)
target_include_directories(nonstdstring PUBLIC include)
target_link_libraries(nonstdstring PUBLIC fmt)

add_library(runtimecheck STATIC runtimecheck.cpp)
target_link_libraries(runtimecheck PUBLIC nonstdstring)

add_executable(useruntimecheck useruntimecheck.cpp)
target_link_libraries(useruntimecheck runtimecheck)

add_library(compiletimecheck STATIC compiletimecheck.cpp)
target_link_libraries(compiletimecheck PUBLIC nonstdstring)

add_executable(usecompiletimecheck usecompiletimecheck.cpp)
target_link_libraries(usecompiletimecheck compiletimecheck)

add_executable(usefmt usefmt.cpp)
target_link_libraries(usefmt nonstdstring)

add_executable(useprintf useprintf.cpp)
target_link_libraries(useprintf nonstdstring)