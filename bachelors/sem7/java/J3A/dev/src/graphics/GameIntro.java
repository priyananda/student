/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.graphics;

import java.awt.*;
import java.io.*;
import java.awt.image. *;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
import java.net.*;
import java.applet.*;

/**
 * Another stupidly named class
 */
interface StoryConstants
{
	String members[] = {
		"It was an age",
		"of war. An age of ",
		"sorrow, an age of cruelty.",
		"It was also the age of great bravery.",
		" ",
		"The guiles of Sauron had wrecked",
		"the trust of the Numenorians in ",
		"the Valar.There were ferments of ",
		"dissent in the Numenorian minds.",
		"'War' , the hounds cried , 'Blood'",
		"shouted the wolves.",
		"   Not all were swayed by the cunning",
		"of Sauron. There were those who kept",
		"their faith in the Valar. The faithfull",
		"decided to forsake Numenor and seek the",
		"path to Middle Earth.Their",
		"Tale unfolds "
	};
}

/**
	This is a prime example of sphagetti code. The result is one Huge class which
	all kinds of things.But I see no use of making this code more beautifull
*/
public class GameIntro extends JPanel implements Runnable ,StoryConstants
{

	float	alpha1 = 1.0f , alpha2 = 0.0f;
	boolean up1 = true , up2 = true ;
	static	Font astar;
	static	Font font = new Font("Dialog", Font.ITALIC, 26);
	Font	normal = new Font("SansSerif" , Font.ITALIC , 40 );
	static	FontMetrics fm ;
	int		mx , my , state = 0 , delay = 50;
	private Image story , name , intro;
	private int beginning, ending;
	private int nStrs, strH, index, yh, height;
	private Vector v = new Vector();
	private Vector cast = new Vector(members.length+3 );
	private int counter, cntMod;
	private GradientPaint gp;
	private Thread mt;
	static private AudioClip clip;

	public GameIntro(Dimension size){
		setSize(size);

		story = ImageLoader.loadImage("images/story.jpg" , this );
		name = 	ImageLoader.loadImage ("images/_story.jpg" , this );
		intro = ImageLoader.loadImage("images/intro.jpg" , this );

		mx = getWidth()	 / 2 - intro.getWidth(null)/2;
		my = getHeight() / 2 - intro.getHeight(null)/2;

		fm = getToolkit().getFontMetrics(font);

		for (int i = 0; i < members.length; i++)
			cast.addElement(members[i]);
		cast.addElement(" ");
		cast.addElement(" ");
		cntMod = (ending - beginning) / cast.size() - 1;
		(mt = new Thread(this)).start();
		clip = AudioLoader.loadAudio( "bg/bgsound.wav" ,0);
		clip.loop();
	}

	public void run(){
		for ( ; ; ){
			try{ Thread.currentThread().sleep(delay);}catch(Exception ae){}
			if( state == 1 )step(getWidth(),getHeight());
			repaint();
		}
	}
	public void paintComponent(Graphics gx){
		Graphics2D g = (Graphics2D) gx;
		switch(state){
			case 0:showCredits(g);break;
			case 1:showStory(g);break;
			default:showName(g);break;
		}
	}
	public void setState(){
		state ++ ; alpha1 = 0.0f; delay = (delay == 50 ? 500 :50);
	}

	public void showCredits(Graphics2D g){
		g.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
						   RenderingHints.VALUE_ANTIALIAS_ON);
		g.fillRect( 0 , 0 , getWidth() , getHeight() );
		g.setColor(Color.white);

		if( up1 ){
			alpha1 +=  0.03f ;
			if ( alpha1 > 0.9f ){  up1 = false; alpha1 = 1.0f; }
		}else{
			alpha1 -=  0.03f ;
			if ( alpha1 <= 0 ){  up1 = true; alpha1 = 0f;}
		}
		g.setComposite(AlphaComposite.getInstance( AlphaComposite.SRC_OVER, (float)alpha1 ));
		g.drawImage ( intro, mx , my , null);
	}
	public void showStory(Graphics2D g){
		g.drawImage( story ,  0 , 0  , getWidth() , getHeight() , this );
		render( getWidth() , getHeight() , (Graphics2D)g);
	}
	public void showName(Graphics2D g){
		super.paintComponent(g);
		g.setColor(Color.black);
		g.fillRect( 0 , 0 , getWidth() , getHeight() );
		if ( alpha1 < 0.93f ) alpha1 += 0.01f;
		g.setComposite(AlphaComposite.getInstance( AlphaComposite.SRC_OVER, (float)alpha1 ));
		mx = getWidth()	 / 2 - name.getWidth(null)/2;
		my = getHeight() / 2 - name.getHeight(null)/2;
		g.drawImage( name , mx , my , name.getWidth(null), name.getHeight(null) , this );
	}
	public void step(int w, int h) {
		if (counter++%cntMod == 0) {
			if (index < cast.size()) {
				v.addElement(cast.get(index));
			}
			if ((v.size() == nStrs || index >= cast.size()) && v.size() != 0) {
				v.removeElementAt(0);
			}
			++index;
		}
	}
	public void render(int w, int h, Graphics2D g2) {
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
						   RenderingHints.VALUE_ANTIALIAS_ON);
		g2.setFont(font);
		g2.setComposite(AlphaComposite.getInstance( AlphaComposite.SRC_OVER, 0.5f ));
		g2.setPaint(gp);
		double remainder = counter%cntMod;
		double incr = 0.8-remainder/cntMod;
		incr = incr == 0.8 ? 0 : incr;
		int y = (int) (incr * (strH));

		if (index >= cast.size())
			y = yh + y;
		else
			y = yh = height - v.size() * strH + y;

		for (int i = 0; i < v.size(); i++) {
			String s = (String) v.get(i);
			g2.drawString(s, w/2-fm.stringWidth(s)/2, y += strH);
		}
	}
	public void reset(int w, int h) {
		v.clear();
		strH = (int) (fm.getAscent()+fm.getDescent());
		nStrs = (h-40)/strH + 1;
		height = strH * (nStrs-1) + 48;
		index = 0;
		gp = new GradientPaint(0,h/2,Color.yellow,0,h+20,Color.black);
		counter = 0;
	}
	static private class KeyHandler extends KeyAdapter{
		private GameIntro g;
		private JFrame f;
		KeyHandler (JFrame _f,GameIntro _g){ f = _f; g = _g;}
		public void keyPressed(KeyEvent e){
			g.setState();
			if( g.state == 3 ){
				f.setVisible(false);
				f = null;
				clip.stop();
				ChooserUI gui = new ChooserUI();
				gui.show();
			}
		}
	}
	public static void main(String [] arg)
	{
		try
		{

			JFrame w = new JFrame();
			new MediaPreloader(w);
			if( arg.length > 0 ){
				ChooserUI gui = new ChooserUI();
				gui.show();
				return;
			}
			Dimension sz = Toolkit.getDefaultToolkit().getScreenSize();
			w.setVisible(false);
			w.dispose();
			w.setUndecorated(true);
			GameIntro gm =  new GameIntro(sz);
			w.getContentPane().add(gm );
			gm.reset(sz.width,sz.height);
			w.setBackground( Color.black );
			w.addMouseListener( new MouseAdapter(){
				public void mouseClicked( MouseEvent we){
					System.exit(0);
				}
			});
			w.requestFocus();
			w.addKeyListener( new KeyHandler(w,gm));
			w.setSize( sz );
			w.setVisible(true);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}