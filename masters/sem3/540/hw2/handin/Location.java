
/**
* This class represents a location on the checkerboard.
* @author Justin Tritz
*/

public class Location {

	/**
	* This is the row on the checkerboard.  Rows run horizontal
	* and are numbered starting at 0.  The 0 row is on the top
	* of the checkerboard.
	*/
	public int row;
	/**
	* This is the column on the checkerboard.  Columns run vertical
	* and are numbered starting at 0.  The 0 column is on the left
	* of the checkerboard.
	*/
	public int col;

	/**
	* This allows you to create a location on the checkerboard
	* at row r and column c
	* @param r This is the row on the checkerboard
	* @param c This is the column on the checkerboard
	*/
	public Location(int r,int c){
		this.row = r;
		this.col = c;
	}

	/**
	* This method returns the row for this location
	* @return An int that is the row associated with this location.
	*/
	public int getRow(){
		return row;
	}

	/**
	* This method returns the column for this location
	* @return An int that is the column associated with this location.
	*/
	public int getCol(){
		return col;
	}

	/**
	* This method allows you to convert the Location object into a String that
	* can then be output for debugging and other purposes.
	* @return The String representing this object is returned.
	*/
	public String toString(){
		return "(" + row + "," + col + ")";
	}

}