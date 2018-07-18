cmake_minimum_required(VERSION 2.6)
project(filebrowserseawolf)
find_package(Qt4 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DDEBUG)

include_directories(${QT_INCLUDES} 
${CMAKE_CURRENT_BINARY_DIR}
${CMAKE_CURRENT_BINARY_DIR}/Forms
${CMAKE_CURRENT_SOURCE_DIR}/Logic)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_library(stdc++fs UNKNOWN IMPORTED)
    set_property(TARGET stdc++fs PROPERTY IMPORTED_LOCATION "/usr/lib/gcc/x86_64-linux-gnu/7/libstdc++fs.a")
endif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Forms/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Logic/)

file(GLOB FileBrowserSeaWolf_SRCS_Forms ${PROJECT_SOURCE_DIR}/Forms/*.cpp)
file(GLOB FileBrowserSeaWolf_SRCS_Logic ${PROJECT_SOURCE_DIR}/Logic/*.cpp)

qt4_automoc(${FileBrowserSeaWolf_SRCS_Forms})
qt4_automoc(${FileBrowserSeaWolf_SRCS_Logic})
add_executable(filebrowserseawolf ${FileBrowserSeaWolf_SRCS_Forms} ${FileBrowserSeaWolf_SRCS_Logic} main.cpp)
target_link_libraries(filebrowserseawolf ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} stdc++fs)

install(TARGETS filebrowserseawolf RUNTIME DESTINATION bin)
#TODO: gui 
