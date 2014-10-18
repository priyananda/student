/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.graphics;

/**
 * This class epitomises the effect rendering of the spell. This has NO data 
 *about the spell.See Spell for that
 */
public abstract class SpellEffect
{
	public java.awt.Point point;
	public abstract int getAnimDelay();
	public abstract void draw( java.awt.Graphics2D g );
	public abstract java.awt.Rectangle getClip();
	public abstract boolean completed();
}
