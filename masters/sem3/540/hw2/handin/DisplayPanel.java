import java.awt.*;
import javax.swing.*;
import java.util.*;
import java.awt.event.*;

public class DisplayPanel extends JPanel implements CheckerBoardConstants, MouseListener {

	private String statusString;

	private Image redPawnGrayBack;
	private Image redPawnWhiteBack;
	private Image blackPawnGrayBack;
	private Image blackPawnWhiteBack;
	private Image redKingGrayBack;
	private Image redKingWhiteBack;
	private Image blackKingGrayBack;
	private Image blackKingWhiteBack;
	private Image blankWhiteBack;
	private Image blankGrayBack;

	private CheckerBoard checkerBoard;

	public DisplayPanel(CheckerBoard cb){
		super();
		setPreferredSize(new Dimension(BOARD_PIXEL_WIDTH, BOARD_PIXEL_HEIGHT));
		setDoubleBuffered(true);
		addMouseListener(this);
		statusString = "";
		checkerBoard = cb;
		loadImages();
	}

    private void loadImages() {
        // Create a media tracker to load the images...
        MediaTracker mediaTracker = new MediaTracker(this);
        Toolkit tk = Toolkit.getDefaultToolkit();
        int mtIndex = 0;

		redPawnGrayBack = tk.getImage( tk.getClass().getResource("/images/RedPawnGrayBack.gif") );
		mediaTracker.addImage(redPawnGrayBack, mtIndex++);

		redPawnWhiteBack = tk.getImage( tk.getClass().getResource("/images/RedPawnWhiteBack.gif") );
		mediaTracker.addImage(redPawnWhiteBack, mtIndex++);

		blackPawnGrayBack = tk.getImage( tk.getClass().getResource("/images/BlackPawnGrayBack.gif") );
		mediaTracker.addImage(blackPawnGrayBack, mtIndex++);

		blackPawnWhiteBack = tk.getImage( tk.getClass().getResource("/images/BlackPawnWhiteBack.gif") );
		mediaTracker.addImage(blackPawnWhiteBack, mtIndex++);

		redKingGrayBack = tk.getImage( tk.getClass().getResource("/images/RedKingGrayBack.gif") );
		mediaTracker.addImage(redKingGrayBack, mtIndex++);

		redKingWhiteBack = tk.getImage( tk.getClass().getResource("/images/RedKingWhiteBack.gif") );
		mediaTracker.addImage(redKingWhiteBack, mtIndex++);

		blackKingGrayBack = tk.getImage( tk.getClass().getResource("/images/BlackKingGrayBack.gif") );
		mediaTracker.addImage(blackKingGrayBack, mtIndex++);

		blackKingWhiteBack = tk.getImage( tk.getClass().getResource("/images/BlackKingWhiteBack.gif") );
		mediaTracker.addImage(blackKingWhiteBack, mtIndex++);

		blankGrayBack = tk.getImage( tk.getClass().getResource("/images/BlankGrayBack.gif") );
		mediaTracker.addImage(blankGrayBack, mtIndex++);

		blankWhiteBack = tk.getImage( tk.getClass().getResource("/images/BlankWhiteBack.gif") );
		mediaTracker.addImage(blankWhiteBack, mtIndex++);

        // Wait for the Tracker
        try {
            mediaTracker.waitForAll();
        }catch ( InterruptedException ie) {
            // That is a load of crap!
            ie.printStackTrace();
        }
    }

	public void setStatus(String s){
		statusString = s;
	}

	public static int getPanelHeight(){
		return BOARD_PIXEL_HEIGHT;
	}

	public static int getPanelWIDTH(){
		return BOARD_PIXEL_WIDTH;
	}

	private void drawEmptyBoard(Graphics g) {
		drawEmptyBoard(g,false);
	}

