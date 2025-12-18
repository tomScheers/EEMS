cmake_minimum_required(VERSION 3.16)
project(e2e_messenger LANGUAGES CXX)

add_executable(e2e_messenger
    src/main.cpp
)

target_compile_features(e2e_messenger PRIVATE cxx_std_20)
