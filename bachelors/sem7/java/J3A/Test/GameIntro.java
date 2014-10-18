package j3a.graphics;

import java.awt.*;
import java.io.*;
import java.awt.image. *;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

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
		"Tale ..."
	};

}

/*
	This is a prime example of sphagetti code. The result is one Huge class which 
	all kinds of things.But I see no use of making this code more beautifull
*/
public class GameIntro extends JPanel implements Runnable ,StoryConstants
{

	float	alpha1 = 0.5f , alpha2 = 0.0f;
	boolean up1 = true , up2 = true ;
	static	Font astar;
	static	Font font = new Font("Dialog", Font.ITALIC, 26);
	Font	normal = new Font("SansSerif" , Font.ITALIC , 40 );
	static	FontMetrics fm ;
	int		x , y , state = 0 ;
	Image	story;
	private int beginning, ending;
	private int nStrs, strH, index, yh, height;
	private Vector v = new Vector();
	private Vector cast = new Vector(members.length+3 );
	private int counter, cntMod;
	private GradientPaint gp;


	public GameIntro(Dimension size){
		setSize(size);
		try{
			astar = Font.createFont( Font.TRUETYPE_FONT, new FileInputStream("images/A.ttf")).deriveFont(200.0f);
		}catch(Exception ae){astar = normal;}
		x = getWidth() / 2 - 50 ; y = getHeight() / 2 - 100;
		new Thread(this).start();
		story = ImageLoader.loadImage("images/story.jpg" , this );
		fm = getToolkit().getFontMetrics(font);
		for (int i = 0; i < members.length; i++) {
			cast.addElement(members[i]);
		}
		cast.addElement(" "); cast.addElement(" ");
		cntMod = (ending - beginning) / cast.size() - 1;
		setSize( 100,300);
	}

	public void run(){
		for ( ; ; ){
			try{ Thread.currentThread().sleep(50);}catch(Exception ae){}
			repaint();
		}
	}
	public void paintComponent(Graphics gx){
		Graphics2D g = (Graphics2D) gx;
		switch(state){
			case 0:showCredits(g);break;
			default:showStory(g);break;
		}
	}
	public void setState(){ state ++ ; alpha1 = 0.0f;}
	
	public void showCredits(Graphics2D g){
		
		g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, 
                           RenderingHints.VALUE_ANTIALIAS_ON);
		g.clearRect( 0 , 0 , getWidth() , getHeight() );
		g.setPaint( new GradientPaint(0,0,Color.black , 2000,2000,Color.blue));
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
		g.setFont(astar);
		g.drawString( "A" , x , y);
		
		if( up2 ){
			alpha2 +=  0.03f ;
			if ( alpha2 > 0.9f ){  up2 = false; alpha2 = 1.0f; }
		}else{
			alpha2 -=  0.03f ;
			if ( alpha2 <= 0 ){  up2 = true; alpha2 = 0f;}
		}
		g.setComposite(AlphaComposite.getInstance( AlphaComposite.SRC_OVER, (float)alpha2 ));
		g.setFont(normal);
		g.drawString( "Harish JP & Priyananda Shenoy P" , x - 180  , y + 50);
		g.drawString( "Creation" , x - 20  , y + 120);
	}
	public void showStory(Graphics2D g){
		if( alpha1 < 1.0f )	alpha1 += 0.005f;
		g.setComposite(AlphaComposite.getInstance( AlphaComposite.SRC_OVER, (float)alpha1 ));
		g.drawImage( story , 0 , 0 , getWidth() , getHeight() , this );
		render( getWidth() , getHeight() , (Graphics2D)g);
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
		g2.setPaint(gp);
		double remainder = counter%cntMod;
		double incr = 1.0-remainder/cntMod;
		incr = incr == 1.0 ? 0 : incr;
		int y = (int) (incr * (strH-5));

		if (index >= cast.size()) {
			y = yh + y; 
		} else {
			y = yh = height - v.size() * strH + y;
		}
		for (int i = 0; i < v.size(); i++) {
			String s = (String) v.get(i);
			g2.drawString(s, w/2-fm.stringWidth(s)/2, y += strH);
		}
	}





	static private class __Temp extends KeyAdapter{
		GameIntro g;
		__Temp(GameIntro _g){ g = _g;}
		public void keyPressed(KeyEvent e){
			g.setState();
		}
	}
	public static void main(String [] arg)
	{
		JFrame w = new JFrame();
		w.setVisible(false);
		GameIntro gm =  new GameIntro(new Dimension(700,700));
		w.getContentPane().add(gm );
		w.setBackground( Color.black );
		w.addMouseListener( new MouseAdapter(){
			public void mouseClicked( MouseEvent we){
				System.exit(0);
			}
		});
		w.requestFocus();

		
		w.addKeyListener( new __Temp(gm));
		w.setSize( Toolkit.getDefaultToolkit().getScreenSize() );
		w.setVisible(true);
	}
}