# lepong
A fully featured Pong clone made for Windows from scratch.

## Coding style
When I started this project, I didn't really know what its coding style would be.
Right now it's pretty much a C interface with a C++ implementation.

The big thing with this C-ish design is that initialization and cleanup has to be done manually for every resource.
The major advantage is having full control over how data is managed, however it gets very tedious at times.
