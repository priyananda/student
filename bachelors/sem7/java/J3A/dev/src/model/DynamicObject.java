/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.model;

import java.awt.*;
import java.util.*;

/**
 * Dynamic Object is an object which:
 * 1> Can be drawn,
 * 2> register an event with a controller
 * 3> Possibly change state
 */
public abstract class DynamicObject extends GameObject
{
	public int state;
	protected int type;

	abstract public void draw(Graphics2D g);
	abstract public int getType();
	public void setState( int _s){
		state = _s;
	}
}