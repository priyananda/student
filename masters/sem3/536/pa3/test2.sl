//tests operator precedence

void someJunkFunction()
{
	int a;
	int b;
	float c;
	
	//should be a = (((((b *c) / d) + e) - 2) == 0);
	a = b * c / d + e - 2 == 0;
	//should be a = (-b + (c*d));
	a = -b + c * d;
	// a = ((a+b) *c)
	a = (a + b) * c;
	// a = (a - -b);
	a = a--b;
	// a = (a - ---------------b);
	a = a----------------b;
}
