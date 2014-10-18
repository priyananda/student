/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.graphics;
import j3a.model.*;

/**
 * Factory for creating renderable spells
 */
public abstract class SpellFactory
{
	public static SpellEffect createSpell(int spType,java.awt.Point p){
		if( spType >= GameConstants.SPELL_START )
			spType -= GameConstants.SPELL_START;
		switch (spType){
			case 0:return new MithrilMist(p);
			case 1:return new FireOfFangorn(p);
			case 2:return new TurinThunder(p);
			case 3:return new BaldurBane(p);
		}
		return new Ethel(p);
	}
}