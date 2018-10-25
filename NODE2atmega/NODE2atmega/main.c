	
	#define F_CPU 16000000
	#define BAUD 9600
	#define UBRREG F_CPU/16/BAUD-1
    #include <avr/io.h>
    #include "UART.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <util/delay.h>

    int main(void){
	    UART_Init(UBRREG);

		int variabel = 1;

	    /* Replace with your application code */
	while(1){
			variabel++;
			if(variabel==300){
	    	printf("pliz funk:%d \n\r", variabel);
			_delay_ms(300);	
			}
			if(variabel>300){
				while(variabel!=0){
					variabel--;
					if(variabel==0){
					printf("pliz funk:%d \n\r", variabel);
					_delay_ms(300);	
					}
				}
			}
								
		    }

}