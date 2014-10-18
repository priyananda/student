/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.graphics;

import java.awt.*;
import java.applet.*;
import java.io.*;
import java.awt.image. *;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
import j3a.model.*;

interface MeaningLessConstants
{
	String spellIcons[] = {
		"images/ui/m.gif" , "images/ui/f.gif" ,
		"images/ui/t.gif" , "images/ui/b.gif" ,
		"images/ui/e.gif"
	};
	AudioClip tauntAudio[] = {
		AudioLoader.loadAudio("taunts/help.wav"),
		AudioLoader.loadAudio("taunts/hurt.wav"),
		AudioLoader.loadAudio("taunts/laugh.wav"),
		AudioLoader.loadAudio("taunts/throw.wav"),
		AudioLoader.loadAudio("taunts/whatever.wav")
	};
	String tauntIcons[] = {
		"images/ui/1.jpg" ,"images/ui/3.jpg" ,
		"images/ui/2.jpg" ,"images/ui/4.jpg" ,
		"images/ui/5.jpg"
	};

}
/**
 * This class represents the HUD of the game
 * Basically it is a hyped up JPanel
 */
public class HUDPanel extends JPanel implements MeaningLessConstants,MouseListener
{
	static final Image img = ImageLoader.loadImage("images/hud.jpg");
	static final BufferedImage bim;
	static final Font bigFont = new Font( "SansSerif",Font.BOLD|Font.ITALIC,20);

	JPanel pHealth,pMsg,pAction;
	JLabel lHealth;
	JLabel lMsg,lSpell;
	MyButton spells[] = new MyButton[5];
	MyButton taunts[] = new MyButton[5];
	JLabel spellCount[] = new JLabel[5];
	public int curr_spell = -1;

	static {
		bim = new BufferedImage(
			img.getWidth(null) , img.getHeight(null) ,
			BufferedImage.TYPE_INT_RGB
		);
		bim.createGraphics().drawImage( img,0,0,null);
	}
	/**
	 * When I draw it , I basically draw the image
	 */
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		g.drawImage( bim, 0,0,getWidth() , getHeight(),this);
	}
	public HUDPanel(){
		newComponents();
		setProperties();
		layoutComponents();
	}
	private void newComponents(){
		pHealth =	new JPanel();
		pMsg =		new JPanel();
		pAction =	new JPanel();
		lHealth =	new JLabel( "" + GameConstants.DEFAULT_HP , JLabel.CENTER );
		lMsg =		new JLabel( "   " , JLabel.CENTER);
		lSpell =		new JLabel( "   " , JLabel.CENTER);
		for( int i = 0 ; i < spells.length ; ++i ){
			spells[i] = new MyButton( new ImageIcon(spellIcons[i]) );
			spells[i].addMouseListener(this);
			spells[i].setToolTipText(j3a.model.SpellData.spellNames[i]);
			spellCount[i] = new JLabel("0",JLabel.CENTER);
		}
		for( int i = 0 ; i < taunts.length ; ++i ){
			taunts[i] = new MyButton( new ImageIcon(tauntIcons[i]));
			taunts[i].addMouseListener(this);
		}
	}
	private void setProperties(){
		setOpaque(true);
		pHealth.setSize(200 , pHealth.getHeight());
		pHealth.setOpaque(false);
		pMsg.setOpaque(false);
		pAction.setOpaque(false);
		lHealth.setOpaque(false);
		lHealth.setBorder(BorderFactory.createLineBorder(Color.yellow,3) );
		lHealth.setForeground(Color.orange);
		lMsg.setBackground( Color.black);
		lMsg.setForeground( Color.yellow);
	}
	public void layoutComponents(){
		setLayout ( new BorderLayout(30,10) );

		layHealth();
		layMsg();
		layAction();

		add(pHealth ,BorderLayout.WEST) ;
		add(pMsg , BorderLayout.NORTH);
		add(pAction , BorderLayout.CENTER);

	}
	private void layHealth(){
		pHealth.setLayout( new GridLayout(3,2));
		pHealth.add( new JLabel(" ") );
		pHealth.add( new JLabel(" Health ") );
		pHealth.add( new JLabel(" ") );
		pHealth.add( lHealth );
		pHealth.add( new JLabel(" ") );
		pHealth.add( new JLabel(" ") );
	}
	private void layMsg(){
		pMsg.setLayout( new GridLayout(1,4));
		pMsg.add( new JLabel("Message:"));
		pMsg.add( lMsg );
		pMsg.add( new JLabel("Selected Spell:"));
		pMsg.add( lSpell );
	}
	private void layAction(){
		pAction.setLayout( new GridLayout(3,12));
		for ( int i = 0 ; i < 12; i++)
			pAction.add(new JLabel(" "));

		for( int i = 0 ; i < spells.length ; ++i )
			pAction.add(spells[i]);
		for( int i = 0 ; i < taunts.length ; ++i )
			pAction.add(taunts[i]);
		pAction.add(new JLabel(" "));
		pAction.add(new JLabel(" "));
		for ( int i = 0 ; i < 5; i++)
			pAction.add(spellCount[i]);
		String temp[] = { "Help","Hurt","Laugh","Throw","What" };
		for ( int i = 0 ; i < 5; i++)
			pAction.add(new JLabel(temp[i],JLabel.CENTER));
		pAction.add(new JLabel(" "));
		pAction.add(new JLabel(" "));
	}
	public void renderHuman(Human h){
		lHealth.setText( ""+ h.hp );
		for( int i = 0 ; i < h.spells.length; ++i )
			spellCount[i].setText(" "+h.spells[i] + " ");
	}
	public void setMessage(String message){
		lMsg.setText( message );
	}
	public int getSpell(){
		return curr_spell;
	}
	public void setSpell(int sp){
		curr_spell = sp;
		lSpell.setText( j3a.model.SpellData.spellNames[sp]);
	}
	public void mouseClicked( MouseEvent ae){
		MyButton butt = (MyButton)ae.getSource();
		for (int i = 0 ;i < spells.length ;++i ){
			if( butt == spells[i]){
				setSpell(i);
				break;
			}
		}
		for (int i = 0 ;i < taunts.length ;++i ){
			if( butt == taunts[i]){
				tauntAudio[i].play();
				break;
			}
		}
	}
	public void mousePressed(MouseEvent me){}
	public void mouseReleased(MouseEvent me){}
	public void mouseEntered(MouseEvent me){}
	public void mouseExited(MouseEvent me){}

	public static class MyButton extends JPanel
	{
		public MyButton( String t){
			this(new JLabel(t, JLabel.CENTER));
			setBorder( BorderFactory.createLineBorder(Color.blue,1));
		}
		public MyButton( ImageIcon icon ){
			this(new JLabel(icon));
		}
		private MyButton(JLabel l){
			setLayout( new GridLayout(1,1,0,0));
			l.setIconTextGap(0);
			add(l);
			setOpaque(false);
		}
	}
}