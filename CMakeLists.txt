cmake_minimum_required(VERSION 3.12)
project(AlianWorlds LANGUAGES CXX)

# Force C++17 or higher (SFML 3 requires C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML and its required modules
find_package(SFML COMPONENTS graphics window system audio REQUIRED)

# Define your executable and its source files
add_executable(AlianWorlds src/main.cpp)

# Include the Game headers
target_include_directories(AlianWorlds PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link SFML libraries to your target
target_link_libraries(AlianWorlds PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
