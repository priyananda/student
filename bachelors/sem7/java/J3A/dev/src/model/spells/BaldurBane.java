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

public class BaldurBane extends SpellEffect
{
	int counter = 0;
	Image img = ImageLoader.loadImage("images/spell/water.png");
	Image light = ImageLoader.loadImage("images/spell/gold_light.png");
	AudioClip ac = AudioLoader.loadAudio("spells/quake.wav" );
	int size1 = 20,size2 = 30;
	float alpha = 0.3f;

	public int getAnimDelay(){
		return 200;
	}
	public BaldurBane(Point pnt){
		point = pnt;
		ac.loop();
	}
	public void draw( Graphics2D g){
		g.setComposite(AlphaComposite.getInstance( AlphaComposite.SRC_OVER, (float)alpha ));
		g.drawImage(
			light,
			point.x + 55,0,
			10,point.y,null
		);
		g.setComposite(AlphaComposite.getInstance( AlphaComposite.SRC_OVER, (float)0.3f ));
		g.drawImage(
			img,
			point.x - 3 * size2 / 10 + 50,
			point.y - size2 / 5,
			3 * size2 / 5,
			2 * size2 / 5,null
		);
		if( (size1 += 10) >= 300 ){ size1 = 20;++counter;}
		if( (size2 += 20) > 600 )size2 = 10;
		if( (alpha += 0.02f) > 0.6f ) alpha = 0.3f;
		if( completed() ) ac.stop();
	}
	public Rectangle getClip(){
		return null;
	}
	public boolean completed(){
		return counter >= 3;
	}
}