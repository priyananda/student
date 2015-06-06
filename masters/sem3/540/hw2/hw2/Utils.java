
/**
* This class provides you with many functions that you may find
* useful when coding your checker player's
* @author Justin Tritz
*/
import java.util.*;
import java.io.*;

public class Utils implements CheckerBoardConstants {

	/**
	* This is the amount of time that the computer players will
	* be given to calculate a move.
	*/
	public static int MOVE_DELAY = 1000;
	/**
	* This indicates whether or not the program is in debug mode.
	*/
	public static boolean debug = false;

	/**
	* This method prints out the board state as represented
	* by the 2 dimensional int array
	* @param arr This is the board state that should be printed out.
	*/
	public static void printBoardState(int[][] arr){
		for(int r=0;r<arr.length;r++){
			for(int c=0;c<arr[r].length;c++){
				String square = arr[r][c]+"";
				if(arr[r][c]==BLANK_GRAY_BACKGROUND || arr[r][c]==BLANK_WHITE_BACKGROUND){
					square = "-";
				}else if(arr[r][c]==RED_PAWN){
					square = "r";
				}else if(arr[r][c]==RED_KING){
					square = "R";
				}else if(arr[r][c]==BLACK_PAWN){
					square = "b";
				}else if(arr[r][c]==BLACK_KING){
					square = "B";
				}
				System.out.print(square);
				if(c+1<arr[r].length){
					System.out.print(" ");
				}
			}
			System.out.println();
		}
		System.out.println();
	}

	/**
	* This method makes a copy of the board state and returns it.
	* @param arr This is the board state that you want to copy.
	* @return The return value is a two dimensional array that is a copy of arr.
	*/
	public static int[][] copyBoardState(int[][] arr){
		int[][] result = new int[arr.length][arr[0].length];
		for(int r=0;r<arr.length;r++){
			for(int c=0;c<arr[r].length;c++){
				result[r][c] = arr[r][c];
			}
		}
		return result;
	}

	/**
	* This method is a scoring function for the checker board.  It will return
	* an integer indicating how good the board state is for both players.
	* A large positive value is good for RED and a large negative value is good
	* for BLACK.
	* @param boardState This is the board state for which a score will be generated.
	* @param whosTurn This indicates which players turn it is because that affects the
	* score (RED_PLAYER or BLACK_PLAYER).
	* @return An int is returned indicating the score for the provided board state.
	*/
	public static int scoreCheckerBoard(int[][] boardState, int whosTurn){

		// number of red pawns on the board
		int redPawnCount = 0;
		// number of black pawns on the board
		int blackPawnCount = 0;
		// number of red kings on the board
		int redKingCount = 0;
		// number of black kings on the board
		int blackKingCount = 0;

		// go through the board and count the pawns and kings for
		// both the red and black player.
		for(int row=0;row<BOARD_HEIGHT;row++){
			for(int col=0;col<BOARD_WIDTH;col++){
				int piece = boardState[row][col];
				if(piece==RED_PAWN){
					redPawnCount++;
				}else if(piece==RED_KING){
					redKingCount++;
				}else if(piece==BLACK_PAWN){
					blackPawnCount++;
				}else if(piece==BLACK_KING){
					blackKingCount++;
				}
			}
		}
		// use the tallies that have been calculated to get a final board score.
		int score = (redPawnCount-blackPawnCount);
		score += 2*(redKingCount-blackKingCount);

		return score;

	}

        
        
