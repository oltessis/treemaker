cmake_minimum_required(VERSION 3.20)

project(TreeSimulator
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# External packages
find_package(glm REQUIRED)

add_executable(TreeSimulator
    src/main.cpp
    src/meristem.cpp
    src/phyllotaxis.cpp
    src/plant_architecture.cpp
)

target_link_libraries(TreeSimulator
    PRIVATE
        glm::glm
        raylib
)

