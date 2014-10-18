/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.graphics;
import java.awt.*;
import java.util.*;
import j3a.model.*;

public class PowerUp extends j3a.model.Pickable
{
	static final String names[] = {
		"HP +2" , "HP +5" , "HP +10"
	};
	final int imgWidth = 50;
	final Image images[] = {
		ImageLoader.loadImage("images/hp2.gif" ),
		ImageLoader.loadImage("images/hp5.gif" ) ,
		ImageLoader.loadImage("images/hp10.gif"),
	};
	final int val[] = { 2 , 5 , 10 };

	public PowerUp( Point p,int i , int j , int ty , GameController c)
	{
		this(p,i,j,ty);
		setController(c);
		setView( PV_DYNAMIC );
	}

	public PowerUp( Point p,int i , int j , int ty){
		tileXY = new Point(i,j);
		if( ty >= GameConstants.POWERUP_START )
			type = ty - GameConstants.POWERUP_START;
		else type = ty;
		location = p;
	}
	public void drawStatic( Graphics2D g)
	{
		g.drawImage(images[type],location.x - imgWidth / 2 + GameConstants.tileWidth, location.y - imgWidth/2, null);
	}
	public void drawDynamic( Graphics2D g)
	{
		drawStatic(g);
	}
	public void onPickUp(Human h)
	{
		h.incrementHP( val[type] );
	}
	public int getType()
	{
		return GameConstants.POWERUP_START + type ;
	}
	public int getRespawnTime()
	{
		return 1000;
	}
}