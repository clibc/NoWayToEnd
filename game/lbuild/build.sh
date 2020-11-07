#!/bin/bash

flags="-g -O0"
includes="-I /home/eax/Desktop/sdl_game/game/Dependencies/ \
	  -I /home/eax/Desktop/sdl_game/game/Dependencies/SDL2/include/ \
	  -I /home/eax/Desktop/sdl_game/game/Dependencies/SDL2_image/include \
	  -I /home/eax/Desktop/sdl_game/game/Dependencies/SDL2_ttf/include \
	  -I /home/eax/Desktop/sdl_game/game/src/"

files="/home/eax/Desktop/sdl_game/game/src/*.cpp \
       /home/eax/Desktop/sdl_game/game/src/opengl/*.cpp"

libs="-lSDL2 -lGL -lSDL2_ttf -lSDL2_image -lGLEW"


time g++ $flags $includes $files $libs

RESULT=$?

if [ $RESULT -eq 0 ]; 
then
	echo ""
	echo -e "\e[92mBuilded"
else
	echo ""
	echo -e "\e[91mFailed"  
fi
