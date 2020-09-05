@echo off

set files=..\src\*.cpp
set flags=/Fe.\main.exe /EHsc /Zi
set libs=..\Dependencies\SDL2\lib\SDL2.lib ..\Dependencies\SDL2\lib\SDL2main.lib ..\Dependencies\SDL2_image\lib\x64\SDL2_image.lib Shell32.lib
set libpath=..\Dependencies\SDL2\lib\ 
set includePath=..\Dependencies\SDL2\include\ /I ..\Dependencies\SDL2_image\include\

pushd build
	cl %flags% %files% /I %includePath% /link %libs%  /SUBSYSTEM:CONSOLE
popd
