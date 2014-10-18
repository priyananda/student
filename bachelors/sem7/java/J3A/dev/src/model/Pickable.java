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
 * Pickable is a Dynamic Object which
 * 1> Doesnot bite  !!!
 * 2> can be picked up by a human
 * 3> Support Multiple views
 */
public abstract class Pickable extends DynamicObject
{
	/**
	 * The static  view of a pickable is rendered when  map
	 * is created in MapCreator
	 */
	public final static int PV_STATIC = 0;
	/**
	 * The dynamic view of a pickable is rendered when  map
	 * is played at Runtime
	 */
	public final static int PV_DYNAMIC = 1;
	/**
	 * The inventory view of a pickable is rendered when it
	 * is shown in the Bag
	 */
	public final static int PV_INVENTORY = 2;
    /**
	 * The normal state of the pickable.
	 */
	public final static int PS_VISIBLE = 0;
    /**
	 * The hidden state of the pickable.
	 */
 	public final static int PS_HIDDEN = 1;

	protected int view = PV_STATIC;
	protected int state = PS_VISIBLE;

	public void setView(int _v)
	{
		view = _v;
	}
	public int getView()
	{
		return view;
	}
	public int getState()
	{
		return state;
	}
	public void setState(int val)
	{
		state = val;
	}
	public int getRespawnTime()
	{
		return -1;
	}

	public abstract void onPickUp(Human h);
	public abstract void drawStatic(Graphics2D g);
	public abstract void drawDynamic(Graphics2D g);
	public void drawInventory(Graphics2D g){}

	public void draw(Graphics2D g)
	{
		switch( view )
		{
			case PV_STATIC: drawStatic(g); break;
			case PV_DYNAMIC:
				if(state == PS_VISIBLE)
					drawDynamic(g);
				break;
			case PV_INVENTORY: drawInventory(g); break;
		}
	}

	public void interactWith(Human h)
	{
		if( state == PS_HIDDEN )
			return;
		if( !tileXY.equals(h.tileXY))
			return;
		state = PS_HIDDEN;
		if( controller != null )
		{
      		int time = getRespawnTime();
      		if( time != -1 )
      		{
				controller.registerEvent( new j3a.model.EventObject(){
					public void eventAction(){
						state = PS_VISIBLE;
					}
				},time);
			}
		}
		onPickUp(h);
	}
}