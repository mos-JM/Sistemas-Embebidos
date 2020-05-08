/*
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A 
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR 
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION 
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE 
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO 
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO 
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE 
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY 
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * 
 *
 * This file is a generated sample test application.
 *
 * This application is intended to test and/or illustrate some 
 * functionality of your system.  The contents of this file may
 * vary depending on the IP in your system and may use existing
 * IP driver functions.  These drivers will be generated in your
 * SDK application project when you run the "Generate Libraries" menu item.
 *
 */
#include <stdio.h>
#include <time.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xbasic_types.h"
#include "xbram.h"
#include "bram_header.h"
#include "xbasic_types.h"
#include "xgpio.h"
#include "gpio_header.h"
#include "my_delay.h"
#include "banner_desp.h"
#include "infrarojos.h"
#include "motor_hw.h"
#include "keypad.h"
#include "i2c.h"

#include <xstatus.h>

#define XPAR_RS232_UART_1_BASEADDR 0x84000000
#define XPAR_ALTAVOZ_0_BASEADDR 0xC0A00000
#define INFRARED_BASEADDR 0xC7200000
#define BANNER_BASE_ADDR_0 0xC2E00000
#define MOTOR_BASE_ADDR_0 0xC0A20000
#define KEYPAD_BASE_ADDR_0 0xC9600000
#define BASE_ADDRESS_I2C 	0xC3000000

#define LECTURA_I2C_CMD 	0x00000000
#define ESCRITURA_I2C_CMD 	0x00000001
#define DIR_EXPANSOR 		0x00000072
#define DIR_MEMORIA 		0x000000A4
#define DIR_CONVERSOR 		0x00000092
#define DIR_LDR				0x00
#define DIR_LM35			0x01
#define DIR_POT2			0x02
#define DIR_POT1			0x03

#define NUMERO_BYTES    16
#define TRUE 1
#define FALSE 0

#define SILENCIO 	0x00000000
#define DO 			0x00000BAA
#define RE 			0x00000A64
#define MI 			0x00000942
#define FA 			0x000008BD
#define SOL 		0x000007C9
#define LA 			0x000006F0
#define SI 			0x0000062E

#define OCTAVA 	3
#define OCTAVA2 4

#define ABRE 1
#define CIERRA 0

#define ABRIR 0xA
#define CONFIRMAR 0xC
#define CERRAR 0xF
#define MUSICA 0xE
#define STOP 0xD
#define TEMP 0xB

void print(char *str);

const int code[][7]={

    { //C   0
        0x0F,0x10,0x10,0x10,0x10,0x10,0x0F,
    },
    { //o   1
        0x00,0x00,0x00,0x0E,0x11,0x11,0x0E,
    },
    { //d   2
        0x01,0x01,0x01,0x0F,0x11,0x11,0x1F,
    },
    { //e   3
        0x00,0x00,0x0E,0x11,0x1F,0x10,0x0F,
    },
    { //:   4
        0x00,0x04,0x00,0x00,0x00,0x04,0x00,
    },
    { //O   5
        0x1F,0x11,0x11,0x11,0x11,0x11,0x1F,
    },
    { //D   6
        0x1E,0x11,0x11,0x11,0x11,0x11,0x1E,
    },

    { //D   7
        0x1E,0x11,0x11,0x11,0x11,0x11,0x1E,
    },

    { //E   8
        0x1F,0x10,0x10,0x1F,0x10,0x10,0x1F,
    }
};

const int home[][7]={
    { //home    0
        0x04,0x0A,0x11,0x15,0x11,0x15,0x15,
    },
    { //espacio    1
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	},
    { //candado abierto 2
        0x00,0x0E,0x11,0x01,0x1F,0x1F,0x1F,
    },
    { //espacio    3
   		0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   	},
    { //:)      4
        0x00,0x0A,0x0A,0x0A,0x11,0x0E,0x00,
    }
};

const int intruso[][7]={
    { //:(      0
        0x00,0x0A,0x0A,0x00,0x0E,0x11,0x00,
    },
    { //espacio    1
   		0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   	},
    { //candado cerrado     2
        0x00,0x0E,0x11,0x11,0x1F,0x1F,0x1F,
    }
};

