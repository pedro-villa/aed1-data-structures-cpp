cmake_minimum_required(VERSION 3.16)
project(aed1_data_structures_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /O2)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O3)
endif()

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/01-dictionary-trie-hashtable-cpp/src")

add_executable(diccionario_aed1
    "${SRC_DIR}/004final.cpp"
    "${SRC_DIR}/diccionario.cpp"
    "${SRC_DIR}/arbolTrie.cpp"
    "${SRC_DIR}/TablaHash.cpp"
)

target_include_directories(diccionario_aed1 PRIVATE "${SRC_DIR}")
