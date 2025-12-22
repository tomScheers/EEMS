cmake_minimum_required(VERSION 3.16)
project(e2e_messenger LANGUAGES CXX)

add_executable(e2e_messenger
    src/main.cpp
    src/user.cpp
)

target_include_directories(e2e_messenger PRIVATE lib)
target_include_directories(e2e_messenger PRIVATE src)

target_compile_features(e2e_messenger PRIVATE cxx_std_20)
