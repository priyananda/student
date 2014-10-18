/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.graphics;

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.image.*;
import java.awt.event.*;
import java.util.*;
import java.net.*;

public class HelpDialog extends JDialog implements HyperlinkListener
{
	JEditorPane edit = null;
	public HelpDialog( JFrame owner)
	{
		super(owner,"Enter new Map" , true);
		setSize( 600,400 );
		try{
			URL index = new URL(
				"file:" + System.getProperty("user.dir") + "/manual/index.html"
			);
			edit = new JEditorPane(index);
		}catch(Exception ae){}
		edit.setEditable(false);
		edit.addHyperlinkListener(this);
		JScrollPane jsp = new JScrollPane( edit);
		getContentPane().add(jsp);
		setDefaultCloseOperation( DISPOSE_ON_CLOSE );
	}

	public void hyperlinkUpdate(HyperlinkEvent e)
	{
		try{
			if (e.getEventType() == HyperlinkEvent.EventType.ACTIVATED)
				edit.setPage( e.getURL() );
		}catch(Exception ae){}
	}
	public static void main(String [] argc){
		HelpDialog  hd = new HelpDialog(new JFrame());
		hd.show();
	}
}