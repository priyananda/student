import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;
import javax.imageio.*;
import java.awt.image.*;

class ImageLoader
{
	static Image loadImage( String path , Component cmp){
		Image img = cmp.getToolkit().createImage(path);
		MediaTracker tracker = new MediaTracker(cmp);
        tracker.addImage(img, 0);
        try {
            tracker.waitForID(0);
            if (tracker.isErrorAny()) {
                System.out.println("Error loading  " + path);
            }
        } catch (Exception ex) { ex.printStackTrace(); }
        return img;
	}
}

class Surface extends JPanel implements Runnable{
	Image img;
	int size = 30;
	Point loc;

	public Surface( Point _loc){
		setSize(500,500);
		Thread t = new Thread( this );
		img = ImageLoader.loadImage( "images/4.gif" , this);
		loc = _loc;
				t.start();
	}
	public void paintComponent( Graphics gx){
		super.paintComponent(gx);
		Graphics2D g = (Graphics2D) gx;
		g.setColor(Color.green);
		g.fillRect(0,0,getWidth(),getHeight());
		g.setComposite(AlphaComposite.getInstance( AlphaComposite.SRC_OVER, 0.3f ));
		g.drawImage( img, loc.x - size / 2 , loc.y - size / 2 , size , size , this); 
		g.drawImage( img, loc.x - size / 4 , loc.y - size / 4 , size / 2 , size / 2 , this); 
	}
	public void run(){
		for(;;){
			//y{ Thread.currentThread().sleep(100); }catch(Exception ae){}
			//ze += 4;
			repaint();
		}
	}
};
class Transparency
{
	public static BufferedImage makeColorTransparent(Image im)
	{
	    ImageFilter filter = new RGBImageFilter()
		{
			public final int filterRGB(int x, int y, int rgb)
			{
				if ( rgb == -16777216 )
					return 0;
				else
				  	return rgb;
			}
	    };
		BufferedImage bi = new BufferedImage(
			im.getWidth(null),im.getHeight(null),
			BufferedImage.TYPE_INT_ARGB
		);
		bi.createGraphics().drawImage(im,0,0,null );
        FilteredImageSource ip = new FilteredImageSource(
			bi.getSource(),
			filter
		);
		Image ret = Toolkit.getDefaultToolkit().createImage( ip );
		bi.createGraphics().drawImage(ret,0,0,null );
		return bi;
    }
}
public class Test extends JFrame{
	Surface s;

	public Test(){
		super("Testing 1 2 3 .." );
		setVisible(false);
		setSize(500,500);
		Container cp = getContentPane();
		s = new Surface( new Point(100,100));
		cp.add( s );
		addWindowListener( new WindowAdapter() {
			public void windowClosing( WindowEvent we ){
				System.exit(0);
			}
		});
		setVisible(true);
	}
	public static void main( String [] argv){
		//new Test().show();
		TestImage();
	}
	public static void TestImage()
	{
		try{
			String [] images =
			{
				"sof.png",
				"cloak1.png",
				"cloak2.png",
				"cloak3.png",
				"cloak4.png",
				"cloak5.png",
				"cloak6.png",
				"trap1.png",
				"trap2.png",
				"trap3.png",
				"trap4.png",
				"trap5.png",
				"trap6.png",
				"trap7.png",
				"trap8.png",
				"trap9.png",
				"neck1.png",
				"neck2.png",
				"neck3.png",
				"neck4.png",
				"neck5.png",
				"neck6.png",
				"neck7.png",
				"neck8.png",
				"neck9.png",
				"neck10.png"
			};
			String[] formatNames = ImageIO.getWriterFormatNames();
			for( int i = 0 ; i < formatNames.length ; ++ i )
			{
				System.out.println( formatNames[i] );
			}
			//for( int i = 0 ; i < images.length ; ++ i )
			//{
			//	Image img = ImageLoader.loadImage( images[i] , new JLabel("") );
			//	BufferedImage bim = Transparency.makeColorTransparent(img);
			//	ImageIO.write( bim , "gif" , new File("out/" + images[i] + ".gif" ));
			//}
		}
		catch(Exception e){System.out.println(""+e);}
	}
};