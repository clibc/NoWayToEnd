# No Way To End

2D Game but ends only if you cheat. (Not really for now)
This game is written in C++ with SDL2 and still in development.
You can design your own levels.

![](https://thumbs.gfycat.com/DirectFrayedGallowaycow-size_restricted.gif)

Besides the game, the codebase is an API that you can use to make any kind of 2D game.

This little API provides:
   - Easy to use Renderer with well designed abstraction layer.
   - Rendering text.
   - Loading and Rendering images (png).
   - 2D Animation 
   - Simple Level editor

#### Make your level:

Open `level1.lvl` with Notepad and Edit it according to pattern below:

  - `0`  Empty block
  - `1`  Wall
  - `2`  Coin (finish point)
  - `3`  Player's start position

The way I designed the game only supports the `10x10` level for now. The main purpose I prefer this because SDL2 has no support for batch rendering and making a draw call for each tile is so expensive. In order to make this happen, I will add OpenGL support.
The example level is shown above in the gif.
```
1,0,1,1,1,1,1,1,1,1,
1,0,0,0,0,1,0,0,0,2,
1,1,1,1,0,1,0,1,1,1,
0,0,0,1,0,0,0,0,0,1,
1,0,0,1,0,1,1,1,1,1,
1,0,1,1,0,1,0,0,0,1,
1,0,0,0,0,1,0,1,0,1,
1,1,1,1,0,1,1,1,0,1,
1,3,0,0,0,0,0,1,0,1,
1,1,1,1,1,1,0,0,0,1
```

#### Build:
In order to build the game you must have Microsoft Visual C++ compiler for Windows (usually, it comes with Visual Studio). If you have already set Visual Studio's environment variables, just run `build.bat` and it's done. 
But if you don't follow these steps:

  - Open CMD and navigate to `[location of VisualStudio]\VC\Auxiliary\Build\`
  - Run `vcvars64.bat`
  - Navigate to NoWayToEnd\game and run `build.bat`
  - And run `run.bat` or start `main.exe` in `\build\`

