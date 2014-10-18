#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE * file;
	char ch;
	int i;
	file = fopen("out.txt","w");
	puts("Enter 16 characters :");
	for ( i = 0 ; i < 16 ; ++i ){
		fputc(fgetc(stdin),file);
	}
	fseek(file,48,SEEK_CUR);
	puts("Enter 16 more characters :");
	fflush(stdin);
	for ( i = 0 ; i < 16 ; ++i ){
		fputc(fgetc(stdin),file);
	}
	fclose(file);
	return 0;
}
