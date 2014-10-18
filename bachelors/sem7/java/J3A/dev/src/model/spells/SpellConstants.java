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
public interface SpellConstants
{
	Image gold = ImageLoader.loadImage( "images/gold.gif");
	Color colors[] = {
		Color.blue,Color.magenta,Color.green , Color.white, Color.red
	};
	Font spellFont = new Font("Dialog", Font.BOLD , 30 );
}