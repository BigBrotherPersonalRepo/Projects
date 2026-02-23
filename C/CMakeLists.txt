cmake_minimum_required(VERSION 3.10)

project(Databaze)

add_executable(Databaze databaze.c databaze_funkce.c)

target_include_directories(Databaze PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )