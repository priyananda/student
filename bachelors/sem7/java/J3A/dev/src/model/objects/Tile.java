/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.graphics;

import javax.swing.*;
import java.awt.*;
import java.awt.image.*;
import java.awt.event.*;
import java.util.*;


public class Tile
{
	public static final String names[] = {
		"grass"	, "water" , "lava", "wall" ,
		"tree" //, "door" , "oracle"
	};
	static final int DRAW_EDGE = 0x1;
    int type;
    int i,j;
    Point corner;
    Polygon polygon;

    public Tile( int _type,int _i, int _j)
	{
        type = _type;
        i = _i; j = _j;
        corner = null;
    }
    public Tile()
	{
        i = j = 0; type = GameConstants.GRASS;corner = null;polygon=null;
    }
    public Tile ( int _type,int _i, int _j, Point start)
	{
        this(_type,_i,_j);
        setPosition(start);
    }
    void setPosition(Point start)
	{
        corner = IsometricTransform.transform(start,i,j);
        polygon = IsometricTransform.transform(corner);
    }
    void draw(Graphics2D g , int drawFlags)
	{
		if( (drawFlags & DRAW_EDGE) == 1)
		{
			g.setColor(Color.white);
			g.drawPolygon(polygon);
		}
		TexturePaint t = null;
		switch( type )
		{
			default:
				t = TextureFactory.getGrassTexture();break;
			case GameConstants.WATER:
				t = TextureFactory.getWaterTexture();break;
			case GameConstants.LAVA:
				t = TextureFactory.getLavaTexture();break;
		}
		g.setPaint(t);
	    g.fill( polygon );
		switch( type )
		{
			case GameConstants.WALL:
				drawWall(g);break;
			case GameConstants.TREE:
				drawTree(g);break;
			//case GameConstants.ORACLE:
				drawOracle(g);break;
		}
    }

	private void drawWall( Graphics2D g)
	{
		Image img = ImageLoader.loadImage("images/wall-sprite.gif");
		g.drawImage( img , corner.x + 20, corner.y - 25 , (ImageObserver)null);
	}
	private void drawTree( Graphics2D g)
	{
		Image img = ImageLoader.loadImage("images/tree.gif");
		g.drawImage( img , corner.x + 20, corner.y - 30 , 60, 50,  (ImageObserver)null);
	}
	private void drawOracle( Graphics2D g)
	{
		Image img = ImageLoader.loadImage("images/oracle.gif");
		g.drawImage( img , corner.x + 25, corner.y - 20 , 60, 60, (ImageObserver)null);
	}
    boolean contains(Point p)
	{
        return polygon.contains( p );
    }
    public Rectangle getBounds()
    {
     	return IsometricTransform.getBounds(corner);
	}
    static void drawTile( Graphics2D g , Point start, int _i,int _j, int _type)
	{
        new Tile( _type,_i,_j,start).draw(g,1);
    }
}