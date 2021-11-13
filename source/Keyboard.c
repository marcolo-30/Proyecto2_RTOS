/*
 * Keyboard.c
 *
 *  Created on: 8 nov. 2021
 *      Author: Diego Avellaneda
 */


#include "Keyboard.h"
#include "fsl_debug_console.h"
#include "Interfaz.h"
#include "pin_mux.h"
#include <queue.h>

#define LONG_STACK      (configMINIMAL_STACK_SIZE + 166)

extern QueueHandle_t ColaKeyboard;
extern QueueHandle_t ColaInterfaz;

char Keyboard_Inicie (Keyboard_Control *cKey, UBaseType_t prioridad)
{

	   if ( xTaskCreate(Keyboard_Procese, "Keyboard_Procese", LONG_STACK, cKey,
	                    prioridad, &(cKey->tarea)) != pdPASS )
	      return NO;

   return SI;
};

void Keyboard_Procese (Keyboard_Control *cKey){
	uint32_t columns[] = {0,0,0,0};
		 TickType_t xLastWakeTime;
		 //const TickType_t xFrequency = 10;
		 xLastWakeTime = xTaskGetTickCount();
		 const TickType_t time_pin = 15/ portTICK_PERIOD_MS;


		 // Cicle of having different frequency
		 uint8_t previous_key_pressed[4][4] = {
				 {0,0,0,0},
				 {0,0,0,0},
				 {0,0,0,0},
				 {0,0,0,0}
		 };

		 uint8_t key_pressed[4][4] = {

				 {'1','2','3','A'},
				 {'4','5','6','B'},
				 {'7','8','9','C'},
				 {'*','0','#','D'},

		 };

		 int coordinates[]= {10,10};
		 int flag_pressed = 0;

	     for( ;; )
	     {
	         // In the first cicle jum move into the different outputs
	    	 for(int i = 0; i < 4 ; i++){

	    		 switch (i){
	    		 case 0:
	    			 GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_row1_PIN,1);
	    			 GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_row2_PIN,0);
	    			 GPIO_WritePinOutput(GPIOD,BOARD_INITPINS_row3_PIN,0);
	    			 GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_row4_PIN,0);

	    			 //Read which pin have the input in

	    			 break;
	    		 case 1:
	    			 GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_row1_PIN,0);
	    			 GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_row2_PIN,1);
	    			 GPIO_WritePinOutput(GPIOD,BOARD_INITPINS_row3_PIN,0);
	    			 GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_row4_PIN,0);


	    			 break;
	    		 case 2:
	    			 GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_row1_PIN,0);
	    			 GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_row2_PIN,0);
	    			 GPIO_WritePinOutput(GPIOD,BOARD_INITPINS_row3_PIN,1);
	    			 GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_row4_PIN,0);


	    			 break;
	    		 case 3:
	    			 GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_row1_PIN,0);
	    			 GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_row2_PIN,0);
	    			 GPIO_WritePinOutput(GPIOD,BOARD_INITPINS_row3_PIN,0);
	    			 GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_row4_PIN,1);

	    			 break;

	    		 }

	    		 vTaskDelayUntil( &xLastWakeTime, time_pin );


	    		 // Go over in each Digital input checking the current value
	    		 columns[0]= GPIO_ReadPinInput(GPIOA,BOARD_INITPINS_column1_PIN);
	    		 columns[1]= GPIO_ReadPinInput(GPIOA,BOARD_INITPINS_column2_PIN);
	    		 columns[2]= GPIO_ReadPinInput(GPIOC,BOARD_INITPINS_column3_PIN);
	    		 columns[3]= GPIO_ReadPinInput(GPIOC,BOARD_INITPINS_column4_PIN);

	    		 for(int j = 0; j < 4 ; j++){

						if(columns[j]==1 && previous_key_pressed[i][j]==0){

							coordinates[0]=i;
							coordinates[1]=j;
							flag_pressed=1;

	    			}

	    				previous_key_pressed[i][j]=columns[j];
	    		 }

	    	 }

	    	 if(flag_pressed){

	    		 // Enviar a la cola de la interzaz de usuario
	    		 xQueueSend(ColaKeyboard,(void *)&key_pressed[coordinates[0]][coordinates[1]],0);
	    		 xQueueSend( ColaInterfaz,(void *)&key_pressed[coordinates[0]][coordinates[1]],0);

				flag_pressed=0;
	    	 }

	     }
}