const int notas[][7]={
    { //nota1    0
        0x04,0x06,0x05,0x04,0x04,0x1C,0x1C,
    },
    { //espacio    1
       	0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     },
    { //nota2   2
        0x04,0x04,0x04,0x04,0x04,0x1C,0x1C,
    },
    { //espacio    3
       	0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     },
    { //nota3   4
        0x03,0x1D,0x11,0x11,0x11,0x1B,0x1B,
    }
};

const int reprod[][7]={
	{ //0			0
		0x0E,0x11,0x11,0x11,0x11,0x11,0x0E,
	},
    { //espacio    1
       	0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     },
	{ //1			2
		0x01,0x03,0x01,0x01,0x01,0x01,0x01,
	},
    { //espacio    3
       	0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     },
	{ //2			4
		0x0E,0x11,0x02,0x04,0x08,0x10,0x1F,
	},
	{ //espacio    5
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	},
    { //play   6
        0x08,0x0C,0x0E,0x0F,0x0E,0x0C,0x08,
    },
    { //espacio    7
    	0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    },
};

const int stop[][7]={
	{ //stop			0
		0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x00,
	}
};
const int temperatura[][7]={
	{ //0			0
		0x0E,0x11,0x19,0x15,0x13,0x11,0x0E,
	},
	{ //1			2
		0x01,0x03,0x01,0x01,0x01,0x01,0x01,
	},
	{ //2			4
		0x0E,0x11,0x02,0x04,0x08,0x10,0x1F,
	},
	{ //3			4
		0x0F,0x01,0x02,0x04,0x02,0x01,0x0F,
	},
	{ //4			4
		0x09,0x09,0x09,0x0F,0x01,0x01,0x01,
	},
	{ //5			4
		0x0F,0x08,0x08,0x0E,0x01,0x01,0x0E,
	},
	{ //6			4
		0x07,0x08,0x08,0x0E,0x09,0x09,0x0E,
	},
	{ //7			4
		0x0F,0x01,0x02,0x02,0x04,0x04,0x08,
	},
	{ //8			4
		0x0E,0x11,0x11,0x1F,0x11,0x11,0x0E,
	},
	{ //9			4
		0x0E,0x11,0x11,0x1F,0x01,0x01,0x0E
	},
	{ //			4
		0x07,0x05,0x07,0x00,0x00,0x00,0x00
	},
	{ //			4
		0x00,0x00,0x00,0x07,0x08,0x08,0x07
	}
};
const int bye[][7]={
	{ //B			0
		0x1E,0x11,0x11,0x1F,0x11,0x11,0x1E,
	},
	{ //y			1
		0x00,0x00,0x09,0x09,0x05,0x02,0x0C,
	},
	{ //e   2
	    0x00,0x00,0x0E,0x11,0x1F,0x10,0x0F,
	},
	{ //!   3
		0x0A,0x0A,0x0A,0x0A,0x0A,0x00,0x0A,
	}

};
  /*
    { //0
        0x0E,0x11,0x11,0x11,0x11,0x11,0x0E,
    },
    { //1
        0x01,0x03,0x01,0x01,0x01,0x01,0x01,
    },
    { //A
        0x0E,0x11,0x11,0x1F,0x11,0x11,0x0E,
    }
};*/

void my_delay(int delay){
	int i, j;
	for (i=0; i<delay; i=i+1)
		for (j=0; j<500; j=j+1){}
}

Xuint32 keyPadRead(){
	Xuint32 keyRead ;
	KEYPAD_mWriteReg( KEYPAD_BASE_ADDR_0,0, 0xFFFFFFFF );
	while(KEYPAD_mReadReg( KEYPAD_BASE_ADDR_0, 0) == 0xFFFFFFFF );

	keyRead = (KEYPAD_mReadReg( KEYPAD_BASE_ADDR_0, 0)) >> 28;
	return keyRead;
	}

