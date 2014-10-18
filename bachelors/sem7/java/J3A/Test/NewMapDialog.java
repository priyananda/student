/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.graphics;

import javax.swing.*;
import java.awt.*;
import java.awt.image.*;
import java.awt.event.*;
import java.util.*;

public class NewMapDialog extends JDialog
{
	JTextField tName , tRows , tCols , tSave , tDesc;
	static final Image img = ImageLoader.loadImage( "images/menu.jpg");
	JButton bOk = new JButton("Ok"),
			bCancel = new JButton("Cancel") ;
	j3a.model.GameMap map = new j3a.model.GameMap ();
	
	public NewMapDialog( JFrame owner)
	{
		super(owner,"Enter new Map" , true);
		setSize(440,400);
		setLocation(200,100);
		JLabel  lName = new JLabel( "Map Name" , JLabel.CENTER ),
				lSizeX = new JLabel( "Rows" , JLabel.CENTER),
				lSizeY = new JLabel( "Columns" , JLabel.CENTER ),
				lDesc = new JLabel( "Description" , JLabel.CENTER),
				lSave = new JLabel( "Save Name"  , JLabel.CENTER);
				
		tName = new JTextField(10);
		tRows = new JTextField(10);
		tCols = new JTextField(10);
		tSave = new JTextField(10);
		tDesc = new JTextField(10);
		
		setBackground(Color.black);
		JPanel p = new JPanel();
		p.setOpaque(false);
		p.setLayout(  new GridLayout(12,2 , 10 , 10) );
		p.add( new JLabel("") );
		p.add( new JLabel("") );
		p.add( new JLabel("") );
		p.add( new JLabel("") );
		p.add( new JLabel("") );
		p.add( new JLabel("") );

		p.add( lName );
		p.add( tName );

		p.add( lSizeX );
		p.add( tRows );

		p.add( lSizeY );
		p.add( tCols );

		p.add( lDesc );
		p.add( tDesc );

		p.add( lSave);
		p.add( tSave);

		p.add( new JLabel("") );
		p.add( new JLabel("") );
		p.add( bOk);
		p.add( bCancel);
		setUndecorated(true);
		Container cp = getContentPane();
		JPanel temp = new JPanel(){
			public void paintComponent(Graphics g){
				super.paintComponent(g);
				g.drawImage(img,0,0,this);
			}
		};
		temp.add(p, BorderLayout.CENTER);
		temp.add(new JLabel("") , BorderLayout.WEST);
		temp.add(new JLabel("") , BorderLayout.SOUTH);
		temp.add(new JLabel(" ") , BorderLayout.NORTH);
		cp.add(temp);
		bCancel.addActionListener( new ActionListener(){
			public void actionPerformed(ActionEvent ave){
				System.exit(0);
			}
		});
		
		bOk.addActionListener( new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				try{
					map.nRows = Integer.parseInt(tRows.getText());
					map.nCols = Integer.parseInt(tCols.getText());
					map.mapName = tName.getText();
					map.mapDescription = tDesc.getText();
					map.saveFile = tSave.getText();
					dispose();
				}catch(Exception age){
					System.out.println("" + age );
				}
			}
		});
	}
}