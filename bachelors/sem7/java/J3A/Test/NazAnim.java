import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.awt.geom.*;
import java.io.*;
import java.util.*;
import javax.swing.*;

class ImageLoader2
{
	static HashMap cache = new HashMap();

	static Image loadImage( String path , Component cmp){
		if( cache.containsKey(path) )
			return (Image)cache.get(path);

		Image img = cmp.getToolkit().createImage(path);
		MediaTracker tracker = new MediaTracker(cmp);
        tracker.addImage(img, 0);

        try {
            tracker.waitForID(0);
            if (tracker.isErrorAny())
                System.out.println("Error loading  " + path);
        } catch (Exception ex) { ex.printStackTrace(); }
		cache.put(path , img);
        return img;
	}
}

class _Contributors extends JPanel {
	final Image umg = ImageLoader2.loadImage("images/naz.gif"  ,this);
	final BufferedImage bim = 
		new BufferedImage(umg.getWidth(null) , umg.getHeight(null), BufferedImage.TYPE_INT_ARGB);
	int counter = 0;

	public _Contributors (){
		bim.createGraphics().drawImage( umg , 0 , 0 , null);
	}
	public void paintComponent( Graphics gx){
		Graphics2D g = (Graphics2D) gx;
		g.setColor(Color.green);
		g.fillRect(0,0,getWidth(),getHeight());
		BufferedImage sub = bim.getSubimage( 
			(counter % 5) * 164,0,
			164,150
		);
		g.drawImage( sub , 200 , 200  , 82 , 80 ,this);
		++counter;
	}
} 

public class NazAnim
{
	static class MyT extends Thread
	{
		_Contributors  p;
		MyT( _Contributors  _p ){ p = _p ;}
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
		_Contributors  cb = new _Contributors ();
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
