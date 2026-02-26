cmake_minimum_required(VERSION 3.30)
project(RGR2Semestr)

set(CMAKE_CXX_STANDARD 20)

add_executable(RGR2Semestr main.cpp
        password.cpp
        password.h
        table.cpp
        table.h
        tarabar.cpp
        tarabar.h
        PolybiusCipher.cpp
        PolybiusCipher.h)
