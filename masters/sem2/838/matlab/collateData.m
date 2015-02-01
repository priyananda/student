function collateData(inp)

filename = sprintf('../data/%s',inp);
mat = dlmread(filename);

lineFileName = strrep(filename,'.txt','.line');
lineInfo = dlmread(lineFileName);

if length(lineInfo) == 0
	%fprintf('%s : line info missing\n',lineFileName);
	return;
end

if all(lineInfo) == 0
	%fprintf('%s : line info invalid\n',lineFileName);
	return;
end

% slope of our boundary
slope_m = -0.5;
intercept_m = 75;

slope_first   = findSlope(lineInfo(1,2),lineInfo(1,1),lineInfo(1,4),lineInfo(1,3));
delta_l_first = findDelta(slope_first(1),slope_first(2), mat, 0);
delta_m_first = findDelta(slope_m,intercept_m,mat,0);
delta_first   = delta_m_first - delta_l_first;

slope_second   = findSlope(lineInfo(2,2),lineInfo(2,1),lineInfo(2,4),lineInfo(2,3));
delta_l_second = findDelta(slope_second(1),slope_second(2), mat, 1);
delta_m_second = findDelta(slope_m,intercept_m,mat,1);
delta_second   = delta_m_second - delta_l_second;

shift = delta_first - delta_second;
fprintf('%s\t\t\t: %7.2f %7.2f %7.2f %7.2f | %7.2f %7.2f %7.2f %7.2f | %7.2f\n',filename,slope_first(1),delta_l_first,delta_m_first,delta_first,slope_second(1),delta_l_second,delta_m_second,delta_second,shift);