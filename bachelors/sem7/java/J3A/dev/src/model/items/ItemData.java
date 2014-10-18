/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.model;
import java.awt.*;
import java.util.*;
import j3a.graphics.*;

public class ItemData
{
	public static String itemNames[];
	public static String itemLetters[];
	public static String itemImagePaths[];

	static
	{
    	LoadConfigFile();
	}

	private static void LoadConfigFile()
	{
		j3a.graphics.ConfigFile cf = j3a.graphics.ConfigFileInterpreter.Parse(
			"conf//items.cfg"
		);
		if( cf == null )
		{
            return;
		}

		int count = cf.GetRowCount();

		itemNames = new String[count];
		itemLetters = new String[count];
		itemImagePaths  = new String[count];

		for( int i = 0 ; i < count ; ++i )
		{
			itemNames[i] = cf.GetItem(i,0);
			itemLetters[i] = cf.GetItem(i,1);
			itemImagePaths[i] = j3a.graphics.GameConstants.IMAGE_SUBDIR + cf.GetItem(i,2);
		}
	}
}