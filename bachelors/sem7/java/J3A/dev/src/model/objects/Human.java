/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.model;
import java.util.*;
import java.awt.*;
import java.applet.*;
import j3a.graphics.*;


/**
 * Human is the only thing that can affect and be affected by other
 * objects. It is also the most complex class with an anim thread
 * of its own.It is not (yet) a DynamicObject , so cant have more than
 * one human interacting with eah other
 */

public class Human implements Runnable , HumanConstants
{
	int tickCounter = 0;
	boolean casting = false;

	private boolean invincible = false;
	private AudioClip currClip = null;
	private GameController control;
	private final Image image = ImageLoader.loadImage( "images/wizz.gif" );
	private SpellEffect currSpell;
	private Point currSpellLocation;
	private int currSpellType =0;

    public int hp = GameConstants.DEFAULT_HP;
	public Point location , tileXY;
	public int spells[] = { 0,0,0,0,0 };
	/**
     * The movement mask.The LSB 4 bits are set if the movement in that
	 * direction is allowed.Initially it is set to 15.
	 * if ( moveMask & moveDirection != 0 ) then you can move
     */
    public int moveMask = 15;

	public Human( int i , int j , Point loc, GameController gc)
	{
		location = loc;
		control = gc;
		tileXY = new Point(i,j);
	}
	public void prepare()
	{
		Point max = control.getTileMax();
		moveMask = 15;
		if ( tileXY.y == 0 )
			moveMask = setBit( moveMask , DIR_LEFT , 0 );
		if ( tileXY.x == 0 )
			moveMask = setBit( moveMask , DIR_UP , 0 );
		if ( tileXY.y == max.y - 1)
			moveMask = setBit( moveMask , DIR_RIGHT , 0 );
		if ( tileXY.x == max.x - 1)
			moveMask = setBit( moveMask , DIR_DOWN , 0 );
	}
	public void addSpell( int sptype )
	{
		if ( sptype > GameConstants.SPELL_START )
			sptype -= GameConstants.SPELL_START;
		spells[ sptype ] ++;
		currClip = spellsnd;
		play();
	}
	public void setDirection(int dir,int value)
	{
		moveMask = setBit( moveMask , dir , value );
	}
 	public void move( int key )
	 {
		if( currClip != null ) currClip.stop();
		currClip = null;
		switch(key){
			case KeyConstants.MOVE_LEFT: doMove( DIR_LEFT );
				break;
			case KeyConstants.MOVE_UP: doMove( DIR_UP );
				break;
			case KeyConstants.MOVE_RIGHT: doMove( DIR_RIGHT );
				break;
			case KeyConstants.MOVE_DOWN: doMove( DIR_DOWN );
				break;
		}
	}
 	public void draw(Graphics2D g)
	 {
		g.drawImage( image,
			location.x + 20,
			location.y - 70,
			75,100,
			null
		);
		if( currSpell != null )
			currSpell.draw(g);
	}
	/**
	 * These two are basically for some redrawing and sounds
	 */
	public void incrementHP(int amt)
	{
		hp += amt;
		currClip = oooh;
		play();
	}
	public void decrementHP(int amt)
	{
		if(invincible)return;
		hp -= amt;
		currClip = dead;
		play();
   	}
   	public void setInvincible(boolean val)
	{
		invincible = val;
	}
	private void play()
	{
		if( currClip != null ) currClip.play();
	}
	public void drown()
	{
		if(invincible)return;
		hp -= 2;
		currClip = water;
		play();
	}
	public synchronized void run()
	{
		try{
			if( currSpell == null )return;
			while(!currSpell.completed()){
				try{ Thread.currentThread().sleep(currSpell.getAnimDelay());}catch(Exception ae){}
				Rectangle r = currSpell.getClip();
				//if( r != null)
				//	control.repaint(r);
				//else
					control.repaint();
			}
			control.checkSpellEffect(currSpellLocation.x,currSpellLocation.y , currSpellType );
			currSpellLocation = null;
			currSpell = null;
		}catch(Exception ae){
			System.out.println("" + ae );
			ae.printStackTrace();
		}
	}
	public boolean castSpell( int tileX , int tileY , int spellType){
		if( spellType < 0 || spellType > 5 )return false;
		if( spells[spellType] == 0 )return false;
		if( !checkSpellRange(tileX , tileY,spellType))return false;
		control.markTile( tileX , tileY );

		currSpellLocation = new Point(tileX,tileY);
		currSpellType = spellType;
		currSpell = SpellFactory.createSpell( spellType,control.getTile(tileX,tileY));

		--spells[spellType];
		new Thread(this).start();
		return true;
	}
	public void doMove(int dir){
		if ( (dir & moveMask) == 0 ){
			currClip = silly;
			play();
			return;
		}
		switch(dir){
			case DIR_LEFT:	tileXY.y --;
						location = IsometricTransform.transform(location,0,-1);
						break;
			case DIR_RIGHT:	tileXY.y ++;
						location = IsometricTransform.transform(location,0,1);
						break;
			case DIR_UP:tileXY.x --;
						location = IsometricTransform.transform(location,-1,0);
						break;
			case DIR_DOWN:	tileXY.x ++;
						location = IsometricTransform.transform(location,1,0);
						break;
		}
	}
	public int setBit( int num , int pos , int val ){
		return val == 0 ? num & ~pos : num | pos;
	}
	private boolean checkSpellRange( int i , int j ,int sp){
		int xdist = i > tileXY.x ? i - tileXY.x : tileXY.x - i;
		int ydist = j > tileXY.y ? j - tileXY.y : tileXY.y - j;
		if( xdist > j3a.model.SpellData.spellRanges[sp] ||
			ydist > j3a.model.SpellData.spellRanges[sp] )return false;
		return true;
	}
	public boolean isDead(){
		return hp <= 0;
	}
	public void addToBag( Pickable p ){

	}
}