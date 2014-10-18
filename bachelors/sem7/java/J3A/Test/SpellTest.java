import java.awt.*;
import java.awt.geom.*;
import java.io.*;
import java.awt.image. *;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
import java.applet.*;
import java.net.*;

abstract class Spell
{
	public abstract int getAnimDelay();
	public abstract void draw( Graphics2D g , Point p);
	public abstract void start();
	public abstract void stop();
}

class SP
{
	static AudioClip getClip( String file){
		try{
			String dir = System.getProperty("user.dir");
			URL url = new URL( "file:///" + dir + "/" + file );
			System.out.println("" + url);
			return JApplet.newAudioClip(url);
		}catch(Exception ae){
			JOptionPane.showMessageDialog(
				null,
				" " + ae,
				"bb",
				0
			);
		}
		return null;
	}
}

class Ethel extends Spell
{
	public static final Image img = ImageLoader.loadImage("images/asteroid.png", new Label(""));
	BufferedImage bim = new BufferedImage(320 , 80 , BufferedImage.TYPE_INT_ARGB);
	Graphics2D gr = bim.createGraphics();
	int counter = 0;
	int position = 200;
	AudioClip ac;

	public int getAnimDelay(){
		return 100;
	}
	public Ethel(){
		gr.drawImage(img,0,0,320,80,null);
		ac = SP.getClip("laugh.wav");
	}
	public void draw( Graphics2D g , Point pnt){
		BufferedImage clip = bim.getSubimage( 32 * ( counter % 10 ), 0 , 32 , 80 ); 
		g.drawImage( clip,pnt.x ,pnt.y - position , 40 , 120 ,null);
		++counter;
		position -= 20;
		if( position <= 0){
			position = 200;
			ac.play();
		}
	}
	public void start(){}
	public void stop(){}

}
class FireOfFangorn extends Spell
{
	static final Image img = ImageLoader.loadImage( "images/fire.png" ,new JLabel(""));
	BufferedImage bim = new BufferedImage ( 580,111,BufferedImage.TYPE_INT_ARGB);
	int counter = 0;
			
	public int getAnimDelay(){
		return 100;
	}
	public FireOfFangorn(){
		bim.createGraphics().drawImage( img , 0 , 0 ,580 , 111 , null );
	}
	public void draw( Graphics2D g , Point pnt ){
		g.setComposite(AlphaComposite.getInstance( AlphaComposite.SRC_OVER, (float)0.7 ));
		BufferedImage i = bim.getSubimage(
			(counter % 10) * 58 , 0,58,111
		);
		g.drawImage ( 
			i ,
			pnt.x  + 20 , pnt.y - 100 ,
			58,111,
			null
		);
		++counter;
	}
	public void start(){}
	public void stop(){}
}

class MithrilMist extends Spell
{
	static final Image img[] = {
		ImageLoader.loadImage( "images/mist1.png" ,new JLabel("")),
		ImageLoader.loadImage( "images/mist2.png" ,new JLabel(""))
	};
	float alpha = 0.5f;
	int height = 10;
	int sizex = 50, sizey = 60;
 	
	public int getAnimDelay(){
		return 100;
	}

	public void draw( Graphics2D g , Point pnt ){
		g.drawImage ( 
			img[0],
			pnt.x + 15,
			0,
			20,height,
			null
		);
		if( height < pnt.y )
			height += 10;
		else{
			g.setComposite(AlphaComposite.getInstance( AlphaComposite.SRC_OVER, (float)alpha ));
			g.drawImage ( 
				img[1],
				pnt.x + 25 - sizex / 2,
				pnt.y - sizey,
				sizex,sizey,
				null
			);
			sizey += 10;
			alpha += 0.03f;
			if( (sizex += 10) > 200 ){ sizex = 50;sizey = 60;alpha = 0.5f;height =0;}
		}
	}
	public void start(){}
	public void stop(){}
}

class TurinThunder extends Spell
{
	static final Image img = ImageLoader.loadImage( "images/light.png" ,new JLabel(""));
	Image cloud = ImageLoader.loadImage("images/cloud.gif",new JLabel(" "));
	BufferedImage bim = new BufferedImage ( 140,180,BufferedImage.TYPE_INT_ARGB);
	int counter = 0;

	public TurinThunder(){
		bim.createGraphics().drawImage( img , 0 , 0 , 140 , 180 , null );
	}
	public int getAnimDelay(){
		return (int)(Math.random() * 500) + 100;
	}
	public void draw( Graphics2D g , Point pnt ){
		g.setComposite(AlphaComposite.getInstance( AlphaComposite.SRC_OVER, (float)0.8f));
		g.drawImage ( 
			bim.getSubimage( ( counter % 2 ) * 70 , 0 , 70,180 ),
			pnt.x - 35 , pnt.y - 180,70,180, null
		);
		g.drawImage(
			cloud,pnt.x - 65,pnt.y - 200,null
		);
		++counter;
	}
	public void start(){}
	public void stop(){}
}

class Sf extends JPanel implements Runnable
{
	Spell sp = new Ethel();
	Thread th = new Thread(this);

	public Sf(){
		setBackground(Color.black);
		th.start();
	}
	public void paintComponent(Graphics gx){
		Graphics2D g = (Graphics2D) gx;
		g.clearRect(0,0,getWidth() , getHeight());
		sp.draw(g, new Point(300,300));
	}
	public void run(){
		for(;;){
			try{th.sleep(sp.getAnimDelay());}catch (Exception ae){}
			repaint();
		}
	}
}


public class SpellTest
{
	public static void main(String arg[]){
		JFrame jf = new JFrame("baba");
		jf.setSize(750,500);
		jf.setBackground(Color.green);
		Sf  cb = new Sf ();
		jf.getContentPane().add( cb );
		jf.setVisible(true);
		jf.show();
		jf.addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                System.exit(0);
            }
        });
	}
}
