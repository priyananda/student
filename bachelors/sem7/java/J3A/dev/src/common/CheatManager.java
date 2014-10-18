/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.model;
import java.util.*;
import java.io.*;

public class CheatManager implements CheatConstants
{
	static String keys[] = new String[NUM_CHEATS];
	static private void loadConf(){
		try{
			File f =  new File("conf/cheat.cfg" );
			if( !f.exists() ) return;
			Properties prop = new Properties();
			prop.load( new FileInputStream( f ) );
			for ( int i = 0 ; i < NUM_CHEATS ; ++i ){
				String str = prop.getProperty(codeStrings[i]);
				if(str == null || str.trim().length() <= 0 ) continue;
					keys[i] = str;
			}
		}catch(Exception ae){
			System.out.println( "" + ae );
		}
	}
	static{ loadConf(); }

	public static int getCheatCode(String code){
		for( int i = 0 ; i < NUM_CHEATS ; ++i )
			if( keys[i] != null && keys[i].compareToIgnoreCase(code ) == 0) return i;
		return -1;
	}
}