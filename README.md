# This is the OpenGL implementation of NWTE.

The main reason to change SDL2 rendering engine was making the rendering efficient through batching.

![](https://s2.gifyu.com/images/ezgif-1-a54f4654cd89.gif)

The scene above being rendered with 3 Draw Calls.

# Build instructions :
#### Linux:
Required packages:
 - libsdl2-dev
 - libglfw3-dev
 - OpenGL 4.6
 
`cd lbuild/` </br>
`chmod +x build.sh` </br>
`./build.sh`

#### Microsoft Windows:
Set Visual Studio environment variables (vcvarsall.bat)
And run `build.bat`.
