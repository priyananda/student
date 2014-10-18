int atoi(const char * ch){
	int sign = 0;
	int radix = 10;
	int value = 0;

	switch(*ch){
		case '-':
			ch++;sign = 1;break;
		case '+':ch++;break;
		case '0':
			if(ch[1] == 'x' || ch[1] == 'X'){
				radix = 16;
				ch += 2;
			}else{
				radix = 8;
				ch++;
			}
			break;
	}
	if(radix == 10){
		while(*ch >= '0' && *ch <= '9')
			value = value * 10 + (*ch++ - '0');
	}else if(radix == 8){
		while(*ch >= '0' && *ch <= '7')
			value = value * 8 + (*ch++ - '0');
	}else{
		while((*ch >= '0' && *ch <= '9') || (*ch >= 'A' && *ch <= 'F') || (*ch >= 'a' && *ch <= 'f'))
			if(*ch >= '0' && *ch <= '9')value = (*ch++ - '0') + value * 16;
			else if(*ch >= 'A' && *ch <= 'F')value = (*ch++ - 'A' + 10) + value * 16;
			else value = (*ch++ - 'a' + 10) + value * 16;
	}
	return sign?-value:value;
}
