// CS 540 : HW1
// author: priyananda( shenoy@cs.wisc.edu )
// date: 24 Sep 2008
// random quote: [The Dark Knight] The Joker: See, I'm not a monster...I'm just ahead of the curve. 

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;

//main class. just has the main method.
public class HW1
{
	//java HW1 <printTreeFlag> <trainFilename> <tuneFilename> <testFilename>
	//printTreeFlag is 1 or 0.
	//	1 - print tree, dont print predictions on the test set
	//	0 - dont print tree, print predictions on the test set
	//trainFilename - the file containing the training set
	//tuneFilename the file containing the tuning set, or NONE
	//testFilename - the file containing the test set
	public static void main(String[] args) throws Exception
	{
		//validate the options and call the processor
		if(args.length != 4){
			System.out.println("Invalid number of arguments");
			return;
		}
		if(! args[0].equals("0") && !args[0].equals("1") ){
			System.out.println("printTreeFlag must be 0 or 1");
			return;
		}
		if(! new File(args[1]).exists() ){
			System.out.println("trainFile doesn't exist");
			return;
		}
		if(!args[2].equals("NONE") && ! new File(args[2].replace("!", "")).exists()){
			System.out.println("tuneFile doesn't exist");
			return;
		}
		if(! new File(args[3]).exists() ){
			System.out.println("testFile doesn't exist");
			return;
		}
		DecisionTree tree = new DecisionTree(new DataSet(args[1]));
		
		if(!args[2].equals("NONE")){
			if(args[2].endsWith("!"))
				//this silently prunes multiple nodes
				tree.pruneMany(new DataSet(args[2].replace("!", "")));
				
				//this prints out accuracies
				//not to be called in submitted code
				//tree.pruneMany(
				//	new DataSet(args[2].replace("!", "")),
				//	new DataSet(args[3])
				//);
			else
				tree.prune(new DataSet(args[2]));
		}

		if(args[0].equals("1"))
			tree.print();
		else
			tree.predict(new DataSet(args[3]));
	}
}

//Each attribute of the example data
class Attribute
{
	//name of the attribute
	private String name;
	
	//list of possible values
	private String[] possibleValues;

	public Attribute(String name, int numAttrs)
	{
		this.name = name;
		this.possibleValues = new String[numAttrs];
	}
	
	public void setValue(int index, String val)
	{
		this.possibleValues[index] = val;
	}
	
	public String getValue(int index)
	{
		return this.possibleValues[index];
	}
	
	public int getIndex(String val)
	{
		for (int i = 0; i < possibleValues.length; i++)
			if(possibleValues[i].equals(val))
				return i;
		return -1;
	}
	
	public String getName()
	{
		return this.name;
	}
	
	public int getPossibleValuesCount()
	{
		return possibleValues.length;
	}
}

//Each record in the dataset. 
class Example
{
	//array of indices of the value for that attribute
	private int [] attributeValues;
	
	//index of the class to which this example belongs  
	private int    classValue;
	
	//constructor
	public Example(int classIndex, int numAttributes)
	{
		this.classValue = classIndex;
		this.attributeValues = new int[numAttributes];
	}
	
	//accessors
	public void setAttributeValue(int index,int val)
	{
		this.attributeValues[index] = val; 
	}
	
	public int getClassValue()
	{
		return this.classValue;
	}
	
	public int getAttributeValue(int attributeIndex)
	{
		return this.attributeValues[attributeIndex];
	}
}

//collection of examples
class DataSet
{
	//possible classes to which an example can belong. Two in our case
	private String [] classes;
	//all attributes
	private ArrayList<Attribute> attributes = new ArrayList<Attribute>();
	//all examples
	private ArrayList<Example> examples = new ArrayList<Example>();
	
