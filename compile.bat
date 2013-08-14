@echo off
echo This requires MinGW to be installed and in your path.
echo Otherwise, it will not compile.
echo.
pause
windres -i ScribblePatcher.rc -o resource.o
gcc -mwindows ScribblePatcher.c resource.o -o ScribblePatcher.exe