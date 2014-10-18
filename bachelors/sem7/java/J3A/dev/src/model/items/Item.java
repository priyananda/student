/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.model;
import java.awt.*;
import java.util.*;
import j3a.graphics.*;
import java.awt.image.*;
import java.awt.geom.*;
import java.applet.*;

public class Item extends Pickable
{
	private static HashMap cache = new HashMap();

	public Item(Point p, int i , int j , int ty)
	{
		location = p; tileXY = new Point(i,j);
		if( ty >= GameConstants.ITEM_START )
			type = ty - GameConstants.ITEM_START;
		else type = ty;
	}
	public int getType()
	{
		return GameConstants.ITEM_START + type ;
	}
	public void drawStatic(Graphics2D g)
	{
  		g.setColor( Color.ORANGE );
		g.setFont ( SpellConstants.spellFont );
		g.drawString(
			ItemData.itemLetters[type],
			location.x + GameConstants.tileWidth - 10,
			location.y + 10
		);
	}
	public void drawDynamic(Graphics2D g)
	{
		Image img = null;
		if ( cache.containsKey( ItemData.itemImagePaths[type] ) )
		{
			img = (Image) cache.get( ItemData.itemImagePaths[type] );
		}
		else
		{
          	img = ImageLoader.loadImage( ItemData.itemImagePaths[type] );
			img = j3a.graphics.Transparency.makeColorTransparent( img );
   			cache.put( ItemData.itemImagePaths[type] , img );
		}
		g.drawImage(
			img,
			location.x + GameConstants.tileWidth / 2,
			location.y - 23 ,
			46,46,
			null
		);
	}
	public void onPickUp(Human h)
	{
		if(controller != null)
			controller.showMessage("You got  the item " + j3a.model.ItemData.itemNames[type]);
	}
}