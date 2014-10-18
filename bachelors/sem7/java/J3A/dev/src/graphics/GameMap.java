/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.model;

import java.util.*;
import java.awt.*;
import java.io.*;
import java.awt.image.BufferedImage;
import j3a.model.*;


public class GameMap implements Serializable
{
	public int nRows, nCols;
	public int imageWidth , imageHeight;
	public Point start = new Point();
	public String mapName;
	public String mapDescription;
	public String saveFile;
	public Vector objects = new Vector();

	public void addObject( int x, int y, int type )
	{
		objects.add( new Triple( x , y , type ));
	}

	public static void persist(GameMap gameMap, BufferedImage image) throws Exception
	{
		Properties prop = new Properties();
		Iterator iter;
		StringBuffer value;

		prop.setProperty( "mapname" , gameMap.mapName );
		prop.setProperty( "description" , gameMap.mapDescription);
		prop.setProperty( "rows" , "" + gameMap.nRows );
		prop.setProperty( "cols" , "" + gameMap.nCols );
		prop.setProperty( "imagewidth" , "" + gameMap.imageWidth );
		prop.setProperty( "imageheight" , "" + gameMap.imageHeight );
		prop.setProperty( "startx" , "" + gameMap.start.x );
		prop.setProperty( "starty" , "" + gameMap.start.y);

		value =  new StringBuffer();
		iter = gameMap.objects.iterator();
		if( iter.hasNext() )
		{
			Triple p = (Triple) iter.next();
			value.append(  p.first + "," + p.second + "," + p.third);
		}
		while( iter.hasNext())
		{
			Triple p = (Triple) iter.next();
			value.append( "," + p.first + "," + p.second + "," + p.third );
		}
		prop.setProperty( "objects" , value.toString() );
		FileOutputStream fos = new FileOutputStream("maps/" + gameMap.saveFile + ".hsh" );

		String header =  "#--------The Fall Of Numenor Map file---------- \r\n" +
						 "#----(c) 2003 Priyananda Shenoy / Harish JP---- \r\n" +
						 "# $ Automatically created donot edit ";
		prop.store( fos, header);
		fos.close();

		javax.imageio.ImageIO.write( image , "png" , new File("maps/" + gameMap.saveFile + ".png" ));
	}
	public static GameMap restore( String filename ) throws Exception
	{
		FileInputStream fis = new FileInputStream( filename);
		Properties prop = new Properties();
		prop.load( fis );
  		GameMap map = new GameMap();

		map.mapName = prop.getProperty("mapname");
		map.mapDescription = prop.getProperty("description");
		map.saveFile = filename.substring( 5, filename.indexOf( ".hsh")  );
		map.start.x = Integer.parseInt(prop.getProperty("startx"));
		map.start.y = Integer.parseInt(prop.getProperty("starty"));
		map.imageWidth = Integer.parseInt(prop.getProperty("imagewidth"));
		map.imageHeight = Integer.parseInt(prop.getProperty("imageheight"));
		map.nRows =  Integer.parseInt(prop.getProperty("rows"));
		map.nCols =  Integer.parseInt(prop.getProperty("cols"));

		StringTokenizer st = new StringTokenizer(prop.getProperty( "objects" ) ,",");
		while (st.hasMoreTokens())
		{
			Triple temp = new Triple();
			temp.first = Integer.parseInt(st.nextToken());
			temp.second = Integer.parseInt(st.nextToken());
			temp.third = Integer.parseInt(st.nextToken());
			map.objects.add( temp );
		}
		return map;
	}
}