cmake_minimum_required(VERSION 2.6)
project(goap)

add_definitions(-std=c++11 -g)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("Source")

set(EXECUTABLE_NAME "goap-client")
add_executable(${EXECUTABLE_NAME} 
    ../Source/main.cpp
    ../Source/Agent.cpp
    ../Source/SfVectorMath.cpp
    ../Source/Steering.cpp)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} tinyxml2)
endif()