	public DataSet(String fileName) throws IOException
	{
		BufferedReader reader = new BufferedReader(new FileReader(fileName));
		String line = null;
		Attribute attr = null;
		Example example = null;
		
		while((line = reader.readLine()) != null){
			//this takes care of any extra spaces
			line = line.replaceAll("\\s+", "");
			
			if(line.startsWith("//"))
				//comment, ignore this line
				continue;

			//split line based on ',' character
			String [] parts = line.split(",");
			
			if(parts[0].equals("%%"))
				//labels for classes
				this.classes = new String[]{parts[1],parts[2]};
			else if(parts[0].equals("##")){
				//attributes and possible values
				this.attributes.add(attr = new Attribute(parts[1], parts.length-2));
				for(int i = 2; i < parts.length; ++i)
					attr.setValue(i-2, parts[i]);
			}else{
				//examples
				examples.add(example = new Example(getClassIndex(parts[0]),attributes.size()));
				for(int i = 1; i < parts.length; ++i)
					example.setAttributeValue(i-1, attributes.get(i-1).getIndex(parts[i]));
			}
		}
		
		reader.close();
	}	
	
	//accessors
	public int getClassIndex(String className)
	{
		if(this.classes[0].equals(className))
			return 0;
		return 1;
	}
	
	public int getAttributeIndex(String name)
	{
		for(int i = 0; i < this.attributes.size(); ++i)
			if(this.attributes.get(i).getName().equals(name))
				return i;
		return -1;
	}
	
	public int getNumberOfAttributes()
	{
		return this.attributes.size();
	}
	
	public ArrayList<Example> getExamples()
	{
		return this.examples;
	}
	
	public String getClassLabel(int index)
	{
		return this.classes[index];
	}
	
	public Attribute getAttribute(int index)
	{
		return this.attributes.get(index);
	}
}

//represents a decision tree
class DecisionTree
{
	//root of the tree
	private TreeNode rootNode = null;
	//is the ith attribute under consideration?
	private boolean  attributeActive[];
	//reference to the training dataSet
	private DataSet  trainingSet;
	
	//builds the tree from the trainingSet
	public DecisionTree(DataSet trainingSet)
	{		
		this.trainingSet = trainingSet;
		attributeActive = new boolean[trainingSet.getNumberOfAttributes()];
		for(int i = 0; i < attributeActive.length; ++i)
			//initially all attributes are active.
			attributeActive[i] = true;
		
		rootNode = buildTree(trainingSet.getExamples(),0);
	}
	
	//prints the tree recursively
	public void print()
	{
		rootNode.print();
	}
	
	//eliminates one node of the tree. preference is  given to nodes
	//higher in the tree in case of tie.
	public boolean prune(DataSet tuningSet)
	{
		double bestAccuracy = accuracy(this.rootNode, tuningSet);
		TreeNode bestTree   = this.rootNode;
		boolean  didPrune   = false;
		
		for(TreeNode internalNode : this.internalNodes()){
			//clone the tree by just replacing the internal node
			//with leaf
			TreeNode newTree = this.cloneTree(tuningSet, internalNode);
			double newTreeAccuracy = accuracy(newTree, tuningSet);

			if(newTreeAccuracy > bestAccuracy){
				bestAccuracy = newTreeAccuracy;
				bestTree = newTree;
				didPrune = true;
			}
		}
		this.rootNode = bestTree;
		return didPrune;
	}
	
	//eliminates multiple nodes of the tree
	public void pruneMany(DataSet tuning)
	{
		while(prune(tuning));
	}
	
	//for extra credit, print accuracies
	public void pruneMany(DataSet tuning,DataSet testing)
	{
		int count = 0;
		
		do
			System.out.printf("%d %f %f %f\n",
				count++,
				accuracy(this.rootNode,this.trainingSet),
				accuracy(this.rootNode,tuning),
				accuracy(this.rootNode,testing)
			);
		while(prune(tuning));	
	}
	
	//tests the tree with a testing set
	public void predict(DataSet testingSet)
	{
		for(Example example : testingSet.getExamples()){
			TreeNode tn = this.rootNode;
			while(!tn.isLeaf()){
				int attrIndex = testingSet.getAttributeIndex(tn.name);
				int valueIndex = example.getAttributeValue(attrIndex);
				tn = tn.children.get(valueIndex);
			}
			//we've reached the leaf, so we have a class label
			System.out.println(tn.name);
		}

	}
	//a value in [0,1] corresponding to the accuracy
	public double accuracy(TreeNode treeRoot, DataSet testingSet)
	{
		double count = 0;
		for(Example example : testingSet.getExamples()){
			TreeNode tn = treeRoot;
			while(!tn.isLeaf()){
				int attrIndex = testingSet.getAttributeIndex(tn.name);
				int valueIndex = example.getAttributeValue(attrIndex);
				tn = tn.children.get(valueIndex);
			}
			//we've reached the leaf, so we have a class label
			if(example.getClassValue() == testingSet.getClassIndex(tn.name))
				//yeah! we guessed right
				++count;
		}
		return count / testingSet.getExamples().size();
	}
	
