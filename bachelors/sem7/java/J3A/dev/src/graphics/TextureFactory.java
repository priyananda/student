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

public class TextureFactory
{
	final static String imgPath = "images/";
	static TexturePaint grass = null , wall = null , lava = null,
				water = null , edge = null;

	public static TexturePaint  createTexture( String fname){
		Image i = ImageLoader.loadImage( imgPath + fname );
		BufferedImage bi = new BufferedImage(
			i.getWidth(null),i.getHeight(null),
			BufferedImage.TYPE_INT_RGB
		);
		bi.createGraphics().drawImage(i,0,0,null );
		return new TexturePaint(bi,new Rectangle(0,0,bi.getWidth(),bi.getHeight()) );
	}

	static TexturePaint getGrassTexture(){
		if( grass == null ) grass = createTexture("grass.gif");
		return grass;
	}
	static TexturePaint getWaterTexture(){
		if( water == null ) water = createTexture("water.gif");
		return water;
	}
	static TexturePaint getWallTexture(){
		if( wall == null ) wall = createTexture("wall.gif");
		return wall;
	}
	static TexturePaint getLavaTexture(){
		if( lava == null ) lava = createTexture("lava.gif");
		return lava;
	}
	static TexturePaint getEdgeTexture(){
		if(edge == null) edge = createTexture("ground.gif");
		return edge;
	}
}
