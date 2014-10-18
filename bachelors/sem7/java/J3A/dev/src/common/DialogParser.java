/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.model;

import java.util.*;
import java.awt.*;
import java.io.*;
import j3a.model.*;


class NoStateException extends Exception{}

class State
{
	String text;
	HashMap links = new HashMap();// "p1" -> <state-object>

	State(){}
	public void addLink( String txt , State st ){
		links.put ( txt , st );
	}
	public String toString(){
		return text;
	}
	public void print(){
		System.out.println( "-------------------------" );
		System.out.println( "Text :" + text );
		System.out.println( "Links->" );
		Iterator iter = links.keySet().iterator();
		while( iter.hasNext() ){
			String key = (String) iter.next();
			System.out.println( key + " :: " + links.get( key ) );
		}
	}
}

public class DialogParser
{
	HashMap states = new HashMap();// "A" -> <state-object>
	HashMap texts = new HashMap() ;// "p1" -> <String>

	public DialogParser( String fileName ) throws Exception{
		if( fileName.indexOf("maps/") == -1 ) fileName = "maps/" + fileName;
		FileInputStream fis = new FileInputStream(fileName);
		Properties prop = new Properties ();
		prop.load( fis );

		parseText( prop );
		parseState( prop );
	}
	private void parseText(Properties prop){
		int idx = 1;
		while(true){
			String val = prop.getProperty( "p" + idx );
			if( val == null || val.length() <= 0 )break;
			texts.put( "p" + idx , val );
			++idx;
		}
	}
	private void parseState(Properties prop){
		char idx = 'A' ;
		while(true){
			String val = prop.getProperty( "" + idx );
			if( val == null || val.length() <= 0 )break;
			states.put ( "" + idx , new State( ) );
			++idx;
		}
		for( char i = 'A'; i < idx ; ++i ){
			String val = prop.getProperty( "" + i );
			parseLine( "" + i , val );
		}
	}
	private void parseLine( String nm , String val ){
		StringTokenizer tz = new StringTokenizer ( val , " " );
		String stext = tz.nextToken();
		State state = (State)states.get( nm );
		state.text = stext.replace( '+' , ' ' );
		while( tz.hasMoreTokens() ){
			String tx = tz.nextToken();
			String ln = tz.nextToken();
			state.addLink( tx , (State)states.get ( ln ) );
		}
	}
	public void print(){
		Iterator iter = states.keySet().iterator();
		while( iter.hasNext() ){
			String key = (String) iter.next();
			System.out.print( key + " :: " );
			((State)states.get( key )).print();;
		}
	}
}