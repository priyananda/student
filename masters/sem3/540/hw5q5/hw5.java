/**
 * CS 540 HW5 : Bayesian Learning
 * author: priyananda (shenoy@cs.wisc.edu)
 * date: Nov 24 2008
 * random quote: 
 */

import java.io.File;
import java.io.FileReader;

public class hw5
{
	public static void main(String[] args)
	{
		if(args.length < 2){
			System.out.println("Format is:\njava hw5 trainset_directory testset_directory");
			System.exit(0);
		}
		
		BayesianClassifier classifier = new BayesianClassifier();			
		classifier.learn(args[0]);
		classifier.printProbabilities();
		classifier.printConfusionMatrix(args[1]);
	}
	static class BayesianClassifier
	{
		//calculate probabilities from existing test data
		public void learn(String folder)
		{
			int nEnglish, nSpanish, nJapanese, nTotal;
			int nCharEnglish = 0 ,nCharSpanish = 0,nCharJapanese = 0;
			
			int countEnglish[] = new int[NUM_CHARS];
			int countSpanish[] = new int[NUM_CHARS];
			int countJapanese[] = new int[NUM_CHARS];
			
			String [] englishFiles = new File(folder, "English").list();
			String [] spanishFiles = new File(folder, "Spanish").list();
			String [] japaneseFiles = new File(folder, "Japanese").list();
			
			nEnglish = englishFiles.length;
			nSpanish = spanishFiles.length;
			nJapanese = japaneseFiles.length;
			
			nTotal = nEnglish + nSpanish + nJapanese;
			
			//priors
			lpEnglish  = Math.log(pEnglish  = (double) nEnglish  / nTotal );
			lpSpanish  = Math.log(pSpanish  = (double) nSpanish  / nTotal );
			lpJapanese = Math.log(pJapanese = (double) nJapanese / nTotal );
			
			for(String file : englishFiles)
				nCharEnglish  += readFile(String.format("%s/%s/%s",folder,"English",file),countEnglish);
			for(String file : spanishFiles)
				nCharSpanish  += readFile(String.format("%s/%s/%s",folder,"Spanish",file),countSpanish);
			for(String file : japaneseFiles)
				nCharJapanese += readFile(String.format("%s/%s/%s",folder,"Japanese",file),countJapanese);
			
			//conditional probability P(char | english) etc
			for(int i = 0 ; i < NUM_CHARS; ++i){
				lpCharEnglish[i]  = Math.log(pCharEnglish[i]  = (double) countEnglish[i]  / nCharEnglish );
				lpCharSpanish[i]  = Math.log(pCharSpanish[i]  = (double) countSpanish[i]  / nCharSpanish );
				lpCharJapanese[i] = Math.log(pCharJapanese[i] = (double) countJapanese[i] / nCharJapanese );
			}
		}
		
		//(pretty) prints all the probabilities
		public void printProbabilities()
		{
			System.out.printf("P(English) = %f\nP(Spanish) = %f\nP(Japanese) = %f\n", pEnglish, pSpanish, pJapanese);
			System.out.println("Char(c)\tP(c|English)\tP(c|Spanish)\tP(c|Japanese)");
			for(int i = 0 ; i < NUM_CHARS - 1; ++i)
				System.out.printf("%c\t%f\t%f\t%f\n",
					(char)('a' + i),
					pCharEnglish[i],
					pCharSpanish[i],
					pCharJapanese[i]
				);
			System.out.printf("space\t%f\t%f\t%f\n",
				pCharEnglish[NUM_CHARS - 1],
				pCharSpanish[NUM_CHARS - 1],
				pCharJapanese[NUM_CHARS - 1]
			);
		}
		
		//checks classification for testing set
		public void printConfusionMatrix(String testingFolder)
		{
			int matrix[][] = new int [][]{{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
			
			for(String file : new File(testingFolder, "English").list())
				matrix[classify(String.format("%s/%s/%s",testingFolder,"English",file))][0]++;
			
			for(String file : new File(testingFolder, "Spanish").list())
				matrix[classify(String.format("%s/%s/%s",testingFolder,"Spanish",file))][1]++;
			
			for(String file : new File(testingFolder, "Japanese").list())
				matrix[classify(String.format("%s/%s/%s",testingFolder,"Japanese",file))][2]++;
			
			if( matrix[3][0] +  matrix[3][1] + matrix[3][2] != 0)
				System.out.println("Warning: some unclassified documents!");
			
			System.out.println("\t\tEnglish\tSpanish\tJapanese");
			System.out.printf("English\t\t%d\t%d\t%d\n", matrix[0][0], matrix[0][1], matrix[0][2]);
			System.out.printf("Spanish\t\t%d\t%d\t%d\n", matrix[1][0], matrix[1][1], matrix[1][2]);
			System.out.printf("Japanese\t%d\t%d\t%d\n",  matrix[2][0], matrix[2][1], matrix[2][2]);
		}
		
		//counts characters in a file
		private int readFile(String filename, int [] count)
		{
			int ret = 0;
			try{
				FileReader reader = new FileReader(filename);
				int c = 0;
				while((c = reader.read()) > 0){
					if( c == 10 || c == 13)
						continue;
					if( (char)c == ' ' )
						count[NUM_CHARS - 1]++;
					else
						count[c - 'a']++;
					++ret;
				}
				reader.close();
			}catch(Exception e){
				System.out.println("Exception:" + e);
			}
			return ret;
		}
		
		//classifies a document, 0 = English, 1 = Spanish, 2 = Japanese, 3 = unclassifiable
		private int classify(String documentName)
		{
			double lpDocEnglish = lpEnglish, lpDocSpanish = lpSpanish, lpDocJapanese = lpJapanese;
			try{
				FileReader reader = new FileReader(documentName);
				int c = 0;
				while((c = reader.read()) > 0){
					if(c == 10 || c == 13)
						continue;
					lpDocEnglish  += lpCharEnglish [ ((char)c == ' ') ? NUM_CHARS - 1 : c - 'a' ];
					lpDocSpanish  += lpCharSpanish [ ((char)c == ' ') ? NUM_CHARS - 1 : c - 'a' ];
					lpDocJapanese += lpCharJapanese[ ((char)c == ' ') ? NUM_CHARS - 1 : c - 'a' ];
				}
				reader.close();
			}catch(Exception e){
				System.out.println("Exception:" + e);
			}
			if(lpDocEnglish > lpDocSpanish && lpDocEnglish > lpDocJapanese)
				return 0;
			if(lpDocSpanish > lpDocEnglish && lpDocSpanish > lpDocJapanese)
				return 1;
			if(lpDocJapanese > lpDocSpanish && lpDocJapanese > lpDocEnglish)
				return 2;
			return 3;
		}
		
		//a-z and ' '
		public final int NUM_CHARS = 27;
		//prior probabilities
		public double pEnglish, pSpanish, pJapanese;
		//log prior probabilities
		public double lpEnglish, lpSpanish, lpJapanese;
		//conditional probabilities
		public double pCharEnglish[]  = new double[NUM_CHARS];
		public double pCharSpanish[]  = new double[NUM_CHARS];
		public double pCharJapanese[] = new double[NUM_CHARS];
		//log conditional probabilities
		public double lpCharEnglish[]  = new double[NUM_CHARS];
		public double lpCharSpanish[]  = new double[NUM_CHARS];
		public double lpCharJapanese[] = new double[NUM_CHARS];
	}
}