//package j3a.graphics;

import java.awt.*;
import java.awt.geom.*;
import java.awt.image.*;
import java.util.*;

abstract class Spell
{
	public abstract int getAnimDelay();
	public abstract int draw( Graphics2D g , int tileX , int tileY );
	public abstract void start();
	public abstract void stop();
}

class FireOfFangorn extends Spell
{
	int counter = 0;
	static final Image img[] = {
		ImageLoader.loadImage( "images/fire.gif"),
		ImageLoader.loadImage( "images/fire2.gif")
	};
	static final int sizes[] = { 120,120,60,60};
	
	public int getAnimDelay(){
		return 100;
	}
	public int draw( Graphics2D g , Point pnt ){
		Image i = img [ counter % 2 ];
		int size = sizes[  counter % 4 ];
		g.drawImage ( i , pnt.x , pnt.y - size / 2,60,size , null);
		++counter;
	}
	public void start(){}
	public void stop(){}
}

class MithrilMist extends Spell
{
	static final Image img = ImageLoader.loadImage( "images/mithril.gif");
	int rotate = 0;
	float alpha  = 0.50f;
	AffineTranform af = new AffineTranform ();

	public int getAnimDelay(){
		return 100;
	}
	public int draw( Graphics2D g , Point pnt ){
		af.rotate( Math.toRadian(rotate) );
		g.setTranform( af );
		g.setComposite(AlphaComposite.getInstance( AlphaComposite.SRC_OVER, (float)alpha ));
		g.drawImage ( img , pnt.x + 50, pnt.y , null);
		if ( (rotate += 5 ) >= 360 ) rotate = 0;
		if ( (alpha  += 0.1f) >= 0.97f ) alpha = 0.5f;
	}
	public void start(){}
	public void stop(){}
}