	//implementation of the algorithm in Fig 18.5
	private TreeNode buildTree(ArrayList<Example> examples, int defaultClassIndex)
	{
		if(examples.isEmpty())
			return new TreeNode(trainingSet.getClassLabel(defaultClassIndex));

		int defaultClassCount = 0;
		for(Example e : examples)
			if(e.getClassValue() == 0)
				++defaultClassCount;
		
		if(defaultClassCount == 0)
			//all examples are of second class
			return new TreeNode(trainingSet.getClassLabel(1));
		
		if(defaultClassCount == examples.size())
			//all examples are of second class
			return new TreeNode(trainingSet.getClassLabel(0));
		
		int majorityIndex = 0;
		if(defaultClassCount >= examples.size() - defaultClassCount)
			//majority is first class
			majorityIndex = 0;
		else
			majorityIndex = 1;
		
		int activeAttrributesCount = 0;
		for(boolean act : attributeActive)
			if(act)
				++activeAttrributesCount;
		
		if(activeAttrributesCount == 0)
			//no attributes exist
			return new TreeNode(trainingSet.getClassLabel(majorityIndex));
		
		int bestAttrIndex = chooseAttribute(examples);
		Attribute bestAttr = trainingSet.getAttribute(bestAttrIndex);
		
		TreeNode treeNode = new TreeNode(bestAttr.getName());
		
		//for each possible value of the best attribute
		for(int vi = 0 ; vi < bestAttr.getPossibleValuesCount(); ++vi){
			ArrayList<Example> matchingExamples =  filterExamples(examples,bestAttrIndex,vi);
			TreeNode kid = buildTree(matchingExamples, majorityIndex);
			treeNode.addChild(bestAttr.getValue(vi),kid);
		}
		return treeNode;
	}
	
	//returns {0,1} value depending on the majority
	//ties broken in favor of first class
	private int majority(ArrayList<Example> examples)
	{
		int defaultClassCount = 0;
		for(Example e : examples)
			if(e.getClassValue() == 0)
				++defaultClassCount;
		return defaultClassCount >= examples.size() - defaultClassCount ? 0 : 1;
	}
	
	//chooses the best attribute which is still under consideration 
	private int chooseAttribute(ArrayList<Example> examples)
	{
		double maxGain = 0;
		int    maxGainAttr = -1;
		for(int i = 0 ; i < trainingSet.getNumberOfAttributes(); ++i)
			if(attributeActive[i]){
				double iGain = gain(i,examples);
				if(maxGainAttr == -1 || iGain > maxGain){
					maxGainAttr = i;
					maxGain = iGain;
				}
			}
		if(maxGainAttr != -1)
			attributeActive[maxGainAttr] = false;
		return maxGainAttr;
	}
	
	//returns only those examples which have a certain value for a certain attribute 
	private ArrayList<Example> filterExamples(ArrayList<Example> ex, int attrIndex, int valueIndex)
	{
		ArrayList<Example> ret = new ArrayList<Example>();
		for(Example e : ex)
			if(e.getAttributeValue(attrIndex) == valueIndex)
				ret.add(e);
		return ret;
	}
	
	private double gain(int attrIndex , final ArrayList<Example> examples)
	{
		return entropy(examples) - remainder(attrIndex, examples);
	}
	
	//entropy of data
	private double entropy(final ArrayList<Example> examples)
	{
		double p_plus = 0, p_minus = 0;
		for(Example e : examples)
			if(e.getClassValue() == 0)
				++p_plus;
		p_plus /= examples.size();
		p_minus = 1.0 - p_plus;
		return - p_plus * log2(p_plus) - p_minus * log2(p_minus);
	}
	
