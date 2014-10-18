package j3a.model;

public class Mapz
{
	public static void main(String [] raaido0) throws Exception{
		ObjectInputStream ois = new ObjectInputStream(
			new FileInputStream("first")
		);
		GameMap g = (GameMap) ois.readObject();
	}
}