void I2C_escritura(Xuint32 dato[], Xuint32 direccion, Xuint32 num_datos){
	int i;
	// ESCRITURA I2C
	while (I2C_mWriteFIFOFull(BASE_ADDRESS_I2C) == TRUE){}
	I2C_mWriteToFIFO(BASE_ADDRESS_I2C, 0, (Xuint32) ((num_datos << 16) + (direccion <<0) + ESCRITURA_I2C_CMD));

	for (i=0; i< (num_datos/4 + ((num_datos%4)!=0)); i=i+1)
	{   while (I2C_mWriteFIFOFull(BASE_ADDRESS_I2C) == TRUE){}
		I2C_mWriteToFIFO(BASE_ADDRESS_I2C, 0, (Xuint32) dato[i]);
	}
	my_delay(20);
}

void I2C_lectura(Xuint32 direccion,  Xuint32 num_datos, Xuint32 dato[]){
	int i;
	//LECTURA I2C

	while (I2C_mWriteFIFOFull(BASE_ADDRESS_I2C) == TRUE){}
	I2C_mWriteToFIFO(BASE_ADDRESS_I2C, 0, (Xuint32) ((num_datos << 16) + (direccion << 0) + LECTURA_I2C_CMD));
	for (i=0; i< (num_datos/4 + ((num_datos%4)!=0)); i++)
	{
	while (I2C_mReadFIFOEmpty(BASE_ADDRESS_I2C) == TRUE){}
	dato[i]= I2C_mReadFromFIFO(BASE_ADDRESS_I2C, 0);
	}
//	return dato;
}

/*
 * La dirección de giro se encuentra en slv_reg0(0);
 *  La señal de stop se encuentra en slv_reg0 (1);
 *  La señal de halfstep se encuentra en slv_reg0 (2);
 *  El número de pasos a girar está en slv_reg0 (4 to 7).
 */
void controlMotor(Xuint32 dirreccion,Xuint32 halfstep,Xuint32 numPasos){
	Xuint32 Data;
	Data = 0 ;
	Data= ((dirreccion << 31)|(halfstep << 29)|(numPasos << 25));
	MOTOR_HW_mWriteReg ( MOTOR_BASE_ADDR_0 , 0, Data );
	Data = MOTOR_HW_mReadReg ( MOTOR_BASE_ADDR_0 , 0);// saber si el motor esta girando o no
	while (!( Data & 0x40000000 )){
		Data = MOTOR_HW_mReadReg ( MOTOR_BASE_ADDR_0 , 0);
	}
}

void abrirCerrarHome(Xuint32 dir){ // sentido reloj ABRE(1). sino cierra(0)
	int i=0;
	for(i=0;i < 60;i++){ // numero de veces que se hacen los pasos
		controlMotor(dir,0,15);
	}
}





void ALTAVOZ_suena(Xuint32 nota, Xuint32 octava){

	MY_DELAY_mWriteSlaveReg0(XPAR_ALTAVOZ_0_BASEADDR, 0, nota << octava);
}

void ALTAVOZ_calla(){

	MY_DELAY_mWriteSlaveReg0(XPAR_ALTAVOZ_0_BASEADDR, 0, SILENCIO);

}

int getNumber (){

	Xuint8 byte;
	Xuint8 uartBuffer[16];
	Xboolean validNumber;
	int digitIndex;
	int digit, number, sign;
	int c;

	while(1){
		byte = 0x00;
		digit = 0;
		digitIndex = 0;
		number = 0;
		validNumber = XTRUE;

		//get bytes from uart until RETURN is entered

		while(byte != 0x0d && byte != 0x0A){
			byte = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
			uartBuffer[digitIndex] = byte;
			XUartLite_SendByte(XPAR_RS232_UART_1_BASEADDR,byte);
			digitIndex++;
		}

		//calculate number from string of digits

		for(c = 0; c < (digitIndex - 1); c++){
			if(c == 0){
				//check if first byte is a "-"
				if(uartBuffer[c] == 0x2D){
					sign = -1;
					digit = 0;
				}
				//check if first byte is a digit
				else if((uartBuffer[c] >> 4) == 0x03){
					sign = 1;
					digit = (uartBuffer[c] & 0x0F);
				}
				else
					validNumber = XFALSE;
			}
			else{
				//check byte is a digit
				if((uartBuffer[c] >> 4) == 0x03){
					digit = (uartBuffer[c] & 0x0F);
				}
				else
					validNumber = XFALSE;
			}
			number = (number * 10) + digit;
		}
		number *= sign;
		if(validNumber == XTRUE){
			return number;
		}
		print("This is not a valid number.\n\r");
	}
}



