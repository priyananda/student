/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.graphics;

import java.awt.*;
import javax.swing.*;
import java.net.*;
import java.applet.*;

public class SplashScreen extends JWindow{
	public SplashScreen(Frame parent){
		super(parent);
		setVisible(false);
		setSize(500,300);
		Dimension dm = Toolkit.getDefaultToolkit().getScreenSize();
		setLocation( dm.width / 2 - 250 , dm.height / 2 - 150 );
		getContentPane().add( new JLabel(new ImageIcon("images/splash.gif")) );
		setVisible(true);
		//try{Thread.currentThread().sleep(2000);}catch(Exception a){}
		setVisible(false);
	}
}