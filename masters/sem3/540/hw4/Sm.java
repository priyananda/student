public class Sm
{
	public static void main(String args[])
	{
		double x = Double.parseDouble(args[0]);
		double sm = 1.0 / ( 1.0 + Math.exp(-x) );
		double smd = sm * ( 1 - sm );
		System.out.printf("sigmoid(%f) = %f, sigmoid'(%f) = %f\n", x,sm,x,smd);	
	}
}