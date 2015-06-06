
/**
* This class is used to call the calculateMove method for
* a computer checker player.  We use this setup in order to allow
* interupting the calculateMove method after some amount of time.
* @author Justin Tritz
*/

public class PlayerThread implements Runnable {

	/**
	* This is the checker player that will be calculating the move
	*/
	private CheckerPlayer player;
	/**
	* This is the initial board state that should be used to calculate
	* the next move.
	*/
	private int[][] boardState;
	/**
	* This is the player which you should choose a move for (RED_PLAYER or BLACK_PLAYER)
	*/
	private int whosTurn;

	/**
	* This allows you to create a thread that can be used
	* to calculate a move, but can be interupted after some amount of time.
	* @param p This is the checker player that should calculate the move
	* @param bs This is the board state that you should use to calculate the next move.
	* @param t This indicates which player you need to calculate the move for (RED_PLAYER or BLACK_PLAYER).
	*/
	public PlayerThread(CheckerPlayer p, int[][] bs, int t){
		player = p;
		boardState = Utils.copyBoardState(bs);
		whosTurn = t;
	}

	/**
	* This is the method that is invoked when the player thread's start() method is called.
	* In turn, this thread has the checker player begin calculating the next move.
	*/
	public void run(){
		try{
			player.calculateMove(boardState, whosTurn);
		}catch(Exception e){}
	}

}