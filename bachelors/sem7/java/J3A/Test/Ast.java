import java.awt.*;
import java.awt.geom.*;
import java.io.*;
import java.awt.image. *;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

class Sf extends JPanel implements Runnable
{
	public static final Image img = ImageLoader.loadImage("images/asteroid.gif", new Label(""));
	BufferedImage bim = new BufferedImage(320 , 80 , BufferedImage.TYPE_INT_ARGB);
	Graphics2D gr = bim.createGraphics();
	Thread th = new Thread(this);
	int counter = 0;
	int position = 200;

	public Sf(){
		setBackground(Color.green);
		gr.drawImage(img,0,0,320,80,this);
		th.start();
	}
	public void paintComponent(Graphics gx){
		Graphics2D g = (Graphics2D) gx;
		g.clearRect(0,0,getWidth() , getHeight());
		BufferedImage clip = bim.getSubimage( 32 * ( counter % 10 ), 0 , 32 , 80 ); 
		g.drawImage( clip,100 ,500 - position , 32 , 80 ,this);
	}
	public void run(){
		for(;;){
			try{th.sleep(100);}catch (Exception ae){}
			repaint();
			++counter;
			position -= 5;
			if( position < 0 )  position = 500;
		}
	}
}

public class Ast
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