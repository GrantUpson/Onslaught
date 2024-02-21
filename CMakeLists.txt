cmake_minimum_required(VERSION 3.28)
project(Onslaught)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libraries)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libraries)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(includes)
include_directories(libraries)
include_directories(libraries/glad/include)
include_directories(libraries/glfw-3.3.9/include/GLFW)
add_subdirectory(libraries/glfw-3.3.9)

set(SOURCE_FILES source/main.cpp
        source/game.cpp
)

set(HEADER_FILES includes/game.h

)

if(WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/includes/platform/windows)

    SET(SOURCE_FILES ${SOURCE_FILES}
            source/platform/windows/windowsWindow.cpp
    )

    SET(HEADER_FILES ${HEADER_FILES}
            includes/platform/windows/window.h
    )

elseif(APPLE)
    include_directories(${CMAKE_SOURCE_DIR}/includes/platform/macos)

    SET(SOURCE_FILES ${SOURCE_FILES}
            source/platform/macos/macOSWindow.cpp

    )

    SET(HEADER_FILES ${HEADER_FILES}
            includes/platform/macos/window.h
    )

endif()

add_executable(Onslaught ${SOURCE_FILES} ${HEADER_FILES})

#Stops the command prompt from appearing in windows
if(WIN32)
    set_target_properties(Onslaught PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")
endif()

target_link_libraries(Onslaught LINK_PUBLIC glfw)
install(TARGETS Onslaught RUNTIME)