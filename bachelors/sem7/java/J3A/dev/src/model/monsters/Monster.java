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
import java.awt.image.*;
import java.awt.geom.*;
import java.applet.*;


/**
 *	Manages animation and attack data
 */
class MonsterRenderer
{
	int type;
	BufferedImage bim;
	AudioClip clip;

	public MonsterRenderer(int _type)
	{
		type = _type;
		Image img = ImageLoader.loadImage( MonsterData.imagePaths[type] );
		bim = new BufferedImage(
			img.getWidth(null) ,
			img.getHeight(null),
			BufferedImage.TYPE_INT_ARGB
		);
		bim.createGraphics().drawImage( img,0,0,null);
		clip = AudioLoader.loadAudio(MonsterData.soundPaths[type]);
	}
	public void drawMonster( Graphics2D g, Point location , int counter)
	{
		BufferedImage sub;
		if( MonsterData.imageCount[type] == 1)
			sub = bim;
		else
			sub = bim.getSubimage(
				(counter++ % MonsterData.imageCount[type]) * MonsterData.imageSizes[type].width,0,
				MonsterData.imageSizes[type].width,MonsterData.imageSizes[type].height
			);
		g.drawImage(
			sub,
			location.x + GameConstants.tileWidth - MonsterData.imageSizes[type].width / 2,
			location.y - MonsterData.imageSizes[type].height / 2,
			MonsterData.imageSizes[type].width,
			MonsterData.imageSizes[type].height,
			null
		);
	}
	public void playSound()
	{
		clip.play();
	}
}

public class Monster extends DynamicObject
{
	private boolean firing = false;
	private MonsterRenderer manager;
	private int counter = 0;
	volatile private int health = 0;
	volatile private boolean dead = false;

	public Monster(Point p, int i , int j , int ty)
	{
		location = p; tileXY = new Point(i,j);
		if( ty >= GameConstants.MONSTER_START )
			type = ty - GameConstants.MONSTER_START;
		else type = ty;
		manager = new MonsterRenderer(type);
		health = MonsterData.monsterHealth[type];
	}
	public Monster(Point p, int i , int j , int ty , GameController gc){
		this(p,i,j,ty);
		setController( gc);
	}
	public void draw( Graphics2D g )
	{
		if(dead)
			return;
		manager.drawMonster( g,location,counter);
		if( !dead && !firing && controller != null && MonsterData.animDelays[type] != 0){
			controller.registerEvent( new EventObject(){
				public void eventAction(){
					firing = false;
					if(dead)return;
					controller.repaint( location.x - 100, location.y - 100 ,200,200 );
					++counter;
				}
			},MonsterData.animDelays[type]);
			firing = true;
		}
	}
	public void interactWith(final Human h )
	{
		if (dead)
			return;
		if ( h.tileXY.x == tileXY.x ){
			if ( h.tileXY.y == tileXY.y + 1){
				h.setDirection( h.DIR_LEFT , 0 );
				attack(h);
			}
			if ( h.tileXY.y == tileXY.y - 1){
				h.setDirection( h.DIR_RIGHT , 0 );
				attack(h);
			}
		}else if ( h.tileXY.y == tileXY.y){
			if ( h.tileXY.x == tileXY.x + 1){
				h.setDirection( h.DIR_UP , 0 );
				attack(h);
			}
			if ( h.tileXY.x == tileXY.x - 1){
				h.setDirection( h.DIR_DOWN , 0 );
				attack(h);
			}
		}
	}
	public void attack(final Human h )
	{
		manager.playSound();
		controller.registerEvent( new EventObject(){
        	public void eventAction(){
             	interactWith(h);
			}
		},500);
		h.decrementHP( MonsterData.monsterAttack[type] );
	}
	public void reactToSpell(int spNum)
	{
		if( spNum == 4 ){ dead = true; health = 0; return;}
		if( type == 4 ) return;
		health -= SpellData.spellDamages[ spNum ];
		if( health <= 0 ) dead = true;
	}
	public int getType()
	{
		return GameConstants.MONSTER_START + type ;
	}
}