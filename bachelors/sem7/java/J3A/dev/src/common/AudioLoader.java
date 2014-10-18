/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.graphics;

import java.util.*;
import java.applet.*;
import java.net.*;

/**
 * Cached Implementation of Audio Loading.
 * NOTE: default behaviour is caching unlike
 * ImageLoader
 */
public class AudioLoader
{
	static HashMap cache = new HashMap();
	/**
	 * fileName is relative path from audio subdirectory
	 */
	public static AudioClip loadAudio( String fileName , int cache_policy)
	{
		AudioClip ac = null;
		if( cache.containsKey(fileName) )
			return (AudioClip)cache.get(fileName);
		try{
			String dir = System.getProperty("user.dir");
			URL url = new URL( "file:///" + dir + "/audio/" + fileName);
			ac = Applet.newAudioClip(url);
		}
		catch(Exception ae){}
		if( cache_policy == 1 )
			cache.put( fileName , ac );
		return ac;
	}
	/**
	 *	Loads audio with caching
	 */
	public static AudioClip loadAudio( String name )
	{
		return loadAudio( name , 1 );
	}
}