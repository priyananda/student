/**
 * The Fall of Numenor - JTile2D
 * (c) 2003 Priyananda Shenoy & Harish JP
 * This software is freely distributable under GNU GPL
 * See copyright.txt for more details
 */
package j3a.graphics;

import javax.swing.*;
import javax.swing.tree.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.image.*;
import java.awt.event.*;
import java.util.*;
import j3a.model.SpellConstants;

public class MapCreator extends javax.swing.JFrame implements TreeSelectionListener
{
    private DesignTimeRenderingSurface surf;
	private JPanel controlPanel;
	private j3a.model.GameMap map ;
	private JButton bSave = new JButton("Save");
	private JTree treeObjects;

    public MapCreator()
	{
		NewMapDialog dialog = new NewMapDialog(this);
		dialog.show();
		map = dialog.map;
		setVisible(false);
        initComponents();
		Dimension dx = Toolkit.getDefaultToolkit().getScreenSize();
		dx.height -= 30;
        setSize(dx);
		setVisible(true);
    }
    public void newComponents()
	{
        surf = new DesignTimeRenderingSurface(map);
	}
    private void initComponents()
	{
        newComponents();
        initControlPanel();
        getContentPane().setLayout(new javax.swing.BoxLayout(getContentPane(), javax.swing.BoxLayout.X_AXIS));
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                exitForm(evt);
            }
        });
		bSave.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				surf.saveMap(map);
			}
		});
		JScrollPane jsp = new JScrollPane();
        jsp.setDoubleBuffered(true);
		jsp.add( surf );
        jsp.setViewportView(surf);
		JSplitPane temp = new JSplitPane( JSplitPane.HORIZONTAL_SPLIT );
		temp.setLeftComponent( controlPanel);
		temp.setRightComponent( jsp );
		temp.setDividerLocation( 150 );
		temp.setOneTouchExpandable(true);
	    getContentPane().add(temp);
        pack();
    }
    private void exitForm(java.awt.event.WindowEvent evt)
	{
		System.exit(0);
    }
	public void valueChanged(TreeSelectionEvent e)
	{
		DefaultMutableTreeNode node = (DefaultMutableTreeNode)
						   treeObjects.getLastSelectedPathComponent();
		if (node == null || !node.isLeaf() ) return;
		TreeElement nodeInfo = (TreeElement) (node.getUserObject());
		surf.setState( nodeInfo.type + nodeInfo.num );
	}
	private void initControlPanel()
	{
		controlPanel = new JPanel();
		controlPanel.setLayout( new BorderLayout() );
		treeObjects = new JTree( createTree() );
		treeObjects.setBackground( Color.black );
		treeObjects.setForeground( Color.white );
		ImageIcon leafIcon = new ImageIcon("images/middle.gif");
		if (leafIcon != null) {
			DefaultTreeCellRenderer renderer =
				new DefaultTreeCellRenderer();
			renderer.setLeafIcon(leafIcon);
			renderer.setBackgroundNonSelectionColor( Color.black );
			renderer.setTextSelectionColor ( Color.black );
			renderer.setTextNonSelectionColor ( Color.white );
			treeObjects.setCellRenderer(renderer);
		}
		bSave.setBackground( Color.black );
		bSave.setForeground( Color.yellow );
		treeObjects.addTreeSelectionListener(this);
		JScrollPane baba = new JScrollPane( treeObjects );
		controlPanel.add( baba  , "Center" );
		controlPanel.add( bSave , "South" );
	}
	private DefaultMutableTreeNode createTree()
	{
		DefaultMutableTreeNode
			root = new DefaultMutableTreeNode ( "Objects" ),
			tiles = new DefaultMutableTreeNode ( "Tiles " ),
			health = new DefaultMutableTreeNode ( "Health" ),
			spells = new DefaultMutableTreeNode ( "Spells" ),
			items = new DefaultMutableTreeNode ( "Items" ),
			monsters = new DefaultMutableTreeNode ( "Monsters" );
		root.add( tiles );
		root.add( health );
		root.add( spells );
		root.add( items );
		root.add( monsters );
		for (int i = 0 ; i < Tile.names.length ; ++i )
			tiles.add( (new TreeElement(Tile.names[i],0,i)).createNode()  );
		for (int i = 0 ; i < PowerUp.names.length ; ++i )
			health.add(  (new TreeElement(PowerUp.names[i],GameConstants.POWERUP_START,i)).createNode() );
		for (int i = 0 ; i < j3a.model.SpellData.spellNames.length ; ++i )
			spells.add(  (new TreeElement(j3a.model.SpellData.spellNames[i],GameConstants.SPELL_START,i)).createNode() );
		for (int i = 0 ; i < j3a.model.ItemData.itemNames.length ; ++i )
			items.add(  (new TreeElement(j3a.model.ItemData.itemNames[i],GameConstants.ITEM_START,i)).createNode() );
		for (int i = 0 ; i < j3a.model.MonsterData.monsterNames.length ; ++i )
			monsters.add(  (new TreeElement(j3a.model.MonsterData.monsterNames[i],GameConstants.MONSTER_START,i)).createNode() );
		return root;
	}
    public static void main(String args[])
	{
        new MapCreator().show();
    }
	private class TreeElement
	{
		String str;
		int type , num ;
		public TreeElement( String _str , int _type , int _num )
		{
			str = _str; type = _type; num = _num;
		}
		public String toString()
		{
			return str;
		}
		public DefaultMutableTreeNode createNode()
		{
			return new DefaultMutableTreeNode( this );
		}
	}
}