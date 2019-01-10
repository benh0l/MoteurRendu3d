cmake_minimum_required(VERSION 3.8)
project(MoteurRendu3d)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp tgaimage.cpp tgaimage.h model.cpp model.h)
add_executable(MoteurRendu3d ${SOURCE_FILES})