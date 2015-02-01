int x;
String s;
bool b;
float f;

void x() //redeclaration error
{
}

void foo(int x, float y)
{
	int foo; //fine
	float b; //fine
	int y;   //redeclaration
	x = 20; //fine
	s = "a"; //fine
}

void main()
{
	bool x; //fine
	String x; //redeclaration
	k = 10; //undeclared
	f = 10; //fine
}

String k;
String f; //redeclaration
