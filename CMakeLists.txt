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

# Copy assets folder to build
add_custom_command(
    TARGET Sight
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Sight>/assets
)