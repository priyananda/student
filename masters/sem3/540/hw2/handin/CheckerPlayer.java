
/**
* This is an abstract class that must be inherited by every
* checker player you create.
* @author Justin Tritz
*/

public abstract class CheckerPlayer {

	/**
	* This is the name given to the player.
	*/
	protected String playerName;
	/**
	* This is the move chosen by a player when the calculateMove
	* method is called.  The player should update this variable as
	* soon as it finds a better move, because the calculateMove method
	* will be interupted by a timer after some amount of time.
	*/
	protected Move chosenMove;

	/**
	* This is the constructor for a CheckerPlayer and should be called
	* via super(...) whenever a subclass of this class is created.
	*/
	public CheckerPlayer(String name){
		playerName = name;
	}

	/**
	* This method must be overriden by any subclass of this class.
	* This method will eventually be interupted, so you should use
	* a copy of the board state when you do your calculations
	* to ensure that you don't change the board state if this thread is
	* killed before it completes.
	* @param boardState This is the state of the board for which you need
	* to choose the next move.
	* @param whosTurn This indicates which player you need to choose a move
	* for given the specified board state (RED_PLAYER or BLACK_PLAYER).
	*/
	public abstract void calculateMove(int[][] boardState, int whosTurn);

	/**
	* This method is used to retrieve the move chosen by this player when the calculateMove
	* method was called.
	* @return The return value is the Move chosen during the calculateMove method.
	*/
	public Move getMove(){
		return chosenMove;
	}

}