import java.awt.*;
import java.awt.geom.*;
import java.util.*;
import javax.swing.*;

public class PowerUp extends JPanel
{
	final int PRESENT = 1 , ABSENT = 0;
	final int HP2 = 0, HP5 = 1, HP10 = 2;
	int regenTime;
	Image img[] = {
		ImageLoader.loadImage("images/fire.gif" , this),
		ImageLoader.loadImage("images/fire2.gif" , this)
	};
	AffineTransform at = new AffineTransform();
	int rotate = 0;
	Point loc;

	public PowerUp(Point _loc){ loc = _loc;}
	public void paintComponent( Graphics gx){
		super.paintComponent(gx);
		gx.clearRect(0,0,getWidth() , getHeight());
		Graphics2D g = (Graphics2D) gx;
		g.setComposite(AlphaComposite.getInstance( AlphaComposite.SRC_OVER, 0.75f ));
		g.drawImage(img[ rotate % 2 ],loc.x - 25 ,loc.y + 120 - rotate, 64 , rotate ,  this);
		if( ( rotate += 15) >= 120 )
			rotate = 30;
	}
	static class AnimThread extends Thread
	{
		int delay;
		JPanel panel;
		AnimThread(JPanel p , int _d){
			super("anim1");
			delay = _d;
			panel = p;
		}
		public void run(){
			for(;;){
				try{ sleep(delay) ; }catch(Exception ae){}
				panel.repaint();
			}
		}
	};
	public static void main(String []arg){
		JFrame f = new JFrame();
		PowerUp pu = new PowerUp(new Point(300,100));
		f.setBackground(Color.green);
		f.getContentPane().add( pu , BorderLayout.CENTER );
		new AnimThread(pu,200).start();
		f.setSize(500,500);
		f.pack();
		f.addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                System.exit(0);
            }
        });
		f.show();
	}
};