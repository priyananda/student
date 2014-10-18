#include <stdio.h>
#include "ports.h"
/* Detects and prints messages about the ports on the system */
u8 portDetect(){
	u8 i=0;
	u16 far  *portbase = (u16 far  *)COM1_BASE_ADDR;
    for(i=0;i<4;i++){
		if(!(*portbase++))
			printf("\nCOM%d is not initialized",i+1);
		else
			printf("\nCOM%d is initialized",i+1);
    }
	return 0;
}

/* Sets a serial port at portno if uninitialized to ioadd */
u8 setSerialPort(u8 portno,u32 ioadd){
    if(portno >= MAXPORTNO){
        printf("\nInvalid port number");
        return INVALIDPNO;
    }
    if(*(((u16 far *)COM1_BASE_ADDR)+portno)){
        (*(((u16 far *)COM1_BASE_ADDR)+portno))=(u16)ioadd;
        return PORTUSED;
    }
    return PORTUNUSED;
}

/* Gets a free port to which a device can be bound */
u8 getFreePort(u16 address){
    u8 i=0;
    u16 far *portbase = (u16 far *)COM1_BASE_ADDR;
    for(i=0;i<4;i++){
                if(!(*portbase)){
			*portbase=address;
                        return i+1;
		}
                portbase++;
	}
	return NOFREEPORT;    
}

int main(){
    portDetect();
    return 0;
}    