	/**
	* This method will update the board state by executing the move.
	* @param whosTurn This indicates which player is executing the move (RED_PLAYER or BLACK_PLAYER).
	* @param move This is the move that should be executed.
	* @param boardState This is the board state that should be updated by
	* executing the move.  This parameter is updated by the method.
	* @return The return value is a stack of two dimensional arrays of int.
	* The purpose of the return value is to allow the user to reset the board
	* state (via the setBoardState method) to what it was before the move was executed.
	*/
	public static Stack executeMove(int whosTurn, Move move, int[][] boardState){
		Stack result = new Stack();
		if(move.includesJumps()){
			Location from = move.getLocationAtIndex(0);
			// execute each of the steps in the move
			for(int i=1;i<move.locationCount();i++){
				Location to = move.getLocationAtIndex(i);
				// call the jump method to actually update the board state.
				result.push( jump(whosTurn, boardState, from.row, from.col, to.row, to.col) );
				from = to;
			}
		}else{
			Location from = move.getLocationAtIndex(0);
			Location to = move.getLocationAtIndex(1);
			// call the move method to actually update the board state.
			result.push( move(whosTurn, boardState, from.row, from.col, to.row, to.col) );
		}
		// crown kings that may have been created after the move was executed.
		crownKings(boardState);
		return result;
	}

	/**
	* This method checks for a winner given a board state and returns a value
	* to indicate if it found one (RED_PLAYER, BLACK_PLAYER, or NEITHER_PLAYER).
	* @param boardState This is the board state for which we want to determine if
	* there is a winner
	* @return The return value is RED_PLAYER if red wins, BLACK_PLAYER if black wins,
	* and NEITHER_PLAYER if nobody has won yet.
	*/
	public static int checkForWinner(int[][] boardState){
		Vector redPossible = getAllPossibleMoves(boardState,RED_PLAYER);
		Vector blackPossible = getAllPossibleMoves(boardState,BLACK_PLAYER);
		// if both black and red have moves.
		if(redPossible.size()>0 && blackPossible.size()>0){
			return NEITHER_PLAYER;
		// if just red has moves.
		}else if(redPossible.size()>0){
			return RED_PLAYER;
		// if just black has moves.
		}else{
			return BLACK_PLAYER;
		}
	}

	/**
	* This method is used to crown kings in the given board state.  Any
	* black piece in the bottom row is crowned as a king, and any red piece
	* in the top row is crowned a king.
	* @param boardState This is the board state for which we will crown kings.
	* This parameter is modified by this method.
	*/
	public static void crownKings(int[][] boardState){
		// for each column in the board state
		for(int c=0;c<BOARD_WIDTH;c++){
			// if the top row and this column has a red piece.
			if(boardState[0][c]==RED_PAWN){
				boardState[0][c] = RED_KING;
			}
			// if the bottom row and this column has a red piece
			if(boardState[BOARD_HEIGHT-1][c]==BLACK_PAWN){
				boardState[BOARD_HEIGHT-1][c] = BLACK_KING;
			}
		}
	}

