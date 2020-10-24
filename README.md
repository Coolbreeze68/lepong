# lepong
A fully featured Pong clone made for Windows from scratch.

## Building
The following PowerShell code typically does the job. Or you could use the CMake GUI.
```
mkdir build
cd build
cmake ../
```

## Coding Style
When I started this project, I didn't really know what its coding style would be.
Right now it's pretty much a C interface with a C++ implementation.

The big thing with this C-ish design is that initialization and cleanup has to be done manually for every resource.
The major advantage is having full control over how data is managed, however it gets very tedious at times.
