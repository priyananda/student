/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.graphics;

import java.awt.*;
import java.io.*;
import java.awt.image. *;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
import j3a.model.*;

/**
 * The graphical counterpart of the Runtime Engine.Along with
 * GameController renders and takes input for the game. Smaller
 * than I expected
 */
public class RunTimeRenderingSurface extends JPanel
{
	final Image back;
	BufferedImage bim;
	Graphics2D gr;
	Vector gameObjects = new Vector();
	GameController control = new GameController(this);
	private HUDPanel hud;
	public Human human;
	GameMap map;

	public RunTimeRenderingSurface(GameMap map)
	{
		back = ImageLoader.loadImage("maps/" + map.saveFile + ".png");
		bim = new BufferedImage( back.getWidth(null) , back.getHeight(null) , BufferedImage.TYPE_INT_RGB);
		gr = bim.createGraphics();
		this.map = map;
		createGameObjects(map);
		setPreferredSize(new Dimension(back.getWidth(null) , back.getHeight(null)));
		gr.drawImage( back,0,0,null);
		control.start();
		addMouseListener( new MouseAdapter(){
			public void mouseClicked(MouseEvent me){
				processClick( me.getPoint() );
			}
		});
		human.prepare();
		interaction();
	}
	public void setHUD(HUDPanel p)
	{
		hud = p;
	}
	private void createGameObjects( GameMap map)
	{
		gameObjects = new Vector ();
		for (int i = 0 ;i < map.objects.size() ; ++i){
			Triple t = (Triple) map.objects.get(i );
			gameObjects.add(
				ObjectFactory.createObject(
					t, control, IsometricTransform.transform( map.start , t.first , t.second )
				)
			);
		}
		human = new Human( 0,0,map.start,control);
	}

	public void paintComponent(Graphics g)
	{
		Graphics2D g2 = (Graphics2D) g;
		g2.drawImage( bim,0,0,null);
		int gccount = gameObjects.size();
		for( int i = 0 ; i < gccount ; ++i )
		{
			GameObject gm = (GameObject)gameObjects.get(i);
			if( gm instanceof DynamicObject)
				((DynamicObject) gm).draw(g2);
		}
		human.draw(g2);
	}
	public void handleKey(int keyCode)
	{
		human.move( keyCode );
		human.prepare();
		interaction();
		repaint();
	}
	public Point getTileMax()
	{
		return new Point(map.nRows , map.nCols);
	}
	public void updateTimes()
	{
		if( hud != null )
			hud.renderHuman(human);
	}
	public void interaction()
	{
		for( int i = 0 ; i < gameObjects.size() ; ++i ){
			GameObject gm = (GameObject)gameObjects.get(i);
			if( gm != null )gm.interactWith(human);
		}
		updateTimes();
		control.checkGameState();
	}
	public void finalize()
	{
		control = null;
	}
	public void showMessage(String m)
	{
		if( hud != null )
			hud.setMessage(m);
	}
	private void processClick(Point pt)
	{
		int i=0, j=0;
		outer:
		for(i = 0 ; i < map.nRows ; ++i)
			for(j = 0 ; j < map.nCols; ++j ){
				Polygon  poly = IsometricTransform.transform2(map.start,i,j);
				if( poly.contains( pt.x,pt.y))break outer;
			}
		if( i >= map.nRows )return;
		human.castSpell( i , j , hud.getSpell() );
	}
	public void markTile( int i , int j)
	{
		Polygon  poly = IsometricTransform.transform2(map.start,i,j);
		gr.setColor(Color.red);
		gr.drawPolygon( poly);
		repaint();
	}
	public void checkSpellEffect(int i , int j ,int sp)
	{
		for( int q = 0 ; q < gameObjects.size() ; ++q ){
			GameObject gm = (GameObject)gameObjects.get(q);
			if( gm != null && gm.tileXY.x == i && gm.tileXY.y == j ){
				gm.reactToSpell(sp);
				break;
			}
		}
	}
	public Point getTile(int i , int j)
	{
		return IsometricTransform.transform(map.start, i,j);
	}
	public void processCheat(int cheatCode)
	{
		control.processCheat(cheatCode);
	}
}