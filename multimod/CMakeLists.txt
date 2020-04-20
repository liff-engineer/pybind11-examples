cmake_minimum_required(VERSION 3.15)

project(pybind_add
    LANGUAGES CXX 
    VERSION 1.0
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")
endif()
if(NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")
endif()

add_subdirectory(pybind11)


add_library(mylib SHARED)

target_sources(mylib
    PRIVATE provider.hpp
    PRIVATE provider.cpp
)
set_target_properties(mylib  PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS  True
)

pybind11_add_module(provider)

target_sources(provider
    PRIVATE PyProvider.cpp 
)

target_link_libraries(provider
    PRIVATE mylib
)

pybind11_add_module(user)

target_sources(user
    PRIVATE PyUser.cpp 
)
target_link_libraries(user
    PRIVATE mylib
)