call \sp j
@echo off
cd src
javac -d .. common\*.java graphics\*.java ui\*.java model\*.java model\monsters\*.java model\objects\*.java model\spells\*.java model\items\*.java
cd ..
jar cvfm game.jar docs\MANIFEST.MF j3a/ src/
copy /y game.jar ..\bin
