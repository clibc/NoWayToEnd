flags="-g -O0"
includes="-I /home/eax/Desktop/sdl_game/dependencies/ \
	  -I /home/eax/Desktop/sdl_game/dependencies/GLEW \
	  -I /home/eax/Desktop/sdl_game/dependencies/SDL2/include/ \
	  -I /home/eax/Desktop/sdl_game/dependencies/SDL2_image/include \
	  -I /home/eax/Desktop/sdl_game/dependencies/SDL2_ttf/include \
	  -I /home/eax/Desktop/sdl_game/code/"

files="/home/eax/Desktop/sdl_game/code/*.cpp"

libs="-lSDL2 -lGL -lGLEW"

pushd /home/eax/Desktop/sdl_game/lbuild/
time g++ $flags $includes $files $libs
popd

RESULT=$?

if [ $RESULT -eq 0 ]; 
then
	echo ""
	echo -e "\e[92mBuilded"
else
	echo ""
	echo -e "\e[91mFailed"  
fi

