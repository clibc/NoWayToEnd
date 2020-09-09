@echo off

set files=..\src\*.cpp
set flags=/nologo /Fe.\main.exe /EHsc /Zi
set libs=..\Dependencies\SDL2\lib\x64\SDL2.lib ..\Dependencies\SDL2\lib\x64\SDL2main.lib ..\Dependencies\SDL2_image\lib\x64\SDL2_image.lib ..\Dependencies\SDL2_ttf\lib\x64\SDL2_ttf.lib Shell32.lib
set libpath=..\Dependencies\SDL2\lib\ 
set includePath=..\Dependencies\SDL2\include\ /I ..\Dependencies\SDL2_image\include\ /I ..\Dependencies\SDL2_ttf\include\

pushd build
	cl %flags% %files% /I %includePath% /link %libs%  /SUBSYSTEM:CONSOLE
popd
