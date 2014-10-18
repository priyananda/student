/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.model;
import java.util.*;
import java.awt.*;

/**
 * The fundamental class for modelling the objects in runtime
 */
public abstract class GameObject{
    /**
	 *	pixel(x,y) position and tile co-ordinates
	 **/
    public Point location,tileXY;
	/**
	 * We model everything in terms of how something interacts with the
	 * Human
	 */
 	public abstract void interactWith( Human h );
 	public GameController controller;
	public void setController( GameController gc){
		controller = gc;
	}
	public void reactToSpell(int spellNum){}
}