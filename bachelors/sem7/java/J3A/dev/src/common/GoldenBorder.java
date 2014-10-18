/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.graphics;

import javax.swing.*;
import javax.swing.border.*;
import java.awt.image.*;
import java.awt.*;

public class GoldenBorder extends EmptyBorder
{
	static TexturePaint tp;
	static{
		BufferedImage bi = new BufferedImage(20, 20, BufferedImage.TYPE_INT_RGB);
        Graphics2D big = bi.createGraphics();
		Image i = ImageLoader.loadImage( "images/gold.gif" );
		big.drawImage(i , 0,0, 20,20,null );
		tp = new TexturePaint(bi,new Rectangle(0,0,50,50) );
	}
	public GoldenBorder(){
		super(10,10,10,10);
	}
	public void paintBorder( Component c,Graphics gx ,  int x, int y, int width, int height) {
		/*
		Graphics2D g = (Graphics2D) gx;
		g.setPaint(tp);
		g.fillRect( x  , y  , x + width  , y +  );
		g.fillRect( x  , y + height - 5 , x + width + 5 , y + height + 3  );
		g.fillRect( x  , y  , x + 5 , y + height   );
		g.fillRect( x + width - 5 , y - 5 , x + width + 5 , y + 5  );
		*/
	}
}