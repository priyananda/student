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

public class Spell extends Pickable implements SpellConstants
{
	public Spell(Point p, int i , int j , int ty)
	{
		location = p; tileXY = new Point(i,j);
		type = (ty >= GameConstants.SPELL_START ) ?
			ty - GameConstants.SPELL_START :
			ty;
	}
	public void drawStatic(Graphics2D g)
	{
		g.setColor( colors[type] );
		g.setFont ( spellFont );
		g.drawString(
			j3a.model.SpellData.letters[type],
			location.x + GameConstants.tileWidth - 10,
			location.y + 10
		);
	}
	public void drawDynamic(Graphics2D g)
	{
		g.drawImage(
			gold,
			location.x + GameConstants.tileWidth / 2,
			location.y - 23 ,
			46,46,
			null
		);
	}

	public void onPickUp(Human h)
	{
		h.addSpell( type );
		if( controller != null )
			controller.showMessage("You got the spell " + j3a.model.SpellData.spellNames[type]);
	}
	public int getType()
	{
		return GameConstants.SPELL_START + type ;
	}
}