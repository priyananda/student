
/**
* This class represents a checker player that chooses randomly
* among its legal moves.  This should be helpful in showing you how
* to create checker players.
* @author Justin Tritz
*/

import java.util.*;

public class RANDOMPlayer extends CheckerPlayer implements CheckerBoardConstants {

	/**
	* This constructor allows you to create a random checker player.
	* @param name This is the name you would like to give this checker player.
	*/
	public RANDOMPlayer(String name){
		super(name);
	}

	/**
	* This method is called when the random player is supposed to choose the next
	* move.  It gets a list of all possible legal moves, and then chooses randomly among them.
	* You should always make sure that you set the chosenMove equal to the best move you find
	* at any given point during the calculation, because this method may get interupted before
	* it completes.  For this same reason, you should make a copy of the boardState before
	* you make any changes to it.
	* @param boardState This is an int array representing the starting state of the board
	* you should use when calculating the next move.
	* @param whosTurn This is an int indicating which player you should calculate the move for (RED_PLAYER or BLACK_PLAYER).
	*/
	public void calculateMove(int[][] boardState, int whosTurn){
		// indicate that a move has not yet been chosen.
		chosenMove = null;
		// get all the possible moves for this player given the board state provided.
		Vector possibleMoves = Utils.getAllPossibleMoves(boardState, whosTurn);
		// if the player has some moves.
		if(possibleMoves.size()!=0){
			// choose a random move from the list of possible moves.
			int rand = (int)(Math.random()*possibleMoves.size());
			// set the chosen move to be the random move chosen.
			chosenMove = (Move)possibleMoves.elementAt(rand);
		}
	}



}