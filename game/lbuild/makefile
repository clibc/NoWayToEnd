PROG = sdlgame
CC = g++
CPPFLAGS =-O2 -g -I../src -I../Dependencies/SDL2/include/ -I ../Dependencies/SDL2_image/include/ -I ../Dependencies/SDL2_ttf/include/ 
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
FILES = ../src/*.cpp

main:
	$(CC) $(CPPFLAGS) $(FILES) $(LDFLAGS) 

clean: 
	rm -f ./*.out

run :
	./a.out
