/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.graphics;

import javax.swing.*;
import java.awt.*;
import java.io.*;
import javax.imageio.*;
import java.awt.image.*;
import java.awt.event.*;
import java.util.*;
import j3a.graphics.DesignTimeMap;
import j3a.model.GameMap;

class DesignTimeRenderingSurface extends JPanel
{
	int currentState;
	DesignTimeMap dtMap;

	DesignTimeRenderingSurface(j3a.model.GameMap gMap )
	{
		dtMap = new DesignTimeMap (
			gMap.nRows, gMap.nCols ,
			new Point( 0, gMap.nCols * GameConstants.tileWidth / 2 )
		);
		gMap.start = new Point( 0, gMap.nCols * GameConstants.tileWidth / 2 );
		setBackground(Color.black);
		currentState = GameConstants.GRASS;
		Dimension dx = new Dimension(
				(gMap.nRows + gMap.nCols) * GameConstants.tileWidth ,
				(gMap.nRows + gMap.nCols) * GameConstants.tileWidth / 2 + 100
		);
		gMap.imageWidth = dx.width;
		gMap.imageHeight = dx.height;
		setPreferredSize(dx);
		addMouseListener( new MouseAdapter() {
			public void mouseClicked( MouseEvent e){
				processMouseClick(e.getPoint());
			}
		});
    }
	public void setState( int newState)
	{
		currentState = newState;
	}
	public void changeTile( int i , int j , int ty )
	{
		dtMap.changeTile( i,j, ty , this);
	}
    public void paintComponent(Graphics g)
	{
        Graphics2D g2 = (Graphics2D) g;
		g2.clearRect( 0,0, getWidth(), getHeight() );
		dtMap.paint(g2);
	}
	private void processMouseClick(Point p)
	{
		Point out = new Point();
		if ( dtMap.contains( p,out) )
			dtMap.changeTile( out.x,out.y,currentState , this);
		repaint();
	}
	public void saveMap(GameMap gMap)
	{
		try
		{
   			dtMap.save( gMap );
		}
		catch( Exception ae){
			System.out.println("" + ae);
		}
	}
}