	/**
	* This method is used to determine if a move is valid.
	* @param whosTurn This indicates which player will be attempting the move. (RED_PLAYER or BLACK_PLAYER).
	* @param boardState This is the board state just before the move would be executed.
	* @param move This is the move that we are checking to see if it is valid.
	* @return The return value indicates whether or not the move is valid.  The possible return
	* values are (VALID_MOVE, INVALID_MOVE, or VALID_MOVE_BUT_INCOMPLETE).
	*/
	public static int validMove(int whosTurn , int[][] boardState , Move move ){
		// if the move doesn't consist of any locations it is invalid
		if(move.locationCount() == 0){ return INVALID_MOVE; }
		// get the location where the move will begin.
		Location start = move.getLocationAtIndex(0);
		// determine the piece that will be moving
		int piece = boardState[start.row][start.col];
		// determine the player that owns the piece that will be moving.
		int owner = getOwner(piece);
		// if the player moving doesn't own the piece that is going to be moved it is an invalid move.
		if(whosTurn != owner){
			return INVALID_MOVE;
		}
		// if the only thing indicated by the move is its starting location, the move is
		// valid, but not complete.
		if(move.locationCount()==1){ return VALID_MOVE_BUT_INCOMPLETE; }
		boolean jumpExists = jumpExists(whosTurn,boardState);
		Location next = move.getLocationAtIndex(1);
		// if the move is not a jump
		if(Math.abs(next.col-start.col)==1 && Math.abs(next.row-start.row)==1){
			// if a jump exists but the move is not a jump, the move is invalid.
			if(jumpExists){
				return INVALID_MOVE;
			}
			// if they player is not allowed to move to the location specified, it is an
			// invalid move.
			if(!canMove(whosTurn , boardState , start.row , start.col , next.row , next.col)){
				return INVALID_MOVE;
			}
			// if the move is not a jump, but it consists of more than two locations, it is invalid.
			if(move.locationCount()!=2){
				return INVALID_MOVE;
			}
			// otherwise it is a valid move.
			return VALID_MOVE;
		}
		Location from = start;
		Stack stateStack = new Stack();
		for(int i=1;i<move.locationCount();i++){
			Location to = move.getLocationAtIndex(i);
			// a jump must be two squares away, otherwise it is invalid
			if(Math.abs(from.col-to.col)!=2 || Math.abs(from.row-to.row)!=2){
				setBoardState(stateStack,boardState);
				return INVALID_MOVE;
			}
			// if the jump cannot be performed, the move is invalid
			if( !canJump(whosTurn, boardState, from.row, from.col, to.row, to.col) ){
				setBoardState(stateStack,boardState);
				return INVALID_MOVE;
			}else{
				// perform the jump.
				stateStack.push( jump(whosTurn, boardState, from.row, from.col, to.row, to.col) );
			}
			// if this is the last location in the jump sequence, and there exists another
			// jump, then the move is valid but incomplete
			if(i+1==move.locationCount() && jumpExists(whosTurn,boardState,to.row,to.col)){
				setBoardState(stateStack,boardState);
				return VALID_MOVE_BUT_INCOMPLETE;
			}
			from = to;
		}
		setBoardState(stateStack,boardState);
		return VALID_MOVE;
	}

	/**
	* This method returns true if a jump exists for the player specified
	* by whos turn in the board state provided.
	* @param whosTurn This indicates which player you would like to check
	* if a jump exists (RED_PLAYER or BLACK_PLAYER).
	* @param boardState This is the state of the board for which you
	* would like to know if a jump exists
	* @return Returns true if a jump exists for the players whos turn it
	* is in the given board state.
	*/
	public static boolean jumpExists(int whosTurn, int[][] boardState){

		for(int r=0;r<boardState.length;r++){
			for(int c=0;c<boardState[r].length;c++){

				if(jumpExists(whosTurn, boardState, r, c)){
					return true;
				}
			}
		}

		return false;

	}

	/**
	* This method returns true if a jump exists from the row and column
	* specified for the player specified
	* by whos turn in the board state provided.
	* @param whosTurn This indicates which player you would like to check
	* if a jump exists (RED_PLAYER or BLACK_PLAYER).
	* @param boardState This is the state of the board for which you
	* would like to know if a jump exists
	* @param fromRow This is the row that the piece in question is in.
	* @param fromCol This is the column that the piece in question is in.
	* @return Returns true if a jump exists for the players whos turn it
	* is in the given board state.
	*/
	public static boolean jumpExists(int whosTurn, int[][] boardState, int fromRow, int fromCol){

		// for the columns two columns to the left and right of the from column
		for(int xDir=-2; xDir<3; xDir+=4){
			// for the rows two columns above and below the from row
			for(int yDir=-2; yDir<3; yDir+=4){

				if( canJump(whosTurn , boardState , fromRow , fromCol , fromRow+yDir , fromCol+xDir) ){
					return true;
				}
			}
		}

		return false;

	}

