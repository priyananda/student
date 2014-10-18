/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.graphics;
import java.awt.*;
import j3a.model.*;

/**
 * Factory for creating runtime Objects
 */
public abstract class ObjectFactory
{
	public static GameObject createObject( Triple t , Point p ){
		return createObject( t.first , t.second , t.third ,  null , p);
	}
	public static GameObject createObject( int x , int y , int type  , Point p ){
		return createObject( x , y , type ,  null , p);
	}
	public static GameObject createObject(Triple t , GameController gc , Point p){
		return createObject( t.first , t.second , t.third , gc , p);
	}
	public static GameObject createObject(int x , int y , int type , GameController gc , Point p)
	{
		if( type  >= GameConstants.ITEM_START  && type  <= GameConstants.ITEM_END)
		{
            Item ret = new Item( p , x , y , type );
            ret.setView( gc == null ?  Pickable.PV_STATIC : Pickable.PV_DYNAMIC );
            ret.setController( gc );
            return ret;
		}
		if( type  >= GameConstants.SPELL_START  && type  <= GameConstants.SPELL_END )
		{
            Spell ret = new Spell( p , x , y , type );
            ret.setView( gc == null ?  Pickable.PV_STATIC : Pickable.PV_DYNAMIC );
            ret.setController( gc );
            return ret;
		}

		if( type  >= GameConstants.MONSTER_START  && type  <= GameConstants.MONSTER_END )
			return gc == null ? new Monster( p , x , y , type ) : new Monster( p , x , y , type , gc );

		if( type >= GameConstants.POWERUP_START && type <= GameConstants.POWERUP_END )
			return gc == null ? new PowerUp( p , x , y , type ) : new PowerUp( p , x , y , type , gc );

		switch( type ){
			case GameConstants.WATER:
			case GameConstants.WALL:
			case GameConstants.TREE:
			case GameConstants.LAVA:
			case GameConstants.ORACLE:
				return gc == null ? null : new DynamicTile( x , y , type , gc );
			case GameConstants.DOOR:
				return gc == null ? new Door( p , x , y ) : new Door( p , x , y , gc);
		}
		return null;
	}
}