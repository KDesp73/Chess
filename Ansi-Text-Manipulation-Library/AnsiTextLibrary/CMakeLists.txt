cmake_minimum_required(VERSION 3.16)

project(AnsiTextManipulationLibrary)
set(CMAKE_CXX_STANDARD 14)

set(LIB_DIR "./Ansi-Text-Manipulation-Library/AnsiTextLibrary")

set(SOURCES
   

    ${LIB_DIR}/src/text/text.hpp
    ${LIB_DIR}/src/text/text.cpp

    ${LIB_DIR}/src/menu/menu.hpp
    ${LIB_DIR}/src/menu/menu.cpp
    ${LIB_DIR}/src/menu/menu_utils.hpp
    ${LIB_DIR}/src/menu/menu_utils.cpp
)

add_library(AnsiTextManipulationLibrary ${SOURCES})