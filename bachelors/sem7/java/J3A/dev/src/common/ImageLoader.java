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

public class ImageLoader
{
	static final int NO_CACHE = 0x01;
	static HashMap cache = new HashMap();

	public static Image loadImage( String path ){
		return loadImage(path,new JLabel("") , 0);
	}
	public static Image loadImage( String path , int flag){
		return loadImage(path,new JLabel("") , flag);
	}
	public static Image loadImage( String path , Component cmp ){
		return loadImage(path,cmp, 0);
	}
	public static Image loadImage( String path , Component cmp , int flag){
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
		if( ( flag & NO_CACHE ) == 0 )
			cache.put(path , img);
        return img;
	}
}
