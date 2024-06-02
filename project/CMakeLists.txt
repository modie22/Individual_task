cmake_minimum_required(VERSION 3.11)

# Назва проекту
project(RecordFileManager)

# Встановити стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Додати виконуваний файл
add_executable(RecordFileManager main.cpp)