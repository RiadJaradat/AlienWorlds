cmake_minimum_required(VERSION 3.12)
project(AlienWorlds LANGUAGES CXX)

# Force C++17 or higher (SFML 3 requires C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML and its required modules
find_package(SFML COMPONENTS graphics window system audio REQUIRED)
# 1. Find the OpenGL package
find_package(OpenGL REQUIRED)

# Define your executable and its source files
add_executable(AlienWorlds src/main.cpp)

# Include the Game headers
target_include_directories(AlienWorlds PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 2. Link OpenGL to your main project executable
# Replace 'AlienWorlds' with the actual name used in your add_executable() command
target_link_libraries(AlienWorlds PRIVATE 
    ${OPENGL_LIBRARIES}
    imgui_lib
)

# Add this module to handle exports
include(GenerateExportHeader)

# Define the ImGui source files
set(IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui-SFML.cpp # The binding file
)

# Create a library target for ImGui
add_library(imgui_lib ${IMGUI_SOURCES})

# Tell CMake where to look for headers
target_include_directories(imgui_lib PUBLIC 
    imgui/
)

# Link ImGui to SFML (make sure your main project also links SFML)
target_link_libraries(imgui_lib PUBLIC sfml-graphics sfml-window sfml-system)

# Link ImGui to your main game executable
# Replace 'AlienWorlds' with your actual target name
target_link_libraries(AlienWorlds PRIVATE imgui_lib)

# Link SFML libraries to your target
target_link_libraries(AlienWorlds PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
