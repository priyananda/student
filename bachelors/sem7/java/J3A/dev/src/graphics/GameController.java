/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.model;
import java.util.*;
import javax.swing.*;
import java.awt.*;
import j3a.graphics.*;

/**
 * Simple class for holding an event and its current tick value
 */
class RequestableEvent
{
	EventObject eo;
	int currTicks;
	public RequestableEvent(EventObject _eo , int ticks){
  		eo = _eo;currTicks = ticks;
	}
	public boolean fire(){
  		if ( currTicks == 0){
			eo.eventAction();
	     	return true;
	    }
	    -- currTicks;
	    return false;
	}
}

/**
 * The main class of the game runtime. controlls all dynamic objects
 * in the game.Has the central thread which takes care of all non-human
 * animations , regenarations etc
 */
public class GameController implements Runnable{
	Thread eventThread = new Thread(this);;
  	Vector events = new Vector();
	RunTimeRenderingSurface surf;
 	public GameController( RunTimeRenderingSurface sr ){
     	surf = sr;
	}
	/**
	 * The time is in ticks . A tick is defined in GameContants
	 * This is the lowest period of time that a request can be
	 * scheduled for.
	 */
 	synchronized public void registerEvent( EventObject eo , int ticks){
  		events.add( new RequestableEvent( eo, ticks));
    }
    public void start(){
		eventThread.start();
	}
	public void stop(){
		eventThread.stop();
	}
 	public void run(){
		for(;;){
			try{
				eventThread.sleep( GameConstants.TICK_INTERVAL );
			}catch(Exception ae){}
			for( int i = 0 ; i < events.size() ; ++i ){
				RequestableEvent req = (RequestableEvent)events.get(i);
				if( req.fire()){
					events.remove(i);
					repaint();
				}
			}
		}
    }
	public void repaint(){
		surf.repaint();
	}
	public void markTile(int i , int j){
		surf.markTile(i,j);
	}
	public Point getTile(int i , int j){
		return surf.getTile(i,j);
	}
	public void checkSpellEffect(int i , int j,int typ){
		surf.checkSpellEffect(i,j,typ);
	}
	public void repaint(Rectangle rect){
		surf.repaint(rect);
	}
	public void repaint(int x,int y,int w,int h){
		surf.repaint(new Rectangle(x,y,w,h));
	}
	/**
	 * returns the map tile size ( rows , cols )
	 */
	public Point getTileMax(){
		return surf.getTileMax();
	}
	public void showMessage( String mess){
		surf.showMessage(mess);
	}
	public void checkGameState(){
		Human h = surf.human;
		Point pt = surf.getTileMax();
		pt.x--; pt.y--;
		if( h.tileXY.equals(pt))
			doWin();
		if( h.isDead())
			doLose();
	}
	public void processCheat(int cheatCode){
		Human h = surf.human;
		switch(cheatCode){
			case CheatConstants.MATCH_WIN:doWin();
			case CheatConstants.MATCH_LOSE:doLose();
			case CheatConstants.HEALTH_INC10:h.incrementHP(100);break;
			case CheatConstants.HEALTH_INC5:h.incrementHP(50);break;
			case CheatConstants.INVINCIBLE:h.setInvincible(true);break;
			case CheatConstants.GIVE_SPELL_0:h.spells[0] = 10;break;
			case CheatConstants.GIVE_SPELL_1:h.spells[1] = 10;break;
			case CheatConstants.GIVE_SPELL_2:h.spells[2] = 10;break;
			case CheatConstants.GIVE_SPELL_3:h.spells[3] = 10;break;
			case CheatConstants.GIVE_SPELL_4:h.spells[4] = 10;break;
			case CheatConstants.GIVE_ALL_SPELLS:
						h.spells[0] = 10;
						h.spells[1] = 10;
						h.spells[2] = 10;
						h.spells[3] = 10;
						h.spells[4] = 10;break;
		}
	}
	public void doWin(){
		//TODO:make this more sexy
		JOptionPane.showMessageDialog( null,
			"You Win",
			"I don't know how , but you WON!!",
			0
		);
		System.exit(0);
	}
	public void doLose(){
		//TODO:make this more sexy
		JOptionPane.showMessageDialog( null,
			"You Lose",
			"Just as I thought , you stupid nincompoop, you lost!",
			0
		);
		System.exit(0);
	}
}