cmake_minimum_required(VERSION 3.18)

project(HwChapter2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CPP_COMPILER iccarm)
# set(CMAKE_C_COMPILER /home/vislab/ccxie/miniconda3/bin/gcc)
set(CMAKE_CXX_COMPILER /home/vislab/ccxie/miniconda3/bin/g++)


set(SOURCE_FILES part1.c)

add_executable(main ${SOURCE_FILES})