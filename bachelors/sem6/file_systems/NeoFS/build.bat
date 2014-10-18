@echo off
set DJGPP=E:/lang/cpp/DJGPP/djgpp.env
set PATH=E:\lang\cpp\tc\bin;C:\windows\command;E:\lang\cpp\djgpp\bin

if "%1" == "clean" goto clean
if "%1" == "lib"   goto lib
if "%1" == "shell" goto shell
if "%1" == "gfx"   goto gfx
echo Usage:
echo       build clean - clean up all the mess
echo       build lib - build core library ( libfs.a )
echo       build shell - QSH
echo       build gfx - GUI ( deprecated )
echo Optional Second Argument is sent as gcc options
echo       -DSHOW_LIST=1 - enables colored list output ( extremely slow)
goto exit

:lib
gpp -w -O2 -Iinclude -c *.c 
ar -crv libfs.a *.o
copy libfs.a out\libfs.a
copy *.o out

del *.o
goto exit

:clean
del *.o 
del *.exe
del *.obj
del out\*.o
del out\*.a
del out\*.obj
del gfx\*.obj
del gfx\*.exe
goto exit

:shell
cd shell
gpp  -w %2 -I../include -o ../out/shell.exe *.cpp ../out/*.o 
cd ..
goto exit

:gfx
cd gfx
@echo on
gpp -I../include -o ../out/check.exe -w  check.c 
gpp -I../include -o ../out/format.exe -w format.c ../out/*.o
gpp -I../include -o ../out/qformat.exe -w qformat.c ../out/*.o
@echo off
cd ..
goto exit

:exit