	/**
	* This method will return all the moves that the player specified by whosTurn
	* can make in the given board state.
	* @param boardState This is the board state for which you will find all possible moves.
	* @param whosTurn This is the player that will be making the move (RED_PLAYER or BLACK_PLAYER).
	* @return The return value is a vector of Move containing all the possible moves
	* that the player can make from the given board state.
	*/
	public static Vector getAllPossibleMoves(int[][] boardState, int whosTurn){

		Vector possibleMoves = new Vector();

		boolean jumpExists = jumpExists( whosTurn , boardState );

		// for each square on the checkerboard
		for(int r=0;r<boardState.length;r++){
			for(int c=0;c<boardState[r].length;c++){

				// for each direction that a piece can move
				for(int xDir=-1; xDir<2; xDir+=2){
					for(int yDir=-1; yDir<2; yDir+=2){

						// if the piece can move in the specified direction
						if( !jumpExists && canMove(whosTurn , boardState , r , c , r+yDir , c+xDir) ){

							Move move = new Move();
							move.addLocation(new Location(r,c));
							move.addLocation(new Location(r+yDir,c+xDir));
							possibleMoves.add(move);

						// if piece can jump in the specified direction
						}else if( canJump(whosTurn , boardState , r , c , r+(2*yDir) , c+(2*xDir)) ){

							Move move = new Move();
							move.addLocation(new Location(r,c));
							move.addLocation(new Location(r+(2*yDir),c+(2*xDir)));
							// save the current state of the checkerboard
							int[][] currentState = jump(whosTurn, boardState, r, c, r+(2*yDir), c+(2*xDir));
							// attempt to add more jumps to this jump
							addMultipleJumps(r+(2*yDir), c+(2*xDir), boardState, move, possibleMoves);
							// restore the state of the checkerboard
							setBoardState(currentState,boardState);
						}
					}
				}
			}
		}

		return possibleMoves;

	}

	/**
	* This method will add all possible combinations of jumps that can be made from
	* the row and column specified in the given board state.  It will then all all those
	* possible moves to the possible moves vector.
	* @param fromRow This is the row that the next jump must begin from
	* @param fromCol This is the column that the next jump must begin from
	* @param boardState This is the state of the board you must use when determining
	* if there are more jumps to add.
	* @param move This is the move that we will be adding the additional jumps to.  It
	* currently consists of 1 jump (2 locations).
	* @param possibleMoves This is a vector that contains all of the possible moves for
	* a player.  We will be adding additional moves that we find to the vector.  Therefore
	* it may change.
	*/
	public static void addMultipleJumps(	int fromRow, int fromCol, int[][] boardState,
											Move move, Vector possibleMoves){

		boolean canJumpAgain = false;

		// for each direction that the piece may jump
		for(int xDir=-2; xDir<3; xDir+=4){
			for(int yDir=-2; yDir<3; yDir+=4){

				// if the piece can jump again.
				if( canJump( getOwner(boardState[fromRow][fromCol]) , boardState , fromRow , fromCol , fromRow+yDir , fromCol+xDir ) ){
					canJumpAgain = true;
					// add the new jump found
					move.addLocation(new Location(fromRow+yDir,fromCol+xDir));
					int[][] currentState = jump( getOwner(boardState[fromRow][fromCol]), boardState, fromRow, fromCol, fromRow+yDir, fromCol+xDir);
					// add any additional jumps you find
					addMultipleJumps(fromRow+yDir, fromCol+xDir, boardState, move, possibleMoves);
					// restore the board state
					setBoardState(currentState,boardState);
					// remove the last jump from the move we have been building.
					move.removeLastLocation();
				}

			}
		}

		// if we could not jump again, add the move to the list of possible moves.
		if(!canJumpAgain){
			possibleMoves.add( move.copy() );
		}

	}

	/**
	* This method will modify the board state by reversing the moves made
	* and stored on the stateStack.
	* @param stateStack This is a sequence of settings that modified the original
	* board state that you are trying to restore.  The settings on the top of the
	* stack indicate what needs to be reset first.
	* @param boardState This is the current state of the board that you would like
	* to change back to what it was before you executed certain moves on it.
	* This parameter is modified by the method.
	*/
	public static void setBoardState(Stack stateStack, int[][] boardState){
		while(!stateStack.isEmpty()){
			setBoardState( (int[][])stateStack.pop() , boardState);
		}
	}

