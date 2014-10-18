#include <stdio.h>
#include <stdlib.h>

int main(int argc,char * argv[]){
	char * envVal;
	int i;
	for ( i = 1 ; i < argc ; ++i ){
		if ( !(envVal=getenv(argv[i])))
			{printf("%s doesnot exist\n",argv[i]);continue;}
		printf("%s :: %s\n",argv[i],envVal);
	}	
	return 0;
}
