void f()
{
}

void g(int x,String y, float z, bool w)
{
}

void main()
{
	int ivar;
	float fvar;
	bool bvar;
	String svar;

	f = 3; 		//Assignment to a function
	ivar = f;	//Assignment from a function
	write(f);	//Attempt to write a function
	
	if(f == g){f();}	//Comparison between two functions
	if(f != g){f();}	//Comparison between two functions
	if(f < g){f();}	//Comparison between two functions
	if(f > g){f();}	//Comparison between two functions
	if(f >= g){f();}	//Comparison between two functions
	if(f <= g){f();}	//Comparison between two functions

	ivar("a");	//Attempt to call a non-function
	g();		//Function call with wrong number of args
	g(1,1,1,1);	//Type of actual does not match type of formal
	
	ivar = bvar + svar;	//Arithmetic operator applied to non-numeric operand(x2)
	ivar = true + "";	//Arithmetic operator applied to non-numeric operand(x2)
	
	if(bvar > true){f();}	//Relational operator applied to non-numeric operand(x2)
	if(bvar < true){f();}	//Relational operator applied to non-numeric operand(x2)
	if(bvar >= true){f();}	//Relational operator applied to non-numeric operand(x2)
	if(bvar <= true){f();}	//Relational operator applied to non-numeric operand(x2)

	if(ivar && fvar){f();}	//Logical operator applied to non-bool operand(x2)
	if(ivar || fvar){f();}	//Logical operator applied to non-bool operand(x2)
	if(! fvar){f();}			//Logical operator applied to non-bool operand

	if( fvar ){f();}			//Non-bool expression used as an if condition
	if( "abc" ){f();}		//Non-bool expression used as an if condition
	if( 10 ){f();}			//Non-bool expression used as an if condition

	while(fvar){f();}		//Non-bool expression used as a while condition
	while("abc"){f();}		//Non-bool expression used as a while condition
	while(10){f();}			//Non-bool expression used as a while condition

	if(ivar == 20.0){f();}	//typemismatch
	if(bvar != "abc"){f();}	//typemismatch
	ivar = "abc";		//typemismatch
	fvar = ivar;		//typemismatch
	ivar = 10 + 20.0;	//typemismatch
	bvar = ivar < fvar;	//typemismatch

	ivar = (true + 3) * 4;			//Arithmetic operator applied to non-numeric operand
	bvar = true && (false || 3);	//Logical operator applied to non-bool operand

	f = f + f;
} 
