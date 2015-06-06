function readData(inp)

filename = sprintf('../data/%s',inp);
mat = dlmread(filename);
numRows = size(mat,1);

lineFileName = strrep(filename,'.txt','.line');
lineInfo = dlmread(lineFileName);

if length(lineInfo) == 0
	fprintf('%s line info missing\n',lineFileName);
	return;
end

if all(lineInfo) == 0
	fprintf('%s line info invalid\n',lineFileName);
	return;
end

before1Count = 1;
after1Count = 1;
before2Count = 1;
after2Count = 1;

for i = 1:1:numRows
	if  mat(i,1) == 0
		if mat(i,4) == 1
			before1S(before1Count) = mat(i,2);
			before1C(before1Count) = mat(i,3);
			before1Count = before1Count + 1;
		else
			before2S(before2Count) = mat(i,2);
			before2C(before2Count) = mat(i,3);
			before2Count = before2Count + 1;
		end
	else
		if mat(i,4) == 1
			after1S(after1Count) = mat(i,2);
			after1C(after1Count) = mat(i,3);
			after1Count = after1Count + 1;
		else
			after2S(after2Count) = mat(i,2);
			after2C(after2Count) = mat(i,3);
			after2Count = after2Count + 1;
		end
	end
end

bfilename = strrep(filename,'.txt','.first.png');
afilename = strrep(filename,'.txt','.second.png');

if before1Count + before2Count ~= 17
	fprintf('Invalid file: before : %s (%d %d)\n', filename,before1Count,before2Count);
	return;
end

if after1Count + after2Count ~= 17
	fprintf('Invalid file: after  : %s (%d %d)\n', filename,after1Count,after2Count);
	return;
end
fprintf('Processing file: %s \n',filename);

hold on;
xlim([0 100]);
ylim([0 100]);
if before1Count > 1
	before1C(before1Count) = 0;
	before1S(before1Count) = 0;

	k = convhull(before1C,before1S);
	fill(before1C(k),before1S(k),[1 0 0]);
	
	scatter(before1C,before1S,50,'+k');
end
if before2Count > 1
	before2C(before2Count) = 100;
	before2S(before2Count) = 100;

	k = convhull(before2C,before2S);
	fill(before2C(k),before2S(k),[0 0 1]);
	
	scatter(before2C,before2S,50,'+m');
end

%extremely inelegant code ahead
p1x = lineInfo(1,2);
p1y = lineInfo(1,1);
p2x = lineInfo(1,4);
p2y = lineInfo(1,3);
calcSlope = 1;

if p1x == p2x 
	% vertical line
	p1y = 100;
	p2y = 0;
	calcSlope = 0;
end

if p1y == p2y
	%horiz line
	p1x = 0;
	p2x = 100;
	calcSlope = 0;
end

if calcSlope == 1
	slope = (p2y - p1y) / (p2x - p1x);
	intercept = p1y - slope * p1x;

	x = [0  100];
	y = slope * x + intercept;
	plot(x,y, 'Color','black', 'LineWidth',3);
else
	line([p1x p2x],[p1y p2y], 'Color','black', 'LineWidth',3);
end
%end of dirty code

set(gcf, 'PaperUnits', 'points');
set(gcf, 'PaperPosition', [1 1 220 220]);
saveas(gcf,bfilename,'png');
close;

figure();
hold on;
xlim([0 100]);
ylim([0 100]);
if after1Count > 1
	after1C(after1Count) = 0;
	after1S(after1Count) = 0;
	
	k = convhull(after1C,after1S);
	fill(after1C(k),after1S(k),[1 0 0]);

	scatter(after1C,after1S,50,'+k');
end
if after2Count > 1
	after2C(after2Count) = 100;
	after2S(after2Count) = 100;
	
	k = convhull(after2C,after2S);
	fill(after2C(k),after2S(k),[0 0 1]);

	scatter(after2C,after2S,50,'+m');
end

%extremely inelegant code ahead .. repeated
p1x = lineInfo(2,2);
p1y = lineInfo(2,1);
p2x = lineInfo(2,4);
p2y = lineInfo(2,3);
calcSlope = 1;

if p1x == p2x 
	% vertical line
	p1y = 100;
	p2y = 0;
	calcSlope = 0;
end

if p1y == p2y
	%horiz line
	p1x = 0;
	p2x = 100;
	calcSlope = 0;
end

if calcSlope == 1
	slope = (p2y - p1y) / (p2x - p1x);
	intercept = p1y - slope * p1x;

	x = [0  100];
	y = slope * x + intercept;
	plot(x,y, 'Color','black', 'LineWidth',3);
else
	line([p1x p2x],[p1y p2y],'Color','black', 'LineWidth',3);
end
%end of dirty code


set(gcf, 'PaperUnits', 'points');
set(gcf, 'PaperPosition', [1 1 220 220]);
saveas(gcf,afilename,'png');
close;
