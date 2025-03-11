cmake_minimum_required(VERSION 3.15)

project(VoskSAPI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/libs/vosk-win64-0.3.45
)

# Set paths to Vosk SDK
set(VOSK_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/vosk-win64-0.3.45)
set(VOSK_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/vosk-win64-0.3.45)

# Include directories
include_directories(${VOSK_INCLUDE_DIR})

# Link Vosk library
link_directories(${VOSK_LIB_DIR})

# Detect and set the Windows SDK version
if (CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION)
	set(WINDOWS_SDK_VERSION ${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION})
else()
	set(WINDOWS_SDK_VERSION "10.0.22621.0") #Default fallback version
endif()

include_directories(
	"C:/Program Files (x86)/Windows Kits/10/Include/${WINDOWS_SDK_VERSION}/um"
	"C:/Program Files (x86)/Windows Kits/10/Include/${WINDOWS_SDK_VERSION}/shared"
	"C:/Program Files (x86)/Windows Kits/10/Include/${WINDOWS_SDK_VERSION}/ucrt"
)

link_directories(
	"C:/Program Files (x86)/Windows Kits/10/Lib/${WINDOWS_SDK_VERSION}/um/x64"
)

add_executable(VoskSAPI 
	src/main.cpp 
	src/VoskSAPI.cpp
	src/AudioCapture.cpp
)

target_link_libraries(VoskSAPI libvosk.lib winmm user32.lib kernel32.lib ole32.lib oleaut32.lib uuid.lib)

# Copy libvosk.dll to the build output directory after compilation
add_custom_command(TARGET VoskSAPI POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${VOSK_LIB_DIR}/libvosk.dll"
		$<TARGET_FILE_DIR:VoskSAPI>
)