	private void drawEmptyBoard(Graphics g, boolean empty) {
		// Draw the background
		// background is set to white color
		g.setColor(Color.black);
		g.fillRect(0, 0, BOARD_PIXEL_WIDTH, BOARD_PIXEL_HEIGHT);

		if (!empty) {
			// set the background color of rugby pitch to green
			g.setColor(Color.blue);
			g.fillRect(BORDER_SIZE*SQUARE_WIDTH,(BORDER_SIZE)*SQUARE_HEIGHT,BOARD_WIDTH*SQUARE_WIDTH,BOARD_HEIGHT*SQUARE_HEIGHT);
		}

		// Frame the Field.
		g.setColor(Color.black);
		g.drawRect(BORDER_SIZE*SQUARE_WIDTH,BORDER_SIZE*SQUARE_HEIGHT,BOARD_WIDTH*SQUARE_WIDTH,(BOARD_HEIGHT)*SQUARE_HEIGHT);
	}


	public void paint(Graphics g) {

		super.paintComponent(g);

		drawEmptyBoard(g);

		drawStatus(g,statusString);

		int[][] boardState = checkerBoard.getBoardState();

		for(int r=0;r<boardState.length;r++){
			for(int c=0;c<boardState[r].length;c++){
				if(boardState[r][c]==BLANK_GRAY_BACKGROUND){
					drawSquare( g, new Location(r,c), blankGrayBack );
				}else if(boardState[r][c]==BLANK_WHITE_BACKGROUND){
					drawSquare( g, new Location(r,c), blankWhiteBack );
				}else if(boardState[r][c]==BLACK_PAWN_WHITE_BACKGROUND){
					drawSquare( g, new Location(r,c), blackPawnWhiteBack );
				}else if(boardState[r][c]==BLACK_PAWN_GRAY_BACKGROUND){
					drawSquare( g, new Location(r,c), blackPawnGrayBack );
				}else if(boardState[r][c]==BLACK_KING_WHITE_BACKGROUND){
					drawSquare( g, new Location(r,c), blackKingWhiteBack );
				}else if(boardState[r][c]==BLACK_KING_GRAY_BACKGROUND){
					drawSquare( g, new Location(r,c), blackKingGrayBack );
				}else if(boardState[r][c]==RED_PAWN_WHITE_BACKGROUND){
					drawSquare( g, new Location(r,c), redPawnWhiteBack );
				}else if(boardState[r][c]==RED_PAWN_GRAY_BACKGROUND){
					drawSquare( g, new Location(r,c), redPawnGrayBack );
				}else if(boardState[r][c]==RED_KING_WHITE_BACKGROUND){
					drawSquare( g, new Location(r,c), redKingWhiteBack );
				}else if(boardState[r][c]==RED_KING_GRAY_BACKGROUND){
					drawSquare( g, new Location(r,c), redKingGrayBack );
				}
			}
		}
	}

	private void drawSquare(Graphics g,Location l,Image image){
		int x = calculateXPosition(l.getCol());
		int y = calculateYPosition(l.getRow());
		g.drawImage(image, x, y, SQUARE_WIDTH, SQUARE_HEIGHT, null);
	}

	private void drawStatus(Graphics g, String s){
		g.setColor(Color.white);
		g.drawString(s,SQUARE_WIDTH/2, SQUARE_HEIGHT/2);
	}

	private int calculateXPosition(double posX){
		return (int)((posX+BORDER_SIZE)*SQUARE_WIDTH);
	}

	private int calculateYPosition(double posY){
		return (int)((posY+BORDER_SIZE)*SQUARE_HEIGHT);
	}

	private int calculateXPosition(int posX){
		return((posX+BORDER_SIZE)*SQUARE_WIDTH);
	}

	private int calculateYPosition(int posY){
		return((posY+BORDER_SIZE)*SQUARE_HEIGHT);
	}

	public void mouseClicked(MouseEvent e){
		int column = e.getX()/SQUARE_WIDTH;
		int row = e.getY()/SQUARE_HEIGHT;
		column--;
		row--;
		if(row >= 0 && row < BOARD_HEIGHT && column >= 0 && column < BOARD_WIDTH){
			checkerBoard.squareClicked(row,column);
		}
	}

	public void mouseEntered(MouseEvent e){
	}

	public void mouseExited(MouseEvent e){
	}

	public void mousePressed(MouseEvent e){
	}

	public void mouseReleased(MouseEvent e){
	}

}