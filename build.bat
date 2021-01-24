@echo off

set files=..\code\*.cpp
set flags=/W3 /nologo /Fe.\main.exe /EHsc /Zi /MP6
set libs=..\dependencies\SDL2\lib\x64\SDL2.lib ..\dependencies\SDL2\lib\x64\SDL2main.lib ..\dependencies\GLEW\lib\glew32.lib opengl32.lib Shell32.lib
set includePath=/I ..\dependencies\SDL2\include\ /I ..\dependencies\ /I ..\dependencies\GLEW\ /I ../code/

pushd output
	cl %flags% %files% %includePath% /link %libs% /SUBSYSTEM:CONSOLE
popd
