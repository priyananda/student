int num;

void a()
{
	int x;
	
	b();
	c(10,20.5,"abc",false);
	
	if(x == 0){
		x = 100 * x + 10;
	}
	
	if(x > 30 && x < 40){
		num = -x;
	}else{
		num = !x;
	}
	
	while(x < 10){
		x = num * x;
	}
	
	if( x > 0 ){
		while(num < 100){
			if(num > 10){
				x = 0;
			}else{
				x = 100;
			}
		}
	}
	
	write(x+ 10);
	
	if (b == -1) { x = 4+3*5-y; while (c) { y = y*2+x; } }

	
	return;
}

int dog;

void b()
{
}

void c(int xx, float yy, String zz, bool baba)
{
}

String cat;