	/**
	* This method will modify the board state by reversing a move made.
	* @param settings This is a sequence of settings that modified the original
	* board state that you are trying to restore.
	* @param boardState This is the current state of the board that you would like
	* to change back to what it was before you executed a move on it.
	* This parameter is modified by the method.
	*/
	public static void setBoardState(int[][] settings, int[][] boardState){
		// 0 0 1
		// 1 1 2
		// the above 2D array of ints would mean we want to set the value
		// in row 0 column 0 to 1 and the value in row 1 column 1 to 2.
		for(int i=0;i<settings.length;i++){
			int row = settings[i][0];
			int col = settings[i][1];
			int piece = settings[i][2];
			boardState[row][col] = piece;
		}
	}

	/**
	* This method will determine whether or not a move (not a jump) is legal.
	* @param whosTurn This is the player whos turn it is to move (RED_PLAYER or BLACK_PLAYER).
	* @param boardState This is the state of the board for which you would like to know if the
	* move is legal.
	* @param fromRow This is the row that the piece is in that you are wondering if you can move.
	* @param fromCol This is the column that the piece is in that you are wondering if you can move.
	* @param toRow This is the row that you are wondering if you can move the piece to.
	* @param toCol This is the column that you are wondering if you can move the piece to.
	* @return This method returns true if you can move the specified piece from the starting location
	* to the desired location.
	*/
	public static boolean canMove(	int whosTurn,int[][] boardState,
									int fromRow, int fromCol,
									int toRow, int toCol){
		// if you are moving out of bounds return false
		if(toRow < 0 || toRow >= BOARD_HEIGHT || toCol < 0 || toCol >= BOARD_WIDTH){
			return false;
		}

		// if a red pawn is moving down the board return false;
		if(boardState[fromRow][fromCol]==RED_PAWN && fromRow <= toRow){
			return false;
		// if a black pawn is moving up the board return false;
		}else if(boardState[fromRow][fromCol]==BLACK_PAWN && fromRow >= toRow){
			return false;
		}

		// return true if the owner of the piece being moved is the same as the
		// players whos turn it is, and the square you are moving to is empty.
		return getOwner(boardState[fromRow][fromCol])==whosTurn && getOwner(boardState[toRow][toCol])==NEITHER_PLAYER;
	}

	/**
	* This method will modify the board state provided by executing the move specified.
	* @param whosTurn This indicates the player whos turn it is (RED_PLAYER or BLACK_PLAYER).
	* @param boardState This is the board state that will be modified.
	* @param fromRow This is the row of the piece that will be moved
	* @param fromCol This is the column of the piece that will be moved.
	* @param toRow This is the row where you will move the piece to.
	* @param toCol This is the column where you will move the piece to.
	* @return The return value is the settings that you need to pass to the
	* setBoardState method in order to restore the board state to what it was before
	* you performed this move.
	*/
	public static int[][] move(	int whosTurn, int[][] boardState,
								int fromRow, int fromCol,
								int toRow, int toCol){

		// save the settings of the board state before you execute the move
		int[][] result = {	{ fromRow, fromCol, boardState[fromRow][fromCol] },
							{ toRow, toCol, boardState[toRow][toCol] } };

		boardState[toRow][toCol] = boardState[fromRow][fromCol];
		boardState[fromRow][fromCol] = BLANK;

		return result;

	}

