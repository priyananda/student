
/**
* This class is used to manipulate a checkerboard
* @author Justin Tritz
*/

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

public class CheckerBoard extends JFrame implements CheckerBoardConstants {

	private DisplayPanel display;
	private int[][] boardState;
	private Checkers checkers;

	/**
	* This method allows you to create a checkerboard object
	* @param ci This is the class that will be notified when
	* a square is clicked via the squareClicked method.
	*/
	public CheckerBoard(Checkers ci){

		super("Checkers");
		this.setResizable(false);

		// store a reference to the Checkers class so you can call the square clicked
		// method when a square on the checkerboard is clicked.
		checkers = ci;

		boardState = Utils.readBoardState("boardstate");

		setLocation(20, 20);
		display = new DisplayPanel(this);
		Insets inset = getInsets();

		getContentPane().setLayout( new BorderLayout() );
		getContentPane().add(display, BorderLayout.CENTER);

		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {System.exit(0);}
		});
		pack();
		show();

	}

	/**
	* This method is invoked when a square is clicked on the checkerboard.
	* It then notifies the Checkers class that a square was clicked.
	* @param row This is the row that contains the square that was clicked.
	* The row numbers start with 0 on the top.
	* @param column This is the column that contains the square that was clicked.
	* The column numbers start with 0 on the left.
	*/
	public void squareClicked(int row,int column){
		checkers.squareClicked(row,column);
	}

	/**
	* This method allows you to set the string value displayed in
	* the upper left corner of the checkerboard display.
	* @param message This is the message you would like to display.
	*/
	public void setStatus(String message){
		display.setStatus(message);
	}

	/**
	* This method allows you to specify what should be displayed on
	* the square at row r and column c on the checkerboard.
	* @param r This is the row that contains the square that you want
	* to display the object in.
	* @param c This is the column that contains the square that you want
	* to display the object in.
	* @param type This is the object that you want to display as defined in
	* the CheckerBoardConstants class.
	*/
	public void setSquare(int r, int c, int type){
		boardState[r][c] = type;
	}

	/**
	* This method allows you to set the board state by passing in an
	* array of ints that specify what should be drawn on each square in the
	* checkerboard.
	* @param board This array of ints is used to specify what should be drawn
	* on each square in the checkerboard.
	*/
	public void setBoardState(int[][] board){
		boardState = board;
	}

	/**
	* This method returns the current state of the checkerboard.
	* @return The return value is an array of ints that indicate
	* what is on each square in the checkerboard.
	*/
	public int[][] getBoardState(){
		return boardState;
	}

	/**
	* Draws the checkerboard according to the current board state.
	*/
	public synchronized void drawCheckerBoard(){
		display.repaint();
	}
}