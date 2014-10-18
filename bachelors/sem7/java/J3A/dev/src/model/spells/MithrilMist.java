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

/**
 * Fantastic mist effect . Wow! what a spell
 */
public class MithrilMist extends SpellEffect
{
	static final Image img[] = {
		ImageLoader.loadImage( "images/spell/mist1.png"),
		ImageLoader.loadImage( "images/spell/mist2.png")
	};
	java.applet.AudioClip ac = AudioLoader.loadAudio( "spells/mithril.wav" );
	float alpha = 0.5f;
	int height = 10 , numTimes = 0;
	int sizex = 50, sizey = 60;

	public MithrilMist( Point pnt ){
		point = pnt;
		ac.loop();
	}
	public int getAnimDelay(){
		return 100;
	}
	public void draw( Graphics2D g){
		g.drawImage (
			img[0],
			point.x + 35,
			0,
			20,height,
			null
		);
		if( height < point.y )
			height += 10;
		else{
			g.setComposite(AlphaComposite.getInstance( AlphaComposite.SRC_OVER, (float)alpha ));
			g.drawImage (
				img[1],
				point.x + 35 - sizex / 2,
				point.y - sizey + 20,
				sizex,sizey,
				null
			);
			sizey += 10;
			alpha += 0.03f;
			if( (sizex += 10) > 200 ){ sizex = 50;sizey = 60;alpha = 0.5f;++numTimes;}
		}
		if( completed() )ac.stop();
	}
	public Rectangle getClip(){
		return new Rectangle( point.x - 200,0,100, point.y + 100);
	}
	public boolean completed(){
		return numTimes >= 5;
	}
}