	/**
	* This method will determine whether or not a jump is legal.
	* @param whosTurn This is the player whos turn it is to move (RED_PLAYER or BLACK_PLAYER).
	* @param boardState This is the state of the board for which you would like to know if the
	* jump is legal.
	* @param fromRow This is the row that the piece is in that you are wondering if you can move.
	* @param fromCol This is the column that the piece is in that you are wondering if you can move.
	* @param toRow This is the row that you are wondering if you can jump the piece to.
	* @param toCol This is the column that you are wondering if you can jump the piece to.
	* @return This method returns true if you can jump the specified piece from the starting location
	* to the desired location.
	*/
	public static boolean canJump(	int whosTurn,int[][] boardState,
									int fromRow, int fromCol,
									int toRow, int toCol){

		// if you are jumping out of bounds return false
		if(toRow < 0 || toRow >= BOARD_HEIGHT || toCol < 0 || toCol >= BOARD_WIDTH){
			return false;
		}

		// if a red pawn is moving down the board return false
		if(boardState[fromRow][fromCol]==RED_PAWN && fromRow <= toRow){
			return false;
		// if a black pawn is moving up the board return false;
		}else if(boardState[fromRow][fromCol]==BLACK_PAWN && fromRow >= toRow){
			return false;
		}

		int overRow = (fromRow+toRow)/2;
		int overCol = (fromCol+toCol)/2;

		// if you are not jumping your opponent
		int jumper = getOwner(boardState[fromRow][fromCol]);
		int jumpee = getOwner(boardState[overRow][overCol]);
		int jumpTo = getOwner(boardState[toRow][toCol]);
		if(	jumper!=whosTurn || jumpTo!=NEITHER_PLAYER || jumpee==whosTurn || jumpee==NEITHER_PLAYER ){
			return false;
		}

		return true;

	}

	/**
	* This method will modify the board state provided by executing the jump specified.
	* @param whosTurn This indicates the player whos turn it is (RED_PLAYER or BLACK_PLAYER).
	* @param boardState This is the board state that will be modified.
	* @param fromRow This is the row of the piece that will be moved
	* @param fromCol This is the column of the piece that will be moved.
	* @param toRow This is the row where you will jump the piece to.
	* @param toCol This is the column where you will jump the piece to.
	* @return The return value is the settings that you need to pass to the
	* setBoardState method in order to restore the board state to what it was before
	* you performed this jump.
	*/
	public static int[][] jump(	int whosTurn, int[][] boardState,
								int fromRow, int fromCol,
								int toRow, int toCol){

		int overRow = (toRow+fromRow)/2;
		int overCol = (toCol+fromCol)/2;

		// save the settings of the board state before you execute the jump
		int[][] result = {	{ fromRow, 	fromCol, 	boardState[fromRow][fromCol] },
							{ toRow, 	toCol, 		boardState[toRow][toCol] },
							{ overRow, 	overCol, 	boardState[overRow][overCol] } };

		boardState[toRow][toCol] = boardState[fromRow][fromCol];
		boardState[fromRow][fromCol] = BLANK;
		boardState[overRow][overCol] = BLANK;

		return result;

	}

	/**
	* This method returns the owner of a piece (RED_PLAYER, BLACK_PLAYER, or NEITHER_PLAYER).
	* @param piece This is the piece you are trying to find an owner for.  It can
	* be any integer from 1-10 corresponding to a type of board square.
	*
	*/
	public static int getOwner(int piece){
		if(piece==RED_PAWN || piece==RED_KING){
			return RED_PLAYER;
		}else if(piece==BLACK_PAWN || piece==BLACK_KING){
			return BLACK_PLAYER;
		}
		return NEITHER_PLAYER;
	}

	public static int[][] readBoardState(String fileName){
		int[][] boardState = new int[8][8];
		try{
			BufferedReader br = new BufferedReader(new FileReader(fileName));
			for(int i=0;i<boardState.length;i++){
				String line=br.readLine().trim();
				StringTokenizer st = new StringTokenizer(line);
				for(int j=0;j<boardState[i].length;j++){
					char token = st.nextToken().charAt(0);
					if(token=='-'){
						if(i%2==0){
							boardState[i][j] = j%2==0 ? BLANK_WHITE_BACKGROUND : BLANK_GRAY_BACKGROUND;
						}else{
							boardState[i][j] = j%2==1 ? BLANK_WHITE_BACKGROUND : BLANK_GRAY_BACKGROUND;
						}
					}else if(token=='r'){
						boardState[i][j] = RED_PAWN;
					}else if(token=='b'){
						boardState[i][j] = BLACK_PAWN;
					}else if(token=='R'){
						boardState[i][j] = RED_KING;
					}else if(token=='B'){
						boardState[i][j] = BLACK_KING;
					}
				}
			}
		}catch(Exception e){}
		return boardState;
	}
}