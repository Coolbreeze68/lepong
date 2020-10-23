cmake_minimum_required(VERSION 3.7)
project(lepong)

set(CMAKE_CXX_STANDARD 17)

add_executable(lepong
    inc/lepong/Graphics/GL.h
    inc/lepong/Graphics/GLInterface.h
    inc/lepong/Graphics/Graphics.h
    inc/lepong/Graphics/Mesh.h
    inc/lepong/Graphics/Quad.h
    inc/lepong/Math/Math.h
    inc/lepong/Math/Vector2.h
    inc/lepong/Assert.h
    inc/lepong/Attribute.h
    inc/lepong/lepong.h
    inc/lepong/Log.h
    inc/lepong/OS.h
    inc/lepong/Window.h
    src/Graphics/Extensions.h
    src/Graphics/GL.cpp
    src/Graphics/Graphics.cpp
    src/Graphics/LoadOpenGLFunction.h
    src/Graphics/Mesh.cpp
    src/Graphics/Quad.cpp
    src/lepong.cpp
    src/Log.cpp
    src/Main.cpp
    src/Window.cpp)

target_link_libraries(lepong
    User32
    OpenGL32
    GDI32)

target_include_directories(lepong PUBLIC inc PRIVATE src)
