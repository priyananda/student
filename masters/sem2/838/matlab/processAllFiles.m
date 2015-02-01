function processAllFiles()

files = dir('../data/*.txt');
numFiles = length(files)

for i = 1:1:numFiles
	readData(files(i).name);
end
