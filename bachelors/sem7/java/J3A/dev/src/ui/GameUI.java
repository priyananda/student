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
import java.applet.*;

public class GameUI extends JFrame implements KeyConstants
{
	RunTimeRenderingSurface pMain;
	HUDPanel pHUD ;
	JScrollPane jsp;
	JScrollBar vscroll;

	public GameUI(GameMap map){
		super("Press f1 for help");
		newComponents(map);
		initComponents();
		getSize( Toolkit.getDefaultToolkit().getScreenSize() );
		pack();
		setCursor(getToolkit().createCustomCursor(
			ImageLoader.loadImage( "images/cursor.png" ),
			new Point(0,0),
			"Numenor"
		));
	}

	private void newComponents(GameMap map){
		pMain = new RunTimeRenderingSurface(map);
		pHUD = new HUDPanel();
		pMain.setHUD( pHUD );
		jsp = new JScrollPane(
			jsp.VERTICAL_SCROLLBAR_NEVER,
			jsp.HORIZONTAL_SCROLLBAR_NEVER
		);
		addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
				askAndQuit();
            }
        });
		addKeyListener( new KeyAdapter(){
			public void keyPressed(KeyEvent ke) {
				int x;
				//System.out.println("" + ke.getKeyCode());
				switch(x = KeyBinding.getKey(ke.getKeyCode())){
					case HELP:new HelpDialog(GameUI.this).show();break;
					case QUIT:askAndQuit();break;
					case MOVE_UP:
					case MOVE_DOWN:
					case MOVE_LEFT:
					case MOVE_RIGHT:
						pMain.handleKey(x);break;
					case SPELL_0:pHUD.setSpell(0);break;
					case SPELL_1:pHUD.setSpell(1);break;
					case SPELL_2:pHUD.setSpell(2);break;
					case SPELL_3:pHUD.setSpell(3);break;
					case SPELL_4:pHUD.setSpell(4);break;
					case CHEAT_BOX :cheat();break;
					case SCROLL_UP:scroll(0,0);break;
					case SCROLL_LEFT:scroll(1,0);break;
					case SCROLL_DOWN:scroll(0,1);break;
					case SCROLL_RIGHT:scroll(1,1);break;
				}
			}
		});
		addMouseMotionListener( new MouseMotionAdapter(){
			public void mouseMoved(MouseEvent me){
				mouseScroll(me.getPoint());
			}
		});
	}
	private void initComponents(){
		GridBagLayout gb = new GridBagLayout();
		GridBagConstraints gbc = new GridBagConstraints();
		Container cp = getContentPane();
		cp.setLayout( gb );

		jsp.add(pMain);
		jsp.setViewportView(pMain);

		gbc.fill = gbc.BOTH;

		gbc.gridx = 0;
		gbc.gridy = 1;
		gbc.weightx = 1.0f;
		gbc.weighty = 1.0f;
		gb.setConstraints( pHUD, gbc );
		cp.add(pHUD);

		gbc.gridx = 0;
		gbc.gridy = 0;
		gbc.weightx = 1.0f;
		gbc.weighty = 20.0f;
		gb.setConstraints( jsp, gbc );
		cp.add(jsp);
	}

	private void mouseScroll( Point p){
		JScrollBar  h = jsp.getHorizontalScrollBar(),
					v = jsp.getVerticalScrollBar();

		if( p.x <= 50 ){
			h.setValue( h.getValue() - 10 );
			return;
		}
		if( p.x >= getWidth() - 50 && p.y <= getWidth() ){
			h.setValue( h.getValue() + 10 );
			return;
		}
		if( p.y <= 50 ){
			v.setValue( v.getValue() - 10 );
			return;
		}
		if( p.y >= getHeight() - 50 && p.y <= getHeight() ){
			v.setValue( v.getValue() + 10 );
			return;
		}
	}
	public void quake(int ticks){
		scroll( 1,ticks % 2);
	}
	public void askAndQuit(){
		JOptionPane.showMessageDialog(this,
			"So,you are scared to death,you lousy coward",
			"I am a loser",
			JOptionPane.ERROR_MESSAGE );
		System.exit(0);
	}
	/**
	 * @param dir direction 0=vertical
	 * @param more scroll increase=0
	 */
	public void scroll(int dir, int more){
		JScrollBar  bar =  dir == 1 ?jsp.getHorizontalScrollBar():
						jsp.getVerticalScrollBar();
		bar.setValue( bar.getValue() + ( more == 1 ? 50 : -50 ) );
	}
	public void cheat(){
		String input = JOptionPane.showInputDialog("Enter the cheat code");
		int x = 0;
		if( ( x = CheatManager.getCheatCode(input)) >= 0 )
			pMain.processCheat(x);
	}
}