Akallabeth - The Fall of Numenor
(c) 2003 Priyananda Shenoy/Harish JP
Distributed under GNU GPL 2.0

Contact:
harishjp@indiatimes.com
pshenoy_2000@yahoo.com

For gameplay help , see the manual

Compilation Intructions:
1> Make sure javac 1.4.1+ is availiable on PATH
2> To compile , change to src directory and type the command
  javac -d .. *.java
3> To run game , in top-level directory type
  java -cp . j3a.graphics.GameIntro
4> To run MapCreator , in top-level directory type
  java -cp . j3a.graphics.MapCreator

  if you have JDK properly installed, then double click the game.bat or mapc.bat
  to start playing
5> Better have the following directories or else it might not work properly
     audio/
     images/
     maps/
     players/
   The following directories are NOT required for playing the game
   	 src/ - required for compiling(of course)
   	 docs/
   	 Test/
   The rest are required by some parts of the game
6> You MUST have a map to  play
7> You MUST have atleast have one player
8> Create a dummy player file with atleast 2 lines of text. extension is ".ply"


Revision History

[Oct 2003]
Started with IsometricTransform and MapCreator

[Dec 2003]
Completed most of the features

[23 Jan 2004]
Changed the MapCreator UI to Tree based
Simplified a lot of code  - much , much cleaner now
Started on the Pickable interface