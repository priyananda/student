package j3a.graphics;
import java.io.*;
import java.util.StringTokenizer;

public class ConfigFileInterpreter
{
	public static ConfigFile Parse(String fileName)
	{
		try
		{
			ConfigFile output = new ConfigFile();
			BufferedReader reader = new BufferedReader(
        		new InputStreamReader(
        			new FileInputStream(
        				fileName
        			)
        		)
        	);
        	String line = null;
        	while( ( line = reader.readLine() ) != null )
        	{
				Parse(  output , line );
			}
			reader.close();
   			return output;
		}
		catch(Exception e)
		{
		}
		return null;
	}
	private static void Parse( ConfigFile cf, String line )
	{
		if( line.charAt(0) == '#' )return;
		String [] tokens = line.split("\\s+");
		for( int i = 0 ; i < tokens.length ; ++i )
  			tokens[i] = tokens[i].replace( '+' , ' ');
		cf.AddRow( tokens );
	}
}