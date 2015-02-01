function processAllFiles()

warning off all

files = dir('../data/*.txt');
numFiles = length(files)

for i = 1:1:numFiles
	collateData(files(i).name);
end