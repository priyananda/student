
/**
* This interface is used to store the different constants that you
* may need when coding for this assignment.
* @author Justin Tritz
*/

public interface CheckerBoardConstants {

	/**
	* This is the width of a checker board square in pixels
	*/
	public final static int SQUARE_WIDTH = 50;
	/**
	* This is the height of a checker board square in pixels
	*/
	public final static int SQUARE_HEIGHT = 50;
	/**
	* This is the number of squares wide the checkerboard is
	*/
	public final static int BOARD_WIDTH = 8;
	/**
	* This is the number of squares high the checkerboard is
	*/
	public final static int BOARD_HEIGHT = 8;

	/**
	* This is the number of cells between the edge of the JPanel and
	* the checkerboard panel in squares.  This means the boarder around
	* the checkerboard is 1 square wide.
	*/
	public final static int BORDER_SIZE =  1;
	/**
	* This is how wide our JPanel is going to have to be in pixels
	*/
	public final static int BOARD_PIXEL_WIDTH = SQUARE_WIDTH * (BOARD_WIDTH + 2*BORDER_SIZE);
	/**
	* This is how tall our JPanel is going to have to be in pixels
	*/
	public final static int BOARD_PIXEL_HEIGHT = SQUARE_HEIGHT * (BOARD_HEIGHT + 2*BORDER_SIZE);

	/**
	* This represents a blank gray square on the checkerboard
	*/
	public final static int BLANK_GRAY_BACKGROUND = 1;
	/**
	* This represents a blank white square on the checkerboard
	*/
	public final static int BLANK_WHITE_BACKGROUND = 2;
	/**
	* This represents a black pawn on a square with a gray background
	*/
	public final static int BLACK_PAWN_GRAY_BACKGROUND = 3;
	/**
	* This represents a black pawn on a square with a white background
	*/
	public final static int BLACK_PAWN_WHITE_BACKGROUND = 4;
	/**
	* This represents a black king on a square with a gray background
	*/
	public final static int BLACK_KING_GRAY_BACKGROUND = 5;
	/**
	* This represents a black king on a square with a white background
	*/
	public final static int BLACK_KING_WHITE_BACKGROUND = 6;
	/**
	* This represents a red pawn on a square with a gray background
	*/
	public final static int RED_PAWN_GRAY_BACKGROUND = 7;
	/**
	* This represents a red pawn on a square with a white background
	*/
	public final static int RED_PAWN_WHITE_BACKGROUND = 8;
	/**
	* This represents a red king on a square with a gray background
	*/
	public final static int RED_KING_GRAY_BACKGROUND = 9;
	/**
	* This represents a red king on a square with a white background
	*/
	public final static int RED_KING_WHITE_BACKGROUND = 10;

	/**
	* This is the short way of refering to a black pawn since all pieces
	* should always be on a gray background
	*/
	public final static int BLACK_PAWN = 3;
	/**
	* This is the short way of refering to a black king since all pieces
	* should always be on a gray background
	*/
	public final static int BLACK_KING = 5;
	/**
	* This is the short way of refering to a red pawn since all pieces
	* should always be on a gray background
	*/
	public final static int RED_PAWN = 7;
	/**
	* This is the short way of refering to a red king since all pieces
	* should always be on a gray background
	*/
	public final static int RED_KING = 9;
	/**
	* This is the short way of refering to a blank square that a piece
	* may move to since all pieces
	* should always be on a gray background
	*/
	public final static int BLANK = 1;

	/**
	* This represents the neither player option and is used to
	* indicate that a square is not occupied by either player
	*/
	public final static int NEITHER_PLAYER = 0;
	/**
	* This represents the red player option and is used to
	* indicate that a square is occupied by the red player
	*/
	public final static int RED_PLAYER = 1;
	/**
	* This represents the black player option and is used to
	* indicate that a square is occupied by the black player
	*/
	public final static int BLACK_PLAYER = 2;

	/**
	* This is the value returned by the validMove method in the
	* Utils class when a move is not valid
	*/
	public final static int INVALID_MOVE = 0;
	/**
	* This is the value returned by the validMove method in the
	* Utils class when a move is valid, but
	* not complete because it can jump more pieces or make
	* a single first move without jumping pieces.
	*/
	public final static int VALID_MOVE_BUT_INCOMPLETE = 1;
	/**
	* This is the value returned by the validMove method in the
	* Utils class when a move is valid
	*/
	public final static int VALID_MOVE = 2;

}