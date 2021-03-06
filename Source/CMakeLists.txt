cmake_minimum_required(VERSION 2.6)
project(goap)

include_directories("${PROJECT_BINARY_DIR}")

set(EXECUTABLE_NAME "goap-client")
add_executable(${EXECUTABLE_NAME} 
    main.cpp
    SfVectorMath.cpp
    StaticEntity.cpp
    Steering.cpp
    Agent.cpp
)

# C++11
add_definitions(-std=c++11 -g)

include_directories(${CMAKE_SOURCE_DIR})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

find_package(TinyXML2)
include_directories(${TINYXML2_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${TINYXML2_LIBRARY})
