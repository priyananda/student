@echo off

cd source\fs
make
if errorlevel 1 goto up_exit
cd ..\..\

make
if errorlevel 1 goto error

echo insert floppy created with creatb
pause
copy kernel.bin a: /y > nul
if errorlevel 1 goto error
echo HELIX Installed
goto exit

:up_exit
cd ..\..\

:error
echo .
echo .
echo some error occured please clear it and try again

:exit
