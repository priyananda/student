/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.model;
import java.applet.*;
import j3a.graphics.AudioLoader;

/**
 * This is the stupidest named class in the project
 */
public interface HumanConstants
{
	/** 
	 * use these things as masks
	 */
	int DIR_UP  = 1,
		DIR_DOWN = 2,
		DIR_LEFT = 4,
		DIR_RIGHT = 8;

	AudioClip water = AudioLoader.loadAudio( "water.wav" , 1 );
	AudioClip oooh = AudioLoader.loadAudio( "oo.wav" , 1 );
	AudioClip dead = AudioLoader.loadAudio( "dead.wav" , 1 );
	AudioClip silly = AudioLoader.loadAudio( "silly.wav" , 1 );
	AudioClip spellsnd = AudioLoader.loadAudio( "confirm.wav" , 1 );
}
