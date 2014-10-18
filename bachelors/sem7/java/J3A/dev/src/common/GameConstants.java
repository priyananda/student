/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.graphics;

/**
 * A set of misc. constants . I have tried not to hardcode but ...
 * Why this should be in j3a.graphics , god only knows
 */
public interface GameConstants
{
    int GRASS = 0,
        WATER = 1,
        LAVA = 2,
        WALL = 3,
		TREE = 4,
		DOOR = 5,
		ORACLE = 6;

	int POWERUP_START = 100;
	int POWERUP_END = 199;

	int MONSTER_START = 200;
	int MONSTER_END = 299;

	int SPELL_START = 300;
	int SPELL_END = 399;

	int ITEM_START = 400;
	int ITEM_END = 599;

	int DYNAMIC_MASK = 32; /* Sixth bit set */
 	long TICK_INTERVAL = 10; /* 10 for the rest of the world */
	int DEFAULT_HP = 100;

    int tileWidth = 60;
    int aspectRatio = 2;
    int ntile = aspectRatio * tileWidth / 2;

	/** Game States **/
	int GAME_WON = 1,
		GAME_LOST = 2;

 	String IMAGE_SUBDIR = "images/";
 	String AUDIO_SUBDIR = "audio/";
}