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

/*
public class TextureConfig
{
	static Vector ;
	static{
		init();
	}
	private static void init(){
		try{
			FileInputStream fis = new FileInputStream("conf/textures.cfg");
			BufferedReader read = new BufferedReader( new InputStreamReader(fis) );
			String str;
			while( (str = read.readLine()) != null ){
				if( str.startsWith("#" )) continue;
				tokenize(str);
			}
		}catch(Exception ae){
			JOptionPane.showMessageDialog ( null , "Unable to read textures" , "Aborting" , 0);
		}
	}
	private static void tokenize( String str ){
		StringTokenizer tok = new StringTokenizer(str , " ");
		String command = tok.nextToken();
		String name = tok.nextToken();
		String type = tok.nextToken();
		String path = tok.nextToken();
		if( command.compareToIgnoreCase( "AddTexture" ) )
			addTexture( type , path );
		if( command.compareToIgnoreCase( "RemoveTexture" ) )
			remTexture( type , path );
	}
}
*/