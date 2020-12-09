cmake_minimum_required(VERSION 3.7)
project(lepong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")

add_executable(lepong WIN32
    inc/lepong/Game/Ball.h
    inc/lepong/Game/Game.h
    inc/lepong/Game/GameObject.h
    inc/lepong/Game/Paddle.h
    inc/lepong/Graphics/GL.h
    inc/lepong/Graphics/GLInterface.h
    inc/lepong/Graphics/Graphics.h
    inc/lepong/Graphics/Mesh.h
    inc/lepong/Graphics/Quad.h
    inc/lepong/Math/Math.h
    inc/lepong/Math/Vector2.h
    inc/lepong/Time/Time.h
    inc/lepong/Attribute.h
    inc/lepong/Check.h
    inc/lepong/lepong.h
    inc/lepong/Log.h
    inc/lepong/OS.h
    inc/lepong/Window.h
    src/Game/Ball.cpp
    src/Game/GameObject.cpp
    src/Game/Paddle.cpp
    src/Graphics/WGLExtensions.h
    src/Graphics/GL.cpp
    src/Graphics/Graphics.cpp
    src/Graphics/LoadOpenGLFunction.h
    src/Graphics/Mesh.cpp
    src/Graphics/Quad.cpp
    src/Math/Math.cpp
    src/Time/Time.cpp
    src/lepong.cpp
    src/Log.cpp
    src/Main.cpp
    src/Window.cpp)

target_link_libraries(lepong
    User32
    Opengl32
    GDI32)

target_include_directories(lepong PUBLIC inc PRIVATE src)
