/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.model;
import java.util.*;
import java.awt.*;
import j3a.graphics.*;

/**
 * Represents a tile.Basically models the static tile properties
 * Pretty easy to write. presently the only static object ,
 * but that may change ( Oracle !!)
 */
public class DynamicTile extends j3a.model.StaticObject
{
	public DynamicTile( int i , int j , int _type , GameController gc)
	{
		tileXY = new Point(i,j);
		type = _type;
		setController(gc);
	}
   	public void interactWith(Human h)
	{
  		switch( type ){
        	case GameConstants.WATER:
          		intWater(h);break;
         	case GameConstants.WALL:
         		intWall(h);break;
         	case GameConstants.LAVA:
         		intLava(h);break;
		}
    }
	/**
	 * Interaction of water tile , call h.drown()
	 * and schedule h.drown() after 5 seconds
	 */
	 private void intWater(final Human h)
	 {
		if( !tileXY.equals(h.tileXY)) return;
  		h.drown();
  		controller.registerEvent( new EventObject(){
        	public void eventAction(){
             	intWater(h);
			}
		},500);
	 }
  	/**
  	 * Lava tile takes 3 hp off from a human
  	 * and does so every 5 seconds
  	 */
	private void intLava(final Human h)
	{
        if( !tileXY.equals(h.tileXY)) return;
        h.decrementHP(3);
		controller.registerEvent( new EventObject(){
        	public void eventAction(){
             	intLava(h);
			}
		},500);
	}
	private void intWall( Human h )
	{
		if ( h.tileXY.x == tileXY.x ){
			if ( h.tileXY.y == tileXY.y + 1)
				h.setDirection( h.DIR_LEFT , 0 );
			if ( h.tileXY.y == tileXY.y - 1)
				h.setDirection( h.DIR_RIGHT , 0 );
		}else if ( h.tileXY.y == tileXY.y){
			if ( h.tileXY.x == tileXY.x + 1)
				h.setDirection( h.DIR_UP , 0 );
			if ( h.tileXY.x == tileXY.x - 1)
				h.setDirection( h.DIR_DOWN , 0 );
		}
	}
}