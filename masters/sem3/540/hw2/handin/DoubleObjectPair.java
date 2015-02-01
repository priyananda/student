
import java.util.*;

public class DoubleObjectPair implements Comparable {

	public double number;
	public Object object;

	public DoubleObjectPair(double d,Object o){
		number = d;
		object = o;
	}

	public int compareTo(Object o){
		DoubleObjectPair dop = (DoubleObjectPair)o;
		double diff = number - dop.number;
		if(diff < 0){
			return -1;
		}else if(diff > 0){
			return 1;
		}else{
			return 0;
		}
	}

}