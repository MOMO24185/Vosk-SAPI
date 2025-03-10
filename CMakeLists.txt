cmake_minimum_required(VERSION 3.15)

project(VoskSAPI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Vosk API path
set(VOSK_ROOT "./libs/vosk-api-0.3.50")
include_directories(${VOSK_ROOT}/C)
link_directories(${VOSK_ROOT}/C)

find_package(WindowsSDK REQUIRED)

add_executable(VoskSAPI 
	src/main.cpp 
	src/VoskSAPI.cpp
	src/AudioCapture.cpp
)

target_link_libraries(VoskSAPI vosk winmm ole32 uuid)
