cmake_minimum_required(VERSION 3.13)

project(VoskSAPI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Vosk API path
set(VOSK_ROOT "./vosk-api-0.3.50")
include_directories(${VOSK_ROOT}/C)
link_directories(${VOSK_ROOT}/C)

add_executable(VoskSAPI main.cpp)

target_link_libraries(VoskSAPI vosk)
