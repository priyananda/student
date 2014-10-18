
#ifndef __PORTS__H__
#define __PORTS__H__
    #define u8 unsigned char
    #define u16 unsigned int
    #define u32 unsigned long
	#define COM1_BASE_ADDR 0x00400000 /* Gives the io address of the device installed at com1 */
	#define COM2_BASE_ADDR 0x00400002 /* Gives the io address of the device installed at com2 */
	#define COM3_BASE_ADDR 0x00400004 /* Gives the io address of the device installed at com3 */
	#define COM4_BASE_ADDR 0x00400006 /* Gives the io address of the device installed at com4 */
	#define COM1_TIMEOUT    0x0040007c /* address a time out in no. of seconds for COM1           */
	#define COM2_TIMEOUT    0x0040007d /* address a time out in no. of seconds for COM2            */
	#define COM3_TIMEOUT    0x0040007e /* address a time out in no. of seconds for COM3            */
	#define COM4_TIMEOUT    0x0040007f  /* address a time out in no. of seconds for COM4            */

	#define OPERATION_TIMED_OUT 0x80 /* operation timed out */
	#define TRANS_SHIFT_REG_EMPTY 0x40 /* Transmitter shift register empty */
	#define TRANS_HOLD_REG_EMPTY 0x20 /* Transmitter holding register empty */
	#define BR_SNGL_DT 0x10 /* Break signal detected */
	#define FRM_ERR_DT 0x08 /* Framing error detected */
	#define PAR_ERR_DT 0x04 /* Parity error detected */
	#define TRANS_OVRRUN 0x02 /* Transmitter overrun */
	#define DATA_PRESENT 0x01 /*Received data present */

	#define CARR_DT 0x80 /* Carrier detect */
	#define RING_IND 0x40/* Ring Indicator */
	#define DSR 0x20/* Data set ready */
	#define CTS 0x10/* Clear to send */
	#define DCD 0x08/* Delta carrier defect */
	#define RITE 0x04/* Ring indicator trailing edge */
	#define DDSR 0x02/* Delta data set ready */
	#define DCTS 0x01/*Delta clear to send */

	#define B0 0x1
	#define B1 0x2
	#define B2 0x4
	#define B3 0x8
	#define B4 0x10
	#define B5 0x20
	#define B6 0x40
	#define B7 0x80

	#define BAUD110 0
	#define BAUD150 B5
	#define BAUD300 B6
	#define BAUD600 (B5+B6)
	#define BAUD1200 B7
	#define BAUD2400 (B7+B5)
	#define BAUD4800 (B7+B6)
	#define BAUD9600 (B6+B7+B5)
	#define CLR_BAUD_RT (B4+B3+B2+B1+B0)

	#define NOPAR 0
	#define ODDPAR B3
	#define EVENPAR (B4+B3)
	#define CLRPAR (B7+B6+B5+B2+B1+B0)

	#define STP1 0
	#define STP2 B2
	#define CLRSTPBTS (B7+B6+B5+B4+B3+B1+B0)
	#define DATA7 B1
	#define DATA8 (B1+B0)
	#define CLRDATABTS (B7+B6+B5+B4+B3+B2)

	#define COM1 0
	#define COM2 1
	#define COM3 2
	#define COM4 3
	#define NOFREEPORT 255
    #define MAXPORTNO 4
    #define INVALIDPNO 1
    #define PORTUSED 2
    #define PORTUNUSED 0
	
	struct port_struct{
		u8 brkcode;
		u8 par;
		u8 stpbt;
		u8 dtbt;
		u8 lnspd;
		u8 pno;
		u8 *lnstat;
		u8 *mdmstat;
	};

	u8 isSerialPortInstalled(u8 portno);
	u8 serSerialPort(u8 portno,u32 ioadd);
	u8 getTimeOut(u8 portno);
	u8 setTimeOut(u8 portno,u8 time);
	u8 getSerLineStatus(u8 portno);
	u8 getSerMdmStatus(u8 portno);
	u8 sendChar(u8 portno,u8 data);
	u8 getChar(u8 portno);
	u8 init(const struct port_struct *ps);
	u8 portDetect();
	u8 getFreePort(u16 address);

#endif