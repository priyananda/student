function ret = findDelta(slope,intercept,mat,which)
ret = 0;
for i = which * 15 + 1:1:(which + 1) * 15
	if isinf(slope)
		if mat(i,3) > intercept
			% on the right side
			if mat(i,4) == 1
				%first category
				ret = ret + mat(i,3) - intercept;
			end
		else
			% of the left side
			if mat(i,4) == 2
				%first category
				ret = ret + intercept - mat(i,3);
			end
		end
		continue
	end
	dist = (mat(i,2) - slope * mat(i,3) - intercept) / sqrt(1 + slope * slope);
	if intercept >= 0
		if dist < 0
			if mat(i,4) == 2
				ret = ret - dist;
			end
		else
			if mat(i,4) == 1
				ret = ret + dist;
			end
		end
	else
		if dist > 0
			if mat(i,4) == 2
				ret = ret + dist;
			end
		else
			if mat(i,4) == 1
				ret = ret - dist;
			end
		end
	end
end