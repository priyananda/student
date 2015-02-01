/**
 * CS 540 HW4 : Perceptron
 * author: priyananda (shenoy@cs.wisc.edu)
 * date: Nov 12 2008
 * random quote: 
 */
import java.io.BufferedReader;
import java.io.FileReader;

//single layer perceptron learning
public class Perceptron
{
	public static void main(String[] args)
	{
		if(args.length != 2){
			System.out.println("Argument missing.Format is\njava Perceptron trainingfile alpha");
			System.exit(1);
		}
		Perceptron tron = new Perceptron();
		tron.parse(args[0], Float.parseFloat(args[1]));
		tron.learn();
		tron.print();
	}
	
	//extracts examples from input file
	private void parse(String fileName, double alp)
	{
		this.alpha = alp;
		
		try{
			BufferedReader reader = new BufferedReader(new FileReader(fileName));
			int numExamples = Integer.parseInt(reader.readLine());
			int numVars = Integer.parseInt(reader.readLine());
			
			this.node = new LTU(numVars);
			this.examples = new Example[numExamples];
			
			String line = null;
			int i = 0;
			while((line = reader.readLine()) != null){
				String [] parts = line.split("\\s+");
				Example ex = new Example(numVars);
				for(int j = 0; j < numVars; ++j)
					ex.variables[j] = Double.parseDouble(parts[j]);
				ex.output = Integer.parseInt(parts[numVars]);
				examples[i++] = ex;
			}
			reader.close();
		}catch(Exception e){
			System.exit(1);
		}
	}
	//learns the weights
	private void learn()
	{
		int c = 0;
		while(true){
			boolean allCorrect = true;
			for(Example ex : examples){
				double actualOutput = node.evaluate(ex.variables);
				if( actualOutput == ex.output )
					continue;
				allCorrect = false;
				double error = ex.output - actualOutput;
				for(int i = 1 ; i < node.weights.length; ++i)
					node.weights[i] += alpha * error * ex.variables[i-1];
				node.weights[0] += alpha * error * -1;
			}
			if(allCorrect)
				break;
		}
	}
	//prints the weights
	private void print()
	{
		for(double w : node.weights)
			System.out.print(w + " ");
		System.out.println("");
	}
	
	//class to model a single linear threshold function
	private class LTU
	{
		public LTU(int numVars)
		{
			weights = new double[numVars+1];
			for(int i = 0 ; i <= numVars ; ++i)
				weights[i] = 0.0;
		}
		public int evaluate(double variables[])
		{
			double sum = -weights[0];
			for(int i = 0 ; i < variables.length; ++i)
				sum += variables[i] * weights[i+1];			
			return sum > 0.0 ? 1 : 0;
		}
		double weights[];
	}
	//class to model an example
	private class Example
	{
		public Example(int numVars)
		{
			variables = new double[numVars];
		}
		double output;
		double variables[]; 
	}
	
	private LTU node;
	private double alpha;
	private Example[] examples;
}
