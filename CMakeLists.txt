cmake_minimum_required(VERSION 3.28)
project(Onslaught)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libraries)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libraries)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
set(BINARY_ASSETS_DIR "${CMAKE_BINARY_DIR}/bin/assets")

# Copies the asset directory into the bin folder
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} ${BINARY_ASSETS_DIR}
    COMMENT "Copying Assets"
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(includes)
include_directories(SYSTEM libraries)
include_directories(libraries/glad/include)
include_directories(libraries/glfw-3.3.9/include/GLFW)
add_subdirectory(libraries/glfw-3.3.9)


set(SOURCE_FILES source/main.cpp
        source/game.cpp
        libraries/glad/src/glad.c
        source/state/gameState.cpp
        source/state/splashScreen.cpp
        source/state/mainMenu.cpp
        source/state/overworld.cpp
        source/rendering/renderer2D.cpp
        source/utility/resourceLoader.cpp
        source/rendering/shader.cpp
        libraries/stb_image/stb_image.cpp
        source/maps/tile.cpp
        source/rendering/orthographicCamera.cpp
        source/maps/map.cpp
        source/rendering/sprite.cpp
)

set(HEADER_FILES includes/game.h
        includes/types.h
        includes/utility/systemTimer.h
        includes/state/gameState.h
        includes/state/state.h
        includes/state/splashScreen.h
        includes/state/mainMenu.h
        includes/state/overworld.h
        includes/rendering/renderer2D.h
        includes/utility/resourceLoader.h
        includes/rendering/shader.h
        libraries/stb_image/stb_image.h
        includes/maps/tile.h
        includes/rendering/orthographicCamera.h
        includes/maps/map.h
        includes/rendering/sprite.h
)

if(WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/includes/platform/windows)

    SET(SOURCE_FILES ${SOURCE_FILES}
            source/platform/windows/windowsWindow.cpp
            source/platform/windows/systemTimer.cpp
            source/platform/opengl/textureLoader.cpp
    )

    SET(HEADER_FILES ${HEADER_FILES}
            includes/platform/windows/window.h
            includes/platform/opengl/textureLoader.h
    )

elseif(APPLE)
    include_directories(${CMAKE_SOURCE_DIR}/includes/platform/macos)

    SET(SOURCE_FILES ${SOURCE_FILES}
            source/platform/macos/macOSWindow.cpp
            source/platform/macos/systemTimer.cpp
            source/platform/opengl/textureLoader.cpp
    )

    SET(HEADER_FILES ${HEADER_FILES}
            includes/platform/macos/window.h
            includes/platform/opengl/textureLoader.h
    )

endif()

add_executable(Onslaught ${SOURCE_FILES} ${HEADER_FILES})
add_dependencies(Onslaught copy_assets)

#Stops the command prompt from appearing in windows
if(WIN32)
    set_target_properties(Onslaught PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")
endif()

target_link_libraries(Onslaught LINK_PUBLIC glfw)
install(TARGETS Onslaught RUNTIME)