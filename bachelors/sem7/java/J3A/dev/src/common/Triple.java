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

/**
	A structure to hold 3 objects - for Spell and Monster
	Pairs are held in Point structures
*/
public class Triple
{
	public int first , second , third;
	public Triple( int a , int b , int c){
		first = a;
		second = b;
		third = c;
	}
	public Triple(){}
}