#include "cmdparse.h"
#include <stdio.h>

#define DELIM (unsigned char)('|')
#define DOT   (unsigned char)('.')

void CommandParser::normalize(unsigned char * path){
	int wIndex = 0,rIndex = 0,nDots = 0,sep = 0;
	if(path[rIndex] != DELIM)	/* Error not starting with delim */
		return;
	while(path[rIndex]){
		if(nDots && path[rIndex] == DELIM){
			if(nDots == 2){
				--wIndex;
				while(wIndex && path[--wIndex] != DELIM);
			}else if(nDots == 1){
				wIndex--;
			}else{
				while(nDots){
					path[wIndex++] = DOT;
					nDots--;
				}
			}
			nDots = 0;
		}else if(path[rIndex] == DELIM){	/* Compress all pipes */
			path[wIndex++] = DELIM;
			rIndex++;
			while(path[rIndex] == DELIM)rIndex++;
			sep = 1;
		}else if(sep && path[rIndex] == DOT){
			nDots++;
			rIndex++;
		}else{
			while(nDots){
				path[wIndex++] = DOT;
				nDots--;
			}
			sep = 0;
			path[wIndex++] = path[rIndex++];
		}
	}
    if(wIndex == 1 && (nDots == 2 || nDots == 1)) nDots = 0;
	else if(nDots == 2){
		--wIndex;
		while(wIndex && path[--wIndex] != DELIM);
	}else if(nDots == 1)wIndex--;
	else if(nDots){
		while(nDots){
			path[wIndex++] = DOT;
			nDots--;
		}
	}
    if(wIndex == 0)path[wIndex++] = DELIM;
	if(path[wIndex - 1] == DELIM)
		if(wIndex == 1)path[wIndex++] = DOT;
		else --wIndex;
	path[wIndex] = 0;
}
