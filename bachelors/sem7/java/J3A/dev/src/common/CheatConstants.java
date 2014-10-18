/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.model;
import java.util.*;

public interface CheatConstants 
{
	int
		MATCH_WIN = 0,
		MATCH_LOSE = 1,
		HEALTH_INC10 = 2,
		HEALTH_INC5 = 3,
		INVINCIBLE = 4,
		GIVE_SPELL_0 = 5,
		GIVE_SPELL_1 = 6,
		GIVE_SPELL_2 = 7,
		GIVE_SPELL_3 = 8,
		GIVE_SPELL_4 = 9,
		GIVE_ALL_SPELLS = 10;
	
	int NUM_CHEATS = 11;
	String codeStrings[] = {
		"MATCH_WIN" ,
		"MATCH_LOSE" ,
		"HEALTH_INC10" ,
		"HEALTH_INC5" ,
		"INVINCIBLE" ,
		"GIVE_SPELL_0" ,
		"GIVE_SPELL_1" ,
		"GIVE_SPELL_2" ,
		"GIVE_SPELL_3" ,
		"GIVE_SPELL_4" ,
		"GIVE_ALL_SPELLS" ,
	};
}
