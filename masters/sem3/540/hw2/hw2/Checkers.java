
/**
* This is the class that drives the checker program.
* You can get an explanation of how to use the command
* by entering java Checkers at the command prompt.
* @author Justin Tritz
*/

import java.util.*;

public class Checkers implements CheckerBoardConstants {

	/**
	* This is the main method where the program will begin execution.
	*/
	public static void main(String[] args){

		if(args==null || args.length==0){
			System.err.println("\njava Checkers <-red_player> <-black_player> [-delay 1000] [-step] [-debug]");
			System.err.println("\n-red_player is the specification of who you want to play the red player");
			System.err.println("\n-black_player is the specification of who you want to play the black player");
			System.err.println("\n-delay 1000 is the option that specifies how much time you will give the computer players to think.  This example will give computer players 1 second to think.");
			System.err.println("\n-step is the option for making the players move on the click of the mouse.  You should only use this option if you are watching two computer players play each other.");
			System.err.println("\n-debug is the option that will set the debug flag to true in the Utils class.  You can then choose to only print when the program is in debug mode.");
			return;
		}

		Checkers checkers = new Checkers();

		CheckerPlayer redPlayer = null;
		CheckerPlayer blackPlayer = null;
		boolean moveOnClick = false;

		// go through the command line arguments and figure out
		// what type of game should be played.
		for(int i=0;i<args.length;i++){
			if(args[i].equals("-random")){
				if(redPlayer==null){
					redPlayer = new RANDOMPlayer("RED PLAYER");
				}else{
					blackPlayer = new RANDOMPlayer("BLACK PLAYER");
				}
			}else if(args[i].equals("-human")){
				if(redPlayer==null){
					redPlayer = new HUMANPlayer("RED PLAYER");
				}else{
					blackPlayer = new HUMANPlayer("BLACK PLAYER");
				}
			}else if(args[i].equals("-basicAlpha")){
				if(redPlayer==null){
					redPlayer = new AlphaBetaPlayer("RED PLAYER");
				}else{
					blackPlayer = new AlphaBetaPlayer("BLACK PLAYER");
				}
			//my modifications
			}else if(args[i].equalsIgnoreCase("-samplePlayer")){
				if(redPlayer == null)
					redPlayer = new SHENOYPlayer("RED PLAYER");
				else
					blackPlayer = new SHENOYPlayer("BLACK PLAYER");
			}else if(args[i].equalsIgnoreCase("-shenoy")){
				if(redPlayer == null)
					redPlayer = new SHENOYPlayer("RED PLAYER");
				else
					blackPlayer = new SHENOYPlayer("BLACK PLAYER");
			}else if(args[i].equals("-delay")){
				i++;
				Utils.MOVE_DELAY = Integer.parseInt(args[i]);
			}else if(args[i].equals("-step")){
				moveOnClick = true;
			}else if(args[i].equals("-debug")){
				Utils.debug = true;
			}
		}

		checkers.setRedPlayer(redPlayer);
		checkers.setBlackPlayer(blackPlayer);

		checkers.setMoveOnClick(moveOnClick);

		if(!moveOnClick){
			checkers.play();
		}
	}

	/**
	* This is the CheckerPlayer that will player for RED
	*/
	private CheckerPlayer redPlayer;
	/**
	* This is the CheckerPlayer that will player for BLACK
	*/
	private CheckerPlayer blackPlayer;
	/**
	* This is a reference to the checkerboard that will be used
	* to set the board state for drawing and actually calling
	* the drawCheckerBoard method.
	*/
	private CheckerBoard checkerboard;
	/**
	* This indicates which player's turn it is (RED_PLAYER or BLACK_PLAYER).
	*/
	private int turn;
	/**
	* This stores the current move being created by a human player via clicks
	* on the checkerboard.
	*/
	private Move currentMove;
	/**
	* This indicates whether or not the moves should be made only when the user clicks
	* on the checkerboard.
	*/
	private boolean moveOnClick;

	/**
	* This method is used to begin a new game of checkers.
	*/
	public Checkers(){
		redPlayer = null;
		blackPlayer = null;
		moveOnClick = false;
		checkerboard = new CheckerBoard(this);
		turn = RED_PLAYER;
		checkerboard.setStatus("RED Turn");
		currentMove = new Move();
		checkerboard.drawCheckerBoard();
	}

	/**
	* This method is used to specify who will be making the
	* move decisions for the red player.
	* @param player This is the player that will be making reds moves.
	*/
	public void setRedPlayer(CheckerPlayer player){
		redPlayer = player;
	}

	/**
	* This method is used to specify who will be making the
	* move decisions for the black player.
	* @param player This is the player that will be making blacks moves.
	*/
	public void setBlackPlayer(CheckerPlayer player){
		blackPlayer = player;
	}

	/**
	* This method allows us to set the moveOnClick variable from
	* outside this class.
	* @param b This is the value moveOnClick will be set to.
	*/
	public void setMoveOnClick(boolean b){
		moveOnClick = b;
	}

