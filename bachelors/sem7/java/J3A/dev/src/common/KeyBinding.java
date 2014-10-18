/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.model;
import java.io.*;
import java.util.*;


public class KeyBinding implements KeyConstants
{
	/** Default key bindings */
	private static int keys[] = {
		38,40,37,39, // movement
		112, //help
		27,//quit
		77,70,84,66,69, //spells
		10,//cheat
		87,83,65,68 // scroll
	};
	static private void loadConf(){
		try{
			File f =  new File("conf/key.cfg" );
			if( !f.exists() ) return;
			Properties prop = new Properties();
			prop.load( new FileInputStream( f ) );
			for ( int i = 0 ; i < NUM_KEYS ; ++i ){
				String str = prop.getProperty( strings[i]);
				if(str == null || str.trim().length() <= 0 ) continue;
				 keys[i] = Integer.parseInt(str);
			}
		}catch(Exception ae){
			System.out.println( "" + ae );
		}
	}

	static{ loadConf(); }

	public static int getKey(int keyCode){
		for( int i = 0 ; i < NUM_KEYS ; ++i )
			if( keyCode == keys[i] ) return i;
		return -1;
	}
}