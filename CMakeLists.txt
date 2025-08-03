# CMakeList.txt : CMake project for ProjectVermillion_4_6_2025, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.15) # FetchContent is available in 3.11+
project(ProjectVermillion)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set output directory for executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(RAYLIB_VERSION 5.5)

find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED

if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
  endif()
endif()

# Our Project

# Platform-specific source
# ALL CODE BROKEN NEED TO FIGURE OUT OHOW TO MAKE IT WORK FIND DEBUG API
# if (APPLE)
    # set(PLATFORM_SRC src/Trackers/PerformanceTracking_macOS.cpp)
# elseif (WIN32)
    # set(PLATFORM_SRC src/Trackers/PerformanceTracking_Windows.cpp)
# elseif(UNIX)
    # set(PLATFORM_SRC src/Trackers/PerformanceTracking_Linux.cpp)
# endif()

# Source files
set(SOURCES
    src/main.cpp

    src/game/PlayerController.h
    src/game/PlayerController.cpp

    src/game/GameState.h
    src/game/GameState.cpp

    src/game/MenuManager.h
    src/game/MenuManager.cpp

    src/render/GameRenderer.h
    src/render/GameRenderer.cpp

    src/render/MenuRenderer.h
    src/render/MenuRenderer.cpp

    src/Trackers/PerformanceTracking.h
    src/Trackers/PerformanceTracking.cpp

    ${PLATFORM_SRC}
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    src/game
    src/render
    src/Trackers
)

# Link raylib
target_link_libraries(${PROJECT_NAME} raylib)

# Mac frameworks (if needed)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# Install (optional)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)