import java.awt.*;
import java.io.*;
import java.awt.image. *;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

public class ImageLoader
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
        }catch (Exception ex) { ex.printStackTrace(); }
		cache.put(path , img);
        return img;
	}
}
