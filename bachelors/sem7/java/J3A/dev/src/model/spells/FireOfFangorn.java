/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */

package j3a.graphics;

import java.awt.*;
import java.awt.geom.*;
import java.awt.image. *;
import javax.swing.*;

import j3a.model.*;

public class FireOfFangorn extends SpellEffect
{
	BufferedImage bim = new BufferedImage ( 580,111,BufferedImage.TYPE_INT_ARGB);
	java.applet.AudioClip ac = AudioLoader.loadAudio( "spells/fire.wav" );
	int counter = 0;

	public int getAnimDelay(){
		return 100;
	}
	public FireOfFangorn(Point pnt){
		bim.createGraphics().drawImage(
			ImageLoader.loadImage( "images/spell/fire.png"),
			0 , 0 ,580 , 111 , null
		);
		point = pnt;
		ac.play();
	}
	public void draw( Graphics2D g){
		g.setComposite(AlphaComposite.getInstance( AlphaComposite.SRC_OVER, (float)0.7 ));
		BufferedImage i = bim.getSubimage(
			(counter % 10) * 58 , 0,58,111
		);
		g.drawImage (
			i ,
			point.x  + 20 , point.y - 100 ,
			58,111,
			null
		);
		++counter;
		if( completed() ) ac.stop() ;
	}
	public Rectangle getClip(){
		return new Rectangle(point.x  + 20 , point.y - 100 ,58,111);
	}
	public boolean completed(){
		return counter >= 50;
	}
}