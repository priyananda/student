package j3a.graphics;
import java.util.*;

public class ConfigFile
{
	Vector m_Rows = new Vector();

	public void AddRow( String [] row )
	{
		m_Rows.add( row );
	}
	public int GetRowCount()
	{
		return  m_Rows.size();
	}
	public int GetColumnCount()
	{
  		if( GetRowCount() == 0 )
  			return 0;
    	String [] arr = (String []) m_Rows.get(0);
    	return arr.length;
	}
 	public String GetItem( int row, int col )
 	{
    	if( GetRowCount() <= row )
			return null;
		if( GetColumnCount() <= col )
			return null;
  		return ( (String []) m_Rows.get( row ) )[col];
	}
}