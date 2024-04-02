cmake_minimum_required(VERSION 3.16)

project(Sight LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCE_FILE_LIST
"src/Main.cpp"
"src/Buffer.hpp"
"src/Buffer.cpp"
"src/VertexBuffer.hpp"
"src/VertexBuffer.cpp"
"src/VertexArray.hpp"
"src/VertexArray.cpp"
"src/IndexBuffer.hpp"
"src/IndexBuffer.cpp"
"src/VertexBufferLayout.hpp"
"src/VertexBufferLayout.cpp"
"src/Shader.hpp"
"src/Shader.cpp"
"src/Renderer.hpp"
"src/Renderer.cpp"
"src/Texture.hpp"
"src/Texture.cpp"
"src/Configuration.hpp"
"src/Camera.cpp"
"src/Camera.hpp"
"src/Mesh.hpp"
"src/Mesh.cpp"
"src/Model.hpp"
"src/Model.cpp"
"src/Drawable.hpp"
"src/vendor/stb_image.h"
"src/vendor/stb_image.cpp"
"src/tests/Test.hpp"
"src/tests/Test.cpp"
"src/tests/TestClearColor.hpp"
"src/tests/TestClearColor.cpp"
"src/tests/TestsLibrary.hpp"
"src/tests/TestsLibrary.cpp"
"src/tests/TestTexture2D.hpp"
"src/tests/TestTexture2D.cpp"
"src/tests/Test3DCube.hpp"
)

add_executable(Sight ${SOURCE_FILE_LIST})

# Set C++ dialect version
target_compile_features(Sight PRIVATE cxx_std_20)

include(FetchContent)

# Installing GLEW
FetchContent_Declare(
    glew
    URL           https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip
    SOURCE_SUBDIR build/cmake
)
FetchContent_MakeAvailable(glew)

target_link_libraries(Sight PRIVATE glew)
target_include_directories(Sight PRIVATE ${FETCHCONTENT_BASE_DIR}/glew-src/include)

# Installing GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)
FetchContent_MakeAvailable(glfw)

target_link_libraries(Sight PRIVATE glfw)

# Installing GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1
)
FetchContent_MakeAvailable(glm)

target_link_libraries(Sight PRIVATE glm)

# Installing ImGui
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.90.4
)

FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)
target_link_libraries(imgui PRIVATE glfw)

target_link_libraries(Sight PUBLIC imgui)

# Copy assets folder to build
add_custom_command(
    TARGET Sight
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Sight>/assets
)