

/**
* This class represents a checker move.  A checker move constists
* of a sequence of locations.  The starting location and the subsequent
* locations that the checker piece should be moved to.
* @author Justin Tritz
*/

import java.util.*;

public class Move {

	/**
	* The move id is automatically assigned when the move is
	* created.  This allows you to easily determine if two
	* different variables refer to the same move.
	*/
	private int moveId;
	/**
	* The vector of Location stores the move sequence.
	*/
	private Vector locations;
	/**
	* This variable stores the id that will be assigned to the next move that is created.
	*/
	private static int nextId = 1;

	/**
	* This constructor allows you to create a new move
	*/
	public Move(){
		locations = new Vector();
		moveId = nextId++;
	}

	/**
	* This method allows you to add a location to the move sequence.
	* @param location This is the location that you would like to add to
	* the move sequence.
	*/
	public void addLocation(Location location){
		locations.add(location);
	}

	/**
	* This method allows you to remove the last location from
	* the move sequence.
	*/
	public void removeLastLocation(){
		locations.removeElementAt(locations.size()-1);
	}

	/**
	* This method creates a copy of this Move object and returns it.
	* @return The return value is a copy of this move object.
	*/
	public Move copy(){
		Move m = new Move();
		m.locations = (Vector)locations.clone();
		return m;
	}

	/**
	* This method is used to determine the number of locations in the move.
	* @return The number of locations in the move sequence.
	*/
	public int locationCount(){
		return locations.size();
	}

	/**
	* This method is used to determine if the move contains jumps
	* @return This method returns true if this move includes a jump
	*/
	public boolean includesJumps(){
		// if there is more than 2 locations in the move sequence,
		// then the move must include jumps
		if(locations.size() > 2){
			return true;
		// if there are 2 locations in the move sequence, then you need
		// to check if the squares are next to each other.  If they are
		// not, then the move must be a jump.
		}else if(locations.size()==2){
			Location from = getLocationAtIndex(0);
			Location to = getLocationAtIndex(1);
			if(Math.abs(from.col-to.col)!=1){
				return true;
			}
		}
		return false;
	}

	/**
	* This method is used to determine if two moves are equal.  Two moves
	* are equal if they have the same moveId.
	* @param z This is the move object that you would like to compare this
	* move to.
	* @return This method returns true if the moves have the same moveId
	*/
	public boolean equals(Object z){
		Move m = (Move)z;
		return moveId==m.moveId;
	}

	/**
	* This method allows you to get the location at index i in the move sequence.
	* @param i This is the index of the location you would like to retrieve.
	* @return The location at index i.
	*/
	public Location getLocationAtIndex(int i){
		return (Location)locations.elementAt(i);
	}

	/**
	* This method allows you to convert the Move object into a String that
	* can then be output for debugging and other purposes.
	* @return The String representing this object is returned.
	*/
	public String toString(){
		String result = "";
		for(int i=0;i<locations.size();i++){
			result += locations.elementAt(i);
			if(i+1<locations.size()){
				result += ",";
			}
		}
		return result;
	}

}