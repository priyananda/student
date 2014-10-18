import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.awt.geom.*;
import java.io.*;
import java.util.*;
import javax.swing.*;


class Contributors extends JPanel {
	final Image umg = ImageLoader.loadImage("images/fire.gif"  ,this);
	final BufferedImage bim = 
		new BufferedImage(umg.getWidth(null) , umg.getHeight(null), BufferedImage.TYPE_INT_ARGB);
	int size[] = { 120, 60 , 120,60 };
	int rotate[] = { 0,0,180,180 };
	AffineTransform af = new AffineTransform();
	int counter = 0;

	public Contributors (){
		bim.createGraphics().drawImage( umg , 0 , 0 , null);
	}
	public void paintComponent( Graphics gx){
		Graphics2D g = (Graphics2D) gx;
		g.setColor(Color.green);
		g.fillRect(0,0,getWidth(),getHeight());
		//af.shear( rotate[counter % 4] );
		g.setTransform(af);
		g.drawImage( bim , 200 , 200 - size[counter % 4] , 60 , size [counter % 4] ,this);
		++counter;
	}
} 

public class Img
{
	static class MyT extends Thread
	{
		Contributors  p;
		MyT( Contributors  _p ){ p = _p ;}
		public void run(){
			for(;;){
				try{ sleep(160); }catch( Exception ae){}
				p.repaint();
			}
		}
	}
	public static void main(String [] argv){
		JFrame jf = new JFrame("baba");
		jf.setSize(750,500);
		Contributors  cb = new Contributors ();
		jf.getContentPane().add( cb );
		jf.setVisible(true);
		jf.show();
		jf.addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                System.exit(0);
            }
        });
		new MyT( cb ).start();
	}
}
