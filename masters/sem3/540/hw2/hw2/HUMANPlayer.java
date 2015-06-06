

/**
* This class allows us to have a human player.  Notice the calculate move
* method does nothing.  The only function of this class is so that I can
* assign a CheckerPlayer and ask the question "Is this class an 'instanceof'
* HUMANPlayer?
* @author Justin Tritz
*/

public class HUMANPlayer extends CheckerPlayer implements CheckerBoardConstants {

	/**
	* This constructor allows you to create a human checker player.
	* @param name This is the name you would like to give this checker player.
	*/
	public HUMANPlayer(String name){
		super(name);
	}

	/**
	* This method intentionally does nothing because the move is determined by
	* how the human clicks the checkerboard.
	*/
	public void calculateMove(int[][] boardState, int whosTurn){}

}