cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_STANDARD 20)

project(event LANGUAGES CXX VERSION 0.0.1 DESCRIPTION "simple event lib")

add_library(${PROJECT_NAME} STATIC
        event/Event.cpp
        event/EventBroker.cpp
        event/EventListener.cpp
        event/EventDispatcher.cpp
)

target_include_directories(event PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(event PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)