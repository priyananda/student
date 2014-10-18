 /**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.model;
import java.awt.*;
import j3a.graphics.*;
import javax.swing.*;

public class Door extends DynamicObject
{
	final int OPEN = 0 , CLOSED = 1;
	int state;
	private Point oldHuman = new Point(-1,-1);
	Image[] gate = {
		ImageLoader.loadImage( "images/gate_open.gif" ),
		ImageLoader.loadImage( "images/gate_closed.gif" )
	};
	public Door(Point p, int i , int j ){
		location = p; tileXY = new Point(i,j);
		state = CLOSED;
	}
	public Door(Point p, int i , int j , GameController gc){
		this(p,i,j);
		setController( gc);
	}
	public void draw(Graphics2D g){
		g.drawImage( gate[state] , location.x + 10 , location.y - 30 , 100 , 45 , null);
	}
	public void interactWith(Human h ){
		boolean close = false;
		if( state == CLOSED ){
			if ( h.tileXY.x == tileXY.x ){
				if ( h.tileXY.y == tileXY.y + 1){
					h.setDirection( h.DIR_LEFT , 0 );
					close = true;
				}
				if ( h.tileXY.y == tileXY.y - 1){
					h.setDirection( h.DIR_RIGHT , 0 );
					close = true;
				}
			}else if ( h.tileXY.y == tileXY.y){
				if ( h.tileXY.x == tileXY.x + 1){
					h.setDirection( h.DIR_UP , 0 );
					close = true;
				}
				if ( h.tileXY.x == tileXY.x - 1){
					h.setDirection( h.DIR_DOWN , 0 );
					close = true;
				}
			}
			if( !close ) return;
			if( oldHuman.x != -1 && ! oldHuman.equals( h.tileXY ) ) return;
			oldHuman.x = h.tileXY.x;
			oldHuman.y = h.tileXY.y;
			String input = JOptionPane.showInputDialog("Enter the password");
			// hardcoded for testing
			if( input.equals( "baba" ) )
				state = OPEN;
		}
	}
	public int getType(){
		return GameConstants.DOOR;
	}
}