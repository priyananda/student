function ret = findSlope(x1,y1,x2,y2)
	slope = (y2 - y1) / (x2 - x1);
	if(isinf(slope))
		intercept = x2;
	else
		intercept = y2 - slope * x2;
	end
	ret = [slope intercept];
	return;