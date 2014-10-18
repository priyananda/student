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



public class ChooserUI extends JFrame
{
	Vector		players = new Vector(5,5);
	BufferedImage bim	= new BufferedImage(800,600,BufferedImage.TYPE_INT_RGB);
	JPanel		main;
	JButton		bOK		= new JButton(new ImageIcon("images/enter.gif")),
				bCancel = new JButton(new ImageIcon("images/exit.gif"));
	JComboBox   cbPlayer = new JComboBox( ),
				cbMap	= new JComboBox();
	JTextArea	tPlayer = new JTextArea(5,20),
				tMap	= new JTextArea(5,20);
	JLabel		iPlayer	= new JLabel(" " , JLabel.CENTER),
				iMap	= new JLabel(" " , JLabel.CENTER);
	JComboBox	cbMusic	= new JComboBox();
	Vector		vMaps	= new Vector(5,5);
	static java.applet.AudioClip clip;

	public ChooserUI(){
		setVisible(false);
		setUndecorated(true);
		setSize( getToolkit().getScreenSize());
		bim.createGraphics().drawImage(
			ImageLoader.loadImage( "images/uibg.jpg"),0,0,800,600,null
		);
		main = new JPanel(){
			public void paintComponent(Graphics g){
				super.paintComponent(g);
				g.drawImage( bim,0,0,getWidth(),getHeight(),null);
			}
		};
		setAllTheStupidUIProperties();
		getContentPane().add(main);
		addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
				System.exit(0);
            }
        });
		setVisible(true);
	}

	private void setAllTheStupidUIProperties(){
		tPlayer.setWrapStyleWord(true);
		tMap.setWrapStyleWord(true);
		tPlayer.setLineWrap(true);
		tMap.setLineWrap(true);
		iPlayer.setBorder(
			BorderFactory.createBevelBorder(0)
		);
		bOK.setOpaque(false);
		bOK.setBorder(null);
		cbMap.setBackground(Color.black);
		cbMap.setForeground(Color.white);
		cbMap.setBorder( null);
		cbMusic.setBackground(Color.black);
		cbMusic.setForeground(Color.white);
		cbMusic.setBorder( null);
		cbPlayer.setBackground(Color.black);
		cbPlayer.setForeground(Color.white);
		cbPlayer.setBorder( null);
		tPlayer.setBackground(Color.black);
		tPlayer.setForeground(Color.white);
		tMap.setBackground(Color.black);
		tMap.setForeground(Color.white);
		bOK.setPressedIcon( bCancel.getIcon());
		bCancel.setOpaque(false);
		bCancel.setBorder(null);
		bCancel.setPressedIcon( bOK.getIcon());
		layoutComponents();
		iMap.setForeground( Color.yellow);
		iMap.setBorder( BorderFactory.createLineBorder( Color.orange,2));
		fillCombo();
		bOK.addActionListener( new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				setVisible(false);
				dispose();
				GameUI gui = new GameUI( (GameMap)vMaps.get( cbMap.getSelectedIndex()));
				gui.show();
			}
		});
		bOK.setContentAreaFilled(false);
		bCancel.setContentAreaFilled(false);
		bCancel.addActionListener( new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				System.exit(0);
			}
		});
	}

	private void layoutComponents(){
		GridBagLayout gb = new GridBagLayout();
		GridBagConstraints gbc = new GridBagConstraints();
		JLabel	lP = new JLabel("Choose Player" ,JLabel.CENTER),
				lM = new JLabel("Choose Map" , JLabel.CENTER),
				lMus = new JLabel("Choose Map" , JLabel.CENTER);

		lP.setForeground(Color.white);
		lM.setForeground(Color.white);
		JPanel t1 = new JPanel();
		JPanel t2 = new JPanel();
		JPanel t3 = new JPanel();
		JScrollPane p1  = new JScrollPane(tPlayer),p2 =  new JScrollPane(tMap);

		t1.setOpaque(false);
		t2.setOpaque(false);
		t3.setOpaque(false);
		lP.setVerticalAlignment(JLabel.BOTTOM);
		lM.setVerticalAlignment(JLabel.BOTTOM);

		main.setLayout( gb );
		gbc.fill = gbc.HORIZONTAL;
		gbc.ipadx = gbc.ipady = 10;
		gbc.insets = new Insets(5,100,5,100);

		gbc.weightx = 1.0;
		gbc.weighty = 7.0;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.gridx = 0;
		gbc.gridy = 0;
		gb.setConstraints(t1 ,gbc);
		main.add( t1);

		gbc.weightx = 1.0;
		gbc.weighty = 7.0;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.gridx = 1;
		gbc.gridy = 0;
		gb.setConstraints(t2 ,gbc);
		main.add( t2);

		gbc.weightx = 1.0;
		gbc.weighty = 1.0;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.gridx = 0;
		gbc.gridy = 1;
		gb.setConstraints( lP,gbc);
		main.add( lP );

		gbc.weightx = 1.0;
		gbc.weighty = 1.0;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.gridx = 1;
		gbc.gridy = 1;
		gb.setConstraints( lM,gbc);
		main.add( lM);


		gbc.gridx = 0;
		gbc.gridy = 2;
		gb.setConstraints( cbPlayer,gbc);
		main.add( cbPlayer );

		gbc.gridx = 1;
		gbc.gridy = 2;
		gb.setConstraints( cbMap,gbc);
		main.add( cbMap );

		gbc.ipadx = gbc.ipady = 60;
		gbc.gridx = 0;
		gbc.gridy = 4;
		gb.setConstraints(p1,gbc);
		main.add( p1 );

		gbc.gridx = 1;
		gbc.gridy = 4;
		gb.setConstraints(p2,gbc);
		main.add( p2 );

		gbc.ipadx = gbc.ipady = 10;
		gbc.gridx = 0;
		gbc.gridy = 3;
		gb.setConstraints(iPlayer,gbc);
		main.add( iPlayer );

		gbc.gridx = 1;
		gbc.gridy = 3;
		gb.setConstraints(iMap,gbc);
		main.add( iMap );

		gbc.gridx = 0;
		gbc.gridy = 5;
		gb.setConstraints(cbMusic,gbc);
		main.add( cbMusic );

		gbc.gridx = 0;
		gbc.gridy = 6;
		gbc.weighty = 1.0;
		gb.setConstraints(bOK,gbc);
		main.add( bOK );

		gbc.gridx = 1;
		gbc.gridy = 6;
		gbc.weighty = 1.0;
		gb.setConstraints(bCancel,gbc);
		main.add( bCancel );


	}
	public void fillCombo(){
		getPlayers();
		cbPlayer.addItemListener( new ItemListener(){
			public void itemStateChanged(ItemEvent ie){
				int idx = cbPlayer.getSelectedIndex();
				Player pl = (Player) players.get(idx);
				tPlayer.setText( pl.story );
				iPlayer.setIcon( pl.picture );
			}
		});
		Player pl = (Player) players.get(0);
		tPlayer.setText( pl.story );
		iPlayer.setIcon( pl.picture );
		getMaps();
		fillMusicCombo();
	}
	private void fillMusicCombo(){
		File mapDir = new File("audio/bg");
		String [] kids = mapDir.list(new FilenameFilter(){
			public boolean accept( File f , String n){
				return n.endsWith(".aiff") || n.endsWith(".wav") ||
						n.endsWith(".au");
			}
		});
		cbMusic.addItem("-SELECT-");
		if( kids == null || kids.length < 0 )return;
		for ( int i = 0 ; i < kids.length ; ++i )
			cbMusic.addItem(kids[i]);
		cbMusic.addItemListener( new ItemListener(){
			public void itemStateChanged(ItemEvent ie){
				String idx = (String)cbMusic.getSelectedItem();
				if( idx.equals( "-SELECT-" )) return;
				if( clip != null )clip.stop();
				clip = null;
				clip = AudioLoader.loadAudio( "bg/" + idx , 0 );
				clip.play();
			}
		});
	}
	private void getMaps(){
		File mapDir = new File("maps");
		String [] kids = mapDir.list(new FilenameFilter(){
			public boolean accept( File f , String n){
				return n.endsWith(".hsh");
			}
		});

		if( kids == null || kids.length < 1){
			JOptionPane.showMessageDialog(null,
				"No Maps found.Please create a map using mapc.bat",
				"You doaf",0
			);
			System.exit(0);
		}
		for( int i = 0 ; i < kids.length ; ++i )
		{
			GameMap gm;
			try{
				gm = GameMap.restore( "maps/" + kids[i] );
				cbMap.addItem(kids[i]);
				vMaps.add ( gm );
			}
			catch (Exception e){}

		}
		cbMap.addItemListener( new ItemListener(){
			public void itemStateChanged(ItemEvent ie){
				int idx = cbMap.getSelectedIndex();
				GameMap map = (GameMap) vMaps.get(idx);
				tMap.setText( map.mapDescription );
				iMap.setText( map.mapName);
			}
		});
		cbMap.setSelectedIndex(0);
		GameMap map = (GameMap) vMaps.get(0);
		tMap.setText( map.mapDescription );
		iMap.setText( map.mapName);
	}
	public static void main(String [] arg){
		new ChooserUI().show();
	}

	private void getPlayers(){
		File mapDir = new File("players");
		String [] kids = mapDir.list(new FilenameFilter(){
			public boolean accept( File f , String n){
				return n.endsWith(".ply");
			}
		});
		if( kids == null || kids.length < 1){
			JOptionPane.showMessageDialog(null,
				"No Maps found.Please create a map using mapc.bat",
				"You f3star doaf",0
			);
			System.exit(0);
		}
		for( int i = 0 ; i < kids.length ; ++i ){
			String smallname = kids[i];
			smallname = smallname.substring( 0, smallname.indexOf(".ply") );
			Player p = new Player();
			try{p.readFile(smallname);}catch (Exception e){}
			cbPlayer.addItem(p.name);
			players.add ( p );
		}
	}
}

class Player
{
	String name;
	String story;
	ImageIcon picture;

	public void readFile(String pname) throws Exception{
		BufferedReader br = new BufferedReader(
			new InputStreamReader(
				new FileInputStream ( "players/" + pname + ".ply" )
			)
		);
		story = " ";
		name = br.readLine();
		String str = "" ;
		while( ( str = br.readLine() ) != null )
			story += str;
		br.close();
		picture = new ImageIcon("players/" + pname + ".gif");
	}
}