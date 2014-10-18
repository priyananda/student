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

public class TurinThunder extends SpellEffect
{
	Image cloud = ImageLoader.loadImage("images/spell/cloud.gif",new JLabel(" "));
	BufferedImage bim = new BufferedImage ( 140,180,BufferedImage.TYPE_INT_ARGB);
	int counter = 0 ;
	AudioClip ac = AudioLoader.loadAudio("spells/thunder.wav");

	public TurinThunder( Point pnt ){
		bim.createGraphics().drawImage(
			ImageLoader.loadImage("images/spell/lightning.png" ),
			0 , 0 , 140 , 180 , null
		);
		point =  pnt;
		ac.loop();
	}
	public int getAnimDelay(){
		return 100;
	}
	public void draw( Graphics2D g ){
		g.setComposite(AlphaComposite.getInstance( AlphaComposite.SRC_OVER, (float)0.8f ));
		g.drawImage (
			bim.getSubimage( ( counter % 2 ) * 70 , 0 , 70,180 ),
			point.x  , point.y - 180,70,180, null
		);
		g.drawImage(
			cloud,point.x - 65,point.y - 200,null
		);
		++counter;
		if(completed())ac.stop();
	}
	public Rectangle getClip(){
		return new Rectangle( point.x - 100,point.y - 180 ,100,200);
	}
	public boolean completed(){
		return counter >= 60;
	}
}