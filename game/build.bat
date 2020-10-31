@echo off

set files=..\src\*.cpp ..\src\opengl\*.cpp
set flags=/W3 /nologo /Fe.\main.exe /EHsc /Zi
set libs=..\Dependencies\SDL2\lib\x64\SDL2.lib ..\Dependencies\SDL2\lib\x64\SDL2main.lib ..\Dependencies\SDL2_image\lib\x64\SDL2_image.lib ..\Dependencies\SDL2_ttf\lib\x64\SDL2_ttf.lib ..\Dependencies\GLEW\lib\glew32.lib opengl32.lib Shell32.lib
set libpath=..\Dependencies\SDL2\lib\ 
set includePath=..\Dependencies\SDL2\include\ /I ..\Dependencies\SDL2_image\include\ /I ..\Dependencies\SDL2_ttf\include\ /I ..\src\ /I ..\Dependencies\GLEW\ 

pushd build
	cl %flags% %files% /I %includePath% /link %libs%  /SUBSYSTEM:CONSOLE
popd