	/**
	* This method is called to check and see if the player whos turn
	* it is is being operated by a computer player.  If so, the computer
	* player will be called upon to decide on which move to make next.
	*/
	public void play(){

		int[][] boardState = checkerboard.getBoardState();

		Utils.printBoardState(boardState);
		System.out.println(turn==RED_PLAYER?"RED Turn\n":"BLACK Turn\n");

		// if it is the red players turn and the red player is being controlled
		// by the computer.
		if(turn==RED_PLAYER && !(redPlayer instanceof HUMANPlayer) ){
			try{
				// have the player calculate the best move for the red player,
				// but interupt the calculation after the specified amount of time.
				try{
					Thread playerThread = new Thread(new PlayerThread(redPlayer, boardState, RED_PLAYER));
					playerThread.start();
					Thread.sleep(Utils.MOVE_DELAY);
					playerThread.stop();
				}catch(Exception e){}

				// get the move calculated by the red player
				Move move = redPlayer.getMove();
				// if the move is not a valid move, then the red player loses.
				if(Utils.validMove(turn, boardState, move)!=VALID_MOVE){
					throw new Exception("This move is not valid");
				}

				System.out.println("RED PLAYER's move " + move + "\n");
				Utils.executeMove(turn, move, boardState);
				int winner = Utils.checkForWinner(boardState);
				if(winner==RED_PLAYER){
					checkerboard.setStatus("RED wins!!!");
				}else if(winner==BLACK_PLAYER){
					checkerboard.setStatus("BLACK wins!!!");
				}else{
					turn = BLACK_PLAYER;
					checkerboard.setStatus("BLACK Turn");
					checkerboard.drawCheckerBoard();
					if(!moveOnClick){
						play();
					}
				}
			}catch(Exception e){
				checkerboard.setStatus("BLACK wins!!!");
				checkerboard.drawCheckerBoard();
			}
		// if it is the black players turn and the black player is being controlled
		// by the computer.
		}else if(turn==BLACK_PLAYER && !(blackPlayer instanceof HUMANPlayer) ){
			try{
				// have the player calculate the best move for the black player,
				// but interupt the calculation after the specified amount of time.
				try{
					Thread playerThread = new Thread(new PlayerThread(blackPlayer, boardState, BLACK_PLAYER));
					playerThread.start();
					Thread.sleep(Utils.MOVE_DELAY);
					playerThread.stop();
				}catch(Exception e){}

				// get the move calculated by the black player
				Move move = blackPlayer.getMove();
				// if the move is not a valid move, then the black player loses.
				if(Utils.validMove(turn, boardState, move)!=VALID_MOVE){
					throw new Exception("This move is not valid");
				}

				System.out.println("BLACK PLAYER's move " + move + "\n");
				Utils.executeMove(turn, move, boardState);
				int winner = Utils.checkForWinner(boardState);
				if(winner==RED_PLAYER){
					checkerboard.setStatus("RED wins!!!");
				}else if(winner==BLACK_PLAYER){
					checkerboard.setStatus("BLACK wins!!!");
				}else{
					turn = RED_PLAYER;
					checkerboard.setStatus("RED Turn");
					checkerboard.drawCheckerBoard();
					if(!moveOnClick){
						play();
					}
				}
			}catch(Exception e){
				checkerboard.setStatus("RED wins!!!");
				checkerboard.drawCheckerBoard();
			}
		}
	}

	/**
	* This method is called when a square is clicked on the checkerboard.
	* The rows start at the top and go down with indexes starting at 0
	* The columns start from the left and go right with the indexes starting at 0
	* @param row This specifies the row that was clicked on.
	* @param column This specifies the column that was clicked on.
	*/
	public void squareClicked(int row, int column){

		// if the game proceeds only when the checkerboard is clicked,
		// then call the play method.
		if(moveOnClick){
			play();
		}else{

			int[][] boardState = checkerboard.getBoardState();

			if(turn==RED_PLAYER){
				currentMove.addLocation(new Location(row,column));
				int moveStatus = Utils.validMove(turn , boardState , currentMove );
				if(moveStatus==VALID_MOVE){
					System.out.println("RED PLAYER's move " + currentMove + "\n");
					Utils.executeMove(turn, currentMove, boardState);
					int winner = Utils.checkForWinner(boardState);
					if(winner==RED_PLAYER){
						checkerboard.setStatus("RED wins!!!");
					}else if(winner==BLACK_PLAYER){
						checkerboard.setStatus("BLACK wins!!!");
					}else{
						currentMove = new Move();
						turn = BLACK_PLAYER;
						checkerboard.setStatus("BLACK turn");
						play();
					}
				}else if(moveStatus==INVALID_MOVE){
					currentMove = new Move();
					checkerboard.setStatus("Invalid move, please try again RED player");
				}else if(moveStatus==VALID_MOVE_BUT_INCOMPLETE){
					checkerboard.setStatus(currentMove.toString());
				}
			}else if(turn==BLACK_PLAYER){
				currentMove.addLocation(new Location(row,column));
				int moveStatus = Utils.validMove(turn , boardState , currentMove );
				if(moveStatus==VALID_MOVE){
					System.out.println("BLACK PLAYER's move " + currentMove + "\n");
					Utils.executeMove(turn, currentMove, boardState);
					int winner = Utils.checkForWinner(boardState);
					if(winner==RED_PLAYER){
						checkerboard.setStatus("RED wins!!!");
					}else if(winner==BLACK_PLAYER){
						checkerboard.setStatus("BLACK wins!!!");
					}else{
						currentMove = new Move();
						turn = RED_PLAYER;
						checkerboard.setStatus("RED turn");
						play();
					}
				}else if(moveStatus==INVALID_MOVE){
					checkerboard.drawCheckerBoard();
					currentMove = new Move();
					checkerboard.setStatus("Invalid move, please try again BLACK player");
				}else if(moveStatus==VALID_MOVE_BUT_INCOMPLETE){
					checkerboard.setStatus(currentMove.toString());
				}
			}
			checkerboard.drawCheckerBoard();
		}

	}

}