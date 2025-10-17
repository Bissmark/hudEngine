cmake_minimum_required(VERSION 3.16)
project(GameEngine)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
message(STATUS "OpenGL found: ${OPENGL_FOUND}")
message(STATUS "OpenGL libraries: ${OPENGL_LIBRARIES}")

find_package(GLEW REQUIRED)
message(STATUS "GLEW found: ${GLEW_FOUND}")
message(STATUS "GLEW libraries: ${GLEW_LIBRARIES}")
message(STATUS "GLEW include dirs: ${GLEW_INCLUDE_DIRS}")

find_package(glm CONFIG REQUIRED)

set(SDL3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/SDL3")
set(SDL3_LIBRARY "${CMAKE_SOURCE_DIR}/SDL3/lib/x86/SDL3.lib")

find_package(SDL3 REQUIRED)
message(STATUS "SDL3 found: ${SDL3_FOUND}")
message(STATUS "SDL3 libraries: ${SDL3_LIBRARIES}")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/window.cpp
    src/camera.cpp
    src/texture.cpp
    src/mesh.cpp
    src/editor.cpp
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_impl_sdl3.cpp
    src/imgui/imgui_impl_sdlrenderer3.cpp
    src/imgui/imgui_impl_opengl3.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_demo.cpp
)

target_link_libraries(GameEngine PRIVATE
    OpenGL::GL
    GLEW::GLEW
    glm::glm
    SDL3::SDL3
)