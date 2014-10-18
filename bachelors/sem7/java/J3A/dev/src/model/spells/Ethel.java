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
import java.applet.*;
import j3a.model.*;

public class Ethel extends SpellEffect
{
	BufferedImage bim = new BufferedImage(320 , 80 , BufferedImage.TYPE_INT_ARGB);
	int counter = 0;
	int position = 200;
	int numTimes = 0;
	AudioClip ac = AudioLoader.loadAudio("spells/explo.wav" );

	public int getAnimDelay(){
		return 300;
	}
	public Ethel(Point pnt){
		bim.createGraphics().drawImage(
			ImageLoader.loadImage("images/spell/asteroid.png"),
			0,0,320,80,null
		);
		point = pnt;
		ac.loop();
	}
	public void draw( Graphics2D g){
		BufferedImage clip = bim.getSubimage( 32 * ( counter % 10 ), 0 , 32 , 80 );
		g.drawImage( clip,point.x + 30,point.y - position - 60, 40 , 120 ,null);
		++counter;
		position -= 20;
		if( position <= 0){
			position = 200;
			++numTimes;
		}
		if(completed())ac.stop();
	}
	public Rectangle getClip(){
		return null;
	}
	public boolean completed(){
		return numTimes >= 5;
	}
}