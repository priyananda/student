CS 838 Computational Cognitive Science
Spring 2008

Final Project of Priyananda Shenoy (shenoy@cs.wisc.edu).
Semi supervised classification in two dimensions.

How to get it to work:
1. Set up a database
	a. run 'schema.sql' on a postgres DB. This will generate the tables.
	b. change the parameters in 'readdb.pl' and 'code\common.php' to
		point to the correct DB.
2. Setup the web app
	a. the 'code' directory contains all the code for the web application.
	b. the 'images' subfolder under the 'code' folder has all the 
		generated images.
3. Read the data from the DB
	a. Run 'readdb.pl'. It should dump all the data in the DB into files
		in the 'data' folder.
4. Generate decision boundaries
	a. Run 'matlab/createLines.m' in Matlab. This generates files with
		extension '.line' for each subject.
5. Generate images for the data(optional)
	a. Run 'matlab/processAllData.m' in Matlab. This should generate two
	images per subject in the 'data' folder.
6. Process the data
	a. Run 'matlab/collateAll.m' in Matlab. This should dump the calculated
	values for each subject on the screen.

Acknowledgements
The images were generated using YkImageTools
(http://www.cns.atr.jp/~kmtn/imageMatlab/index.html)