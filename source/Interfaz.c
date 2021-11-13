/*
 * Interfaz.c
 *
 *  Created on: 10 nov. 2021
 *      Author: Diego Avellaneda
 */


#include "Interfaz.h"
#include "lcd.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"

//Interfaz de Usuario

#define LONG_STACK      (configMINIMAL_STACK_SIZE + 166)




extern QueueHandle_t ColaInterfaz;


char Interfaz_Inicie (Interfaz_Control *iucp, UBaseType_t prioridad){

	if ( xTaskCreate(Interfaz_Procese, "Interfaz Usuario", LONG_STACK, iucp,
                    prioridad, &(iucp->tarea)) != pdPASS )
      return NO;


	return SI;
}

void Interfaz_Procese (Interfaz_Control *iucp){

//		char s='i';
//		char *line="hola rtos";
//		//char *lcd_msg = "LCD task\r\n";
		 TickType_t xLastWakeTime;
		 xLastWakeTime = xTaskGetTickCount();

		 const TickType_t lcd_time = 1000/ portTICK_PERIOD_MS;

		 init_LCD_display();
		 int lcd_render_state=0;

		 char dato_cola;
	    for( ;; )
	    {
	    	//vTaskDelayUntil( &xLastWakeTime, lcd_time );

	    	if(lcd_render_state==0){
		    	clear_and_home();
		    	write_line("A.ProgF/H B.For");
		    	write_second_line();
		    	write_line("C.Mon D.Alrm");
		    	lcd_render_state=1;
	    	}
	    	// si se recibe algo de la cola estando en este estado

	    	if(lcd_render_state==1){
	    		if(uxQueueMessagesWaiting(ColaInterfaz)){
	    			xQueueReceive(ColaInterfaz,&dato_cola,0);
			    	clear_and_home();
			    	 write_character(dato_cola);
			    	 switch (dato_cola){
			    	 	 case 'A':
			 		    	clear_and_home();
			 		    	write_line("Programing State");
			 		    	lcd_render_state=2;
			    	 		 break;
			    	 	 case 'B':
				 		    clear_and_home();
				 		    write_line("Mode Forzado");
				 		   lcd_render_state=2;
			    	 		 break;
			    	 	 case 'C':
					 		 clear_and_home();
					 		write_line("A/D Monitoreo");
					 		lcd_render_state=2;
			    	 		 break;
			    	 	 case 'D':
					 		 clear_and_home();
					 		write_line("Alarma");
					 		lcd_render_state=2;
			    	 		 break;
			    	 	 default:
					 		clear_and_home();
					 		write_line("Wrong Key");
					 		vTaskDelay( lcd_time );
					 		lcd_render_state=0;


			    	 }


	    			}
	    	}

	    	// yo que escriba en el teclado cuando este mostrando 0


	    }
}

