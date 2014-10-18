/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.model;
import java.awt.*;

/**
 * What crap is this? Shenoy's example of meaningless
 * interfaces. Just a bunch of static final public thingies
 *
 *	Q: Where are interfaces used?
 *  A: Instead of typing "public static final" use interfaces !!
 */
public class MonsterData
{
	public static String monsterNames[];
	public static String soundPaths[];
	public static int monsterHealth[];
	public static int monsterAttack[];
	public static int animDelays[];
	public static Dimension imageSizes[];
	public static int imageCount[];
	public static String imagePaths[];

	static
	{
		LoadConfigFile();
	}

	private static void LoadConfigFile()
	{
		j3a.graphics.ConfigFile cf = j3a.graphics.ConfigFileInterpreter.Parse(
			"conf//monsters.cfg"
		);
		if( cf == null )
		{
            return;
		}

		int count = cf.GetRowCount();

		monsterNames = new String[count];
		soundPaths = new String[count];
		monsterHealth = new int[count];
		monsterAttack = new int[count];
		animDelays = new int[count];
		imageSizes = new Dimension[count];
		imageCount = new int[count];
		imagePaths  = new String[count];

		for( int i = 0 ; i < count ; ++i )
		{
			monsterNames[i] = cf.GetItem(i,0);
			soundPaths[i] = j3a.graphics.GameConstants.AUDIO_SUBDIR + cf.GetItem(i,8);
			monsterHealth[i] = Integer.parseInt( cf.GetItem(i,1) );
			monsterAttack[i] = Integer.parseInt( cf.GetItem(i,2) );
			animDelays[i] = Integer.parseInt( cf.GetItem(i,3) );
			imageSizes[i] = new Dimension(
				Integer.parseInt( cf.GetItem(i,4) ),
				Integer.parseInt( cf.GetItem(i,5) )
			);
			imageCount[i] = Integer.parseInt( cf.GetItem(i,6) );
			imagePaths[i] = j3a.graphics.GameConstants.IMAGE_SUBDIR + cf.GetItem(i,7);
		}
	}
}