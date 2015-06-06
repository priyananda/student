@echo off
cls
echo Helix Boot Disk Creator

nasm -f bin boot0.asm -oboot0.bin
if errorlevel 1 goto error

tcc -c -r- -mt  main.c
if errorlevel 1 goto error

tcc -c -r- -mt fat12.c
if errorlevel 1 goto error

tcc -c -r- -mt boot1.c
if errorlevel 1 goto error

nasm -f obj startup.asm
if errorlevel 1 goto error

nasm -f obj graphics.asm
if errorlevel 1 goto error

tlink /x startup.obj main.obj fat12.obj graphics.obj boot1.obj
if errorlevel 1 goto error

exe2bin startup.exe boot1.bin /SA00
if errorlevel 1 goto error

goto install

nasm -f obj startup1.asm
if errorlevel 1 goto error

tlink /x startup1.obj test.obj
if errorlevel 1 goto error

exe2bin startup1.exe kernel.bin /S1000
if errorlevel 1 goto error

:install
del *.obj
del startup.exe

echo Insert a formatted floppy
pause

echo .
echo .
echo Installing boot record ...

partcopy boot0.bin 0 3 -f0
partcopy boot0.bin 3e 1c2 -f0 3e
if errorlevel 1 goto error

echo Installing boot1 ...
copy /Y boot1.bin a:\ > nul

echo Boot disk successfully created
echo Please copy the kernel.bin file to floppy [use mk]
goto exit

:error
echo .
echo .
echo some error occured please correct it.
echo pause

:exit
