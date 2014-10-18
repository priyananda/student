import java.awt.*;
import java.awt.geom.*;
import java.io.*;
import java.awt.image. *;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

class Sf extends JPanel implements Runnable
{
	final Image img = ImageLoader.loadImage( "images/4.gif",this );
	Thread th = new Thread(this);
	public void paintComponent( Graphics g){
		g.drawImage(img , 0 , 0 , this);
	}
	public void run(){
		//try{ th.sleep(100);}catch(Exception ae){}
	}
}

public class Anim
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