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

public class IsometricTransform
{
    public static Point transform ( Point start , int i , int j )
	{
        return new Point(
            start.x + GameConstants.ntile * ( i + j ),
            start.y + GameConstants.tileWidth * ( i - j ) / 2
		);
    }
    public static Polygon transform( Point corner )
	{
		int x[] = {
            corner.x,
            corner.x + GameConstants.ntile,
            corner.x + GameConstants.ntile * 2,
            corner.x + GameConstants.ntile,
        };
        int y[] = {
            corner.y,
            corner.y - GameConstants.tileWidth / 2,
            corner.y,
            corner.y + GameConstants.tileWidth / 2,
        };
        return new Polygon ( x , y , 4 );
    }
    public static Rectangle getBounds( Point corner )
    {
		return new Rectangle(
     		corner.x , corner.y - GameConstants.tileWidth / 2,
			GameConstants.ntile * 2,  GameConstants.tileWidth
		);
	}
	public static Polygon transform2( Point start , int i,int j)
	{
		return transform(transform(start,i,j));
	}
}