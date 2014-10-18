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
import j3a.model.*;

public class DesignTimeMap
{
	Tile tiles[][];
	int nRows , nCols;
	Vector dyn = new Vector(5,5);

	public DesignTimeMap( int _nr , int _nc , Point start)
	{
		nRows = _nr; nCols = _nc;
		try
		{
        	tiles = new Tile[nRows][nCols];
		}
		catch(Exception e)
		{
      		System.out.println( "" + e );
		}
        for ( int i = 0 ; i < nRows; ++i )
            for ( int j = 0 ; j < nCols; ++j )
            	try
				{
                	tiles[i][j] = new Tile( GameConstants.GRASS ,i,j , start );
				}
				catch(Exception e)
				{
					System.out.println( " i= " + i + ",j=" + j + ",ex=" + e );
				}
	}

	public void paint(Graphics2D g)
	{
		renderEdges(g);
		for ( int i = 0 ; i < nRows; ++i )
			for ( int j = 0 ; j < nCols ; ++j )
				tiles[i][j].draw(g,1);

		for ( int i = 0 ; i < dyn.size() ; ++i )
			((DynamicObject) dyn.get(i)).draw(g);
	}
	public void saveMapImage( Graphics2D g)
	{
		renderEdges(g);
		for ( int i = 0 ; i < nRows; ++i )
			for ( int j = 0 ; j < nCols ; ++j )
				tiles[i][j].draw(g,0);
	}
	/**
    *	checks if 'in' is contained in some tile tiles[i][j] , if so sets
	*	'out' to (i,j) and returns true
	*/
	boolean contains( Point in , Point out)
	{
		for ( int i = 0 ; i < nRows; ++i )
            for ( int j = 0 ; j < nCols ; ++j )
				if( tiles[i][j].contains(in) ){
					out.x = i ; out.y = j;return true;
				}
		return false;
	}

	void setTileState( int i , int j , int type )
	{
		Iterator  p = dyn.iterator();
		while( p.hasNext() )
		{
			DynamicObject d = (DynamicObject)p.next();
			if( d.tileXY.x == i &&  d.tileXY.y == j )
				p.remove();
		}
		if( type >= GameConstants.DYNAMIC_MASK || type == GameConstants.DOOR )
			addDynamicObject( i , j , type);
		else
			tiles[i][j].type = type;
	}

	void addDynamicObject(int  i , int j , int type)
	{
		tiles[i][j].type = GameConstants.GRASS;
		dyn.add ( ObjectFactory.createObject( i , j , type , tiles[i][j].corner ));
	}

	void changeTile( int i , int j , int type , JPanel jp)
	{
		setTileState(i,j,type);
		jp.repaint( tiles[i][j].getBounds() );
	}

	public void renderEdges(Graphics2D g)
	{
		Polygon p = new Polygon();
		Point temp = tiles[0][0].corner;
		p.addPoint(temp.x,temp.y);
		p.addPoint(temp.x , temp.y + 70);
		temp = tiles[nRows-1][0].corner;
		p.addPoint(temp.x + GameConstants.ntile , temp.y + GameConstants.tileWidth / 2 + 70);
		p.addPoint(temp.x + GameConstants.ntile , temp.y + GameConstants.tileWidth / 2 );

		g.setPaint( TextureFactory.getEdgeTexture() );
		g.fill(p);
		g.setColor(Color.white);
		g.drawPolygon(p);

		p.reset();
		temp = tiles[nRows-1][0].corner;
		p.addPoint(temp.x + GameConstants.ntile , temp.y + GameConstants.tileWidth / 2 + 70);
		p.addPoint(temp.x + GameConstants.ntile , temp.y + GameConstants.tileWidth / 2 );
		temp = tiles[nRows-1][nCols-1].corner;
		p.addPoint(temp.x + GameConstants.ntile * 2  , temp.y);
		p.addPoint(temp.x + GameConstants.ntile * 2 , temp.y  + 70);

		g.setPaint( TextureFactory.getEdgeTexture() );
		g.fill(p);
		g.setColor(Color.white);
		g.drawPolygon(p);
	}

	private void saveMapData( j3a.model.GameMap gmap )
	{
		Iterator iter = dyn.iterator();
		while( iter.hasNext()){
			DynamicObject obj = (DynamicObject)iter.next();
			gmap.addObject( obj.tileXY.x , obj.tileXY.y , obj.getType() );
		}
		for( int i = 0 ; i < nRows ; ++i )
			for( int j = 0 ; j < nCols ; ++j )
				if( tiles[i][j].type != GameConstants.GRASS )
					gmap.addObject( i , j , tiles[i][j].type );
	}

	public void save( j3a.model.GameMap gmap ) throws Exception
	{
        BufferedImage bim = new BufferedImage ( gmap.imageWidth , gmap.imageHeight ,BufferedImage.TYPE_INT_RGB);
		Graphics2D gx = bim.createGraphics();
		saveMapImage( gx );
		saveMapData( gmap );
		j3a.model.GameMap.persist( gmap,bim );
	}
}