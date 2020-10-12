cmake_minimum_required(VERSION 3.7)
project(lepong)

set(CMAKE_CXX_STANDARD 17)

add_executable(lepong
    inc/lepong/Graphics/Context.h
    inc/lepong/Graphics/Graphics.h
    inc/lepong/Math/Math.h
    inc/lepong/Math/Vector2.h
    inc/lepong/Assert.h
    inc/lepong/Attribute.h
    inc/lepong/lepong.h
    inc/lepong/Window.h
    src/lepong/Graphics/Graphics.cpp
    src/lepong/Graphics/LoadOpenGLFunction.h
    src/lepong/lepong.cpp
    src/lepong/Main.cpp
    src/lepong/Window.cpp)

target_link_libraries(lepong User32 OpenGL32)
target_include_directories(lepong PUBLIC inc PRIVATE src)