	private double remainder(int attrIndex, final ArrayList<Example> examples)
	{
		double ret = 0;
		Attribute attr = trainingSet.getAttribute(attrIndex);
		for(int possibleValue = 0; possibleValue < attr.getPossibleValuesCount(); ++possibleValue){
			int matchingExamples = 0, positiveExamples = 0;
			for(Example e : examples)
				if(e.getAttributeValue(attrIndex) == possibleValue){
					++matchingExamples;
					if(e.getClassValue() == 0)
						++positiveExamples;
				}
			if(matchingExamples == 0)
				continue;
			double p_plus 	= (double) positiveExamples / matchingExamples;
			double p_minus 	= 1.0 - p_plus;
			double q_i 		= (double) matchingExamples / examples.size();
			ret += q_i * ( - p_plus * log2(p_plus) - p_minus * log2(p_minus) );
		}
		return ret;
	}
	
	//log to base 2
	private double log2(double number)
	{
		if(number == 0.0)
			return 0.0;
		return Math.log(number) / Math.log(2.0);
	}
	
	//BFS to get internal nodes in increasing height order
	private ArrayList<TreeNode> internalNodes()
	{
		ArrayList<TreeNode> ret = new ArrayList<TreeNode>();
		LinkedList<TreeNode> queue = new LinkedList<TreeNode>();
		queue.add(rootNode);
		while(!queue.isEmpty()){
			TreeNode node = queue.removeFirst();
			if(node.isLeaf())
				continue;
			ret.add(node);
			for(TreeNode kid : node.children)
				queue.add(kid);
		}
		return ret;
	}
	
	private TreeNode cloneTree(DataSet d,TreeNode nodeToBeReplaced)
	{
		return this.cloneNode(d.getExamples(), this.rootNode, nodeToBeReplaced);
	}
		
	private TreeNode cloneNode(ArrayList<Example> examples,TreeNode currentNode,TreeNode nodeToBeReplaced)
	{
		TreeNode ret = null;
		if(currentNode.equals(nodeToBeReplaced)){
			//replace this by a node corresponding to majority class of all examples
			ret = new TreeNode(this.trainingSet.getClassLabel(this.majority(examples)));
		}else{
			ret = new TreeNode(currentNode.name);
			if(currentNode.isLeaf())
				return ret;
			
			//clone the child nodes
			int currentAttributeIndex = this.trainingSet.getAttributeIndex(currentNode.name);
			for(int possibleValue = 0 ; possibleValue < currentNode.children.size(); ++possibleValue){
				TreeNode newKid = this.cloneNode(
					filterExamples(examples,currentAttributeIndex,possibleValue),
					currentNode.children.get(possibleValue),
					nodeToBeReplaced
				);
				ret.addChild(currentNode.edgeNames.get(possibleValue), newKid);
			}
		}
		return ret;
	}

	//Each node in the tree
	private class TreeNode
	{
		private String name;
		private ArrayList<String> edgeNames = new ArrayList<String>();
		private ArrayList<TreeNode> children = new ArrayList<TreeNode>();
		
		private TreeNode(String name)
		{
			this.name = name;
		}

		//recursively prints the tree
		private void print()
		{
			print(null,0);
		}
		
		//adds a child node to this node
		private TreeNode addChild(String edge, String name)
		{
			return this.addChild(edge, new TreeNode(name));
		}

		//adds a child node to this node
		private TreeNode addChild(String edge, TreeNode t)
		{
			this.edgeNames.add(edge);
			this.children.add(t);
			return t;
		}
		
		private boolean isLeaf()
		{
			return this.children.size() == 0;
		}
		
		private void print(String edgeLabel,int level)
		{
			//for indentation
			for(int i = 0; i < level; ++i)
				System.out.print("\t");
			if(edgeLabel == null)
				edgeLabel = "Root";
			if(this.isLeaf())
				//leaf
				System.out.printf("%s(%s)\n", edgeLabel,name);
			else{
				//non leaf
				System.out.printf("%s{%s}\n", edgeLabel,name);
				for(int i = 0 ; i < edgeNames.size(); ++i )
					this.children.get(i).print(edgeNames.get(i),level+1);
			}
		}
	}
}