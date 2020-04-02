# CMakeLists.txt
# Script for å generere "build-script" for prosjektet
# Erlend Omland & Marthe Engvik - Med god hjelp fra Martin Vonheim Larsen
# I forbindelse med Bacheloroppgave i Militære studer med fordypning i Elektronikk og Data

cmake_minimum_required(VERSION 3.7)

project(Utkikk9000)

find_package(CUDA REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS core highgui imgcodecs videoio)

add_library(darknet SHARED IMPORTED)

set(darknet_root /home/bachelor/darknet-master)

set_target_properties(darknet PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${darknet_root}/src;${CUDA_INCLUDE_DIRS}"
        IMPORTED_LOCATION "${darknet_root}/darknet.so"
        )

add_executable(Utkikk9000
        main.cpp
        funksjoner.h)

set_target_properties(Utkikk9000 PROPERTIES
        CXX_STANDARD_REQUIRED ON
        CXX_STANDARD 14
        )

target_compile_definitions(Utkikk9000
        PRIVATE GPU
        )

target_link_libraries(Utkikk9000
        PRIVATE darknet
        PRIVATE ${CUDA_LIBRARIES}
        PRIVATE ${OpenCV_LIBRARIES}
        )