void defaultMusic(){
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300); print("DO\n\r");
	ALTAVOZ_suena(RE, OCTAVA);
	my_delay(300); print("RE\n\r");
	ALTAVOZ_suena(MI, OCTAVA);
	my_delay(300); print("MI\n\r");
	ALTAVOZ_suena(FA, OCTAVA);
	my_delay(300); print("FA\n\r");
	ALTAVOZ_suena(SOL, OCTAVA);
	my_delay(300); print("SL\n\r");
	ALTAVOZ_suena(LA, OCTAVA);
	my_delay(300); print("LA\n\r");
	ALTAVOZ_suena(SI, OCTAVA);
	my_delay(300); print("SI\n\r");
	ALTAVOZ_suena(DO, (OCTAVA-1));
	my_delay(300); print("DO\n\r");
	ALTAVOZ_calla();
	my_delay(300); print("--\n\r");
	ALTAVOZ_suena(DO, (OCTAVA-1));
	my_delay(300); print("DO\n\r");
	ALTAVOZ_suena(SI, OCTAVA);
	my_delay(300); print("SI\n\r");
	ALTAVOZ_suena(LA, OCTAVA);
	my_delay(300); print("LA\n\r");
	ALTAVOZ_suena(SOL, OCTAVA);
	my_delay(300); print("SL\n\r");
	ALTAVOZ_suena(FA, OCTAVA);
	my_delay(300); print("FA\n\r");
	ALTAVOZ_suena(MI, OCTAVA);
	my_delay(300); print("MI\n\r");
	ALTAVOZ_suena(RE, OCTAVA);
	my_delay(300); print("RE\n\r");
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300); print("DO\n\r");
	ALTAVOZ_calla();
}
void cucaracha(){
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(FA, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(LA, OCTAVA);
	my_delay(700);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(FA, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(LA, OCTAVA);
	my_delay(700);

	ALTAVOZ_suena(FA, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(FA, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(MI, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(MI, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(RE, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(RE, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300);

	ALTAVOZ_calla();
}

void cumple(){
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(RE, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(FA, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(MI, OCTAVA);
	my_delay(700);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(RE, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300);

	ALTAVOZ_suena(SOL, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(FA, OCTAVA);
	my_delay(700);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(LA, OCTAVA);
	my_delay(600);
	ALTAVOZ_suena(FA, OCTAVA);
	my_delay(300);

	ALTAVOZ_suena(MI, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(RE, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(600);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(LA, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(FA, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(SOL, OCTAVA);
	my_delay(300);
	ALTAVOZ_suena(FA, OCTAVA);
	my_delay(300);

	ALTAVOZ_calla();
}
void intrusoSonido(){
	ALTAVOZ_suena(SOL, OCTAVA);
	my_delay(200);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(500);
	ALTAVOZ_suena(SOL, OCTAVA);
	my_delay(200);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(500);
	ALTAVOZ_suena(SOL, OCTAVA);
	my_delay(200);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(500);
	ALTAVOZ_suena(SOL, OCTAVA);
	my_delay(200);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(500);
	ALTAVOZ_suena(SOL, OCTAVA);
	my_delay(200);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(500);
	ALTAVOZ_suena(SOL, OCTAVA);
	my_delay(200);
	ALTAVOZ_suena(DO, OCTAVA);
	my_delay(500);

	ALTAVOZ_calla();
}
void bannerWrite(Xuint32 fila, Xuint32 columna,Xuint32 dato){

	while(BANNER_DESP_mWriteFIFOFull(BANNER_BASE_ADDR_0));//Mientras la FIFO esta llena espero
	Xuint32 Data =0;
	Data = (( fila & 0xff) << (31-7)) + (( columna & 0xff) << (31-15)) + (( dato & 0xff) << (31-23));
	BANNER_DESP_mWriteToFIFO ( BANNER_BASE_ADDR_0 , 0, Data );
}

void bannerClear(){
	int i=0;
	int j;
	for (j = 0; j < 8; j++)
		for (i = 0; i<7; i++)
			bannerWrite(i,j,0);
}

void bannerPrintCode(){
    int i, j;
    for(j=0; j < 5; j++){
        for(i=0; i<7; ++i)
        	bannerWrite(i, j, code[j][i]);
    }
}

void bannerPrintHome(){
    int i, j;

    for(j=0; j < 5; j++){
        for(i=0; i<7; ++i)
        	bannerWrite(i, j, home[j][i]);

    }
}
void bannerReproductor(){
    int i, j;

    for(j=0; j < 8; j++){
        for(i=0; i<7; ++i)
        	bannerWrite(i, j, reprod[j][i]);

    }
}

void bannerPrintIntruso(){
	 int i, j;

	for(j=0; j < 3; j++){
		for(i=0; i<7; ++i)
			bannerWrite(i, j, intruso[j][i]);
	}
}

void bannerPrintNotas(){
	 int i, j;

	for(j=0; j < 5; j++){
		for(i=0; i<7; ++i)
			bannerWrite(i, j, notas[j][i]);
	}
}

void bannerPrintStop(){
	 int i, j;

	for(j=0; j < 1; j++){
		for(i=0; i<7; ++i)
			bannerWrite(i, j, stop[j][i]);
	}
}

void bannerPrintCerrado(){
	 int i;

	for(i=0; i<7; ++i)
		bannerWrite(i, 0, home[0][i]);
	for(i=0; i<7; ++i)
		bannerWrite(i, 2, intruso[2][i]);
}

void bannerPrintTemperatura(Xuint32 temp){
	Xuint32 coc , resto;
	coc = temp / 10;
	resto = temp % 10;
	 int i;

	for(i=0; i<7; ++i)
		bannerWrite(i, 0, temperatura[coc][i]);
	for(i=0; i<7; ++i)
		bannerWrite(i, 1, temperatura[resto][i]);
	for(i=0; i<7; ++i)
		bannerWrite(i, 2, temperatura[10][i]);
	for(i=0; i<7; ++i)
		bannerWrite(i, 3, temperatura[11][i]);
}

void bannerPrintBye(){
	 int i, j;

	for(j=0; j < 4; j++){
		for(i=0; i<7; ++i)
			bannerWrite(i, j, bye[j][i]);
	}
}

void reproductor(){
	bannerClear();
	bannerReproductor();

	Xuint32 selectMusic = keyPadRead();
	while (selectMusic != STOP){
		bannerClear();
		bannerPrintNotas();
		if(selectMusic == 0x0)
			defaultMusic();
		else if(selectMusic == 0x1)
			cumple();
		else if(selectMusic == 0x2)
			cucaracha();

		bannerClear();
		bannerReproductor();
		selectMusic = keyPadRead();
	}
	bannerClear();
	bannerPrintStop();
}

Xuint32 pedirCodigo (){
	Xuint32 codeUser = 0x0 , codeUserResult = 0;

	while (codeUser != 0xC){ //confirmar code
		codeUser = keyPadRead();
		if(codeUser <= 0x9){
			codeUserResult *= 10;
			codeUserResult += codeUser;
			xil_printf("codeUserResult: %d\n", codeUserResult );
		}

	}

	return codeUserResult;
}

Xuint32 temperaturaBuena(){

	Xuint8 datos[NUMERO_BYTES], datos2[NUMERO_BYTES];
	Xuint32 value, num_datos = 2;
	datos[0]=0x40 + DIR_LM35;
	datos[1]=0x00;  // Valor salida analógica

	I2C_escritura((Xuint32 *)(&datos), DIR_CONVERSOR, num_datos);

	num_datos=1;
	I2C_lectura(DIR_CONVERSOR,num_datos,(Xuint32 *)(&datos2)); //lectura sin sentido
	 my_delay (20);
	I2C_lectura(DIR_CONVERSOR,num_datos,(Xuint32 *)(&datos2)); //lectura sin sentido

	value=datos2[0];
	xil_printf("Valor escrito en los LED 0: %08x\r\n\n", value);
	/* value=datos2[1];

	xil_printf("Valor escrito en los LED 1: %08x\r\n\n", value);
	*/

	return value;
}

void resetI2C(){
	I2C_mReset(BASE_ADDRESS_I2C);
	I2C_mResetWriteFIFO(BASE_ADDRESS_I2C);
	I2C_mResetReadFIFO(BASE_ADDRESS_I2C);
}
/**
 * SISTEMA DE ASISTENCIA HOGAR: Sistema de seguridad, alarma , y musica en el hogar
 * Hola , inicio del sistema , Pedir code para entrar en el hogar , 3 intentos, 3
 * mal ,bloqueado. Bien entra en hogar , poner musica ,cambiar de tema .
 *  Me voy , pongo code y cierro. Vuelta a empezar.
 **/

const int CODEHOME = 14;

int main()
{

    Xuint32 keyCode, codeUser, intentos;
    Xuint32 codeUserResult;
    resetI2C();



    char acceso;
    while (1){

    	my_delay(10000);
    	bannerClear();
    	bannerPrintCerrado();

		acceso = FALSE; // flag de acceso

		resetI2C();

		keyCode = keyPadRead();
		print(keyCode);
		resetI2C();

		while(keyCode != ABRIR){ //imientras no pulse A (acceso) se queda aqui
			xil_printf("primero %d\n", keyCode);
			keyCode = keyPadRead();
			resetI2C();
		}

		bannerClear();
		bannerPrintCode();
		intentos = 0;

		while (intentos < 3 && !acceso){
			resetI2C();
		   codeUser = keyPadRead();

			codeUserResult = 0;
			while (codeUser != CONFIRMAR){ //confirmar code
				resetI2C();
				if(codeUser <= 0x9){
					codeUserResult *= 10;
					codeUserResult += codeUser;
					xil_printf("codeUserResult: %d\n", codeUserResult );
				}
				resetI2C();
				codeUser = keyPadRead();
			}
			if(codeUserResult == CODEHOME){
				acceso = TRUE;
				xil_printf("correcto\n");
			}
			else{
				xil_printf("intentos ++ %d\n", intentos);
				intentos++;

			}
		}
		bannerClear();
		if (acceso){
			abrirCerrarHome(ABRE);
			bannerPrintHome();

			Xuint32 keyHome;
			resetI2C();
			keyHome = keyPadRead();
			xil_printf("aqui  %d\n", keyHome);
			while (keyHome != ABRIR){
				resetI2C();
				if(keyHome == MUSICA){
					xil_printf("repro \n");
					reproductor();
					my_delay(10000);

				}
				else if(keyHome == TEMP ){

					Xuint32 temp = temperaturaBuena();
					xil_printf("Temperatura: %08x\r\n\n", temp);

					bannerClear();
					bannerPrintTemperatura(temp);
					/*//srand(time(NULL));
					temperatura = (rand() % (42));
					xil_printf("temperatura %d\n", temperatura);
					bannerClear();
					bannerPrintTemperatura(temperatura);*/
					my_delay(10000);
					//crear un numero random que me de la temperatura
				}
				bannerClear();
				bannerPrintHome();
				resetI2C();
				keyHome = keyPadRead();
				xil_printf("keyHome %d\n", keyHome);
			}
			xil_printf("aqui llego %d\n", keyHome);
			codeUserResult = 0;
			Xuint32 codeUserOut = 0;
			bannerClear();
			bannerPrintCode();
			while (codeUserOut != CODEHOME){ //confirmar code
				codeUserOut = 0;
				resetI2C();
				codeUserOut = pedirCodigo ();
				resetI2C();
			}
			bannerPrintBye();
			abrirCerrarHome(CIERRA);
			resetI2C();

		}
		else{
			bannerPrintIntruso();
			intrusoSonido();
		}

    }
    
    return 0;

}

