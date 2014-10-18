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

/**
 *	Is this fair? Using an interface as a enum ?
 *  Well , java does it , ( SwingConstants )
 */
public class SpellData
{
	public static String letters[];
	public static String spellNames[];
	public static int spellRanges[];
	public static int spellDamages[];

	static
	{
		LoadConfigFile();
	}

	private static void LoadConfigFile()
	{
		j3a.graphics.ConfigFile cf = j3a.graphics.ConfigFileInterpreter.Parse(
			"conf//spells.cfg"
		);
		if( cf == null )
		{
            return;
		}

		int count = cf.GetRowCount();

		letters = new String[count];
		spellNames = new String[count];
		spellRanges = new int[count];
		spellDamages = new int[count];

		for( int i = 0 ; i < count ; ++i )
		{
			spellNames[i] = cf.GetItem(i,0);
			letters[i] = cf.GetItem(i,1);
			spellRanges[i] = Integer.parseInt( cf.GetItem(i,2) );
			spellDamages[i] = Integer.parseInt( cf.GetItem(i,3) );
		}
	}
}