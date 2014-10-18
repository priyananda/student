/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.graphics;

import javax.swing.*;
import java.awt.*;
import java.awt.image.*;
import java.awt.event.*;
import java.util.*;

/**
 * Preloads a few images and sounds with some fancy
 * progress bars
 */
public class MediaPreloader
{
	static final String images[] = {
		"hp10.gif","hp2.gif",
		"hp5.gif" , "wall-sprite.gif" , "story.jpg",
		"_story.jpg" 
	};

	public MediaPreloader(JFrame parent){
		JProgressBar progressBar = new JProgressBar();
		progressBar.setMaximum(images.length);
		JLabel lb = new JLabel(" ");
		JDialog dialog = new JDialog( parent , "Loading all media");
		Container cp = dialog.getContentPane();
		cp.setLayout( new GridLayout(2,1));
		cp.add( lb );
		cp.add(	progressBar);
		dialog.setSize(200,100);
		dialog.setLocation( 200,200);
		dialog.setVisible(true);
		for (int i = 0 ; i < images.length ;++i ){
			lb.setText("Loading " + images[i]);
			ImageLoader.loadImage( "images/" + images[i]);
			progressBar.setValue(i);
			try{ Thread.currentThread().sleep(100); }catch(Exception ae){}
		}
		dialog.setVisible(false);
	}
}