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
extern SemaphoreHandle_t mutexLCD;

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

		 xSemaphoreTake(mutexLCD, portMAX_DELAY);
		 init_LCD_display();
		 xSemaphoreGive(mutexLCD);

		 int lcd_render_state=0;

		 char dato_cola;
	    for( ;; )
	    {
	    	//vTaskDelayUntil( &xLastWakeTime, lcd_time );

	    	if(lcd_render_state==0){

	    		xSemaphoreTake(mutexLCD, portMAX_DELAY);
		    	clear_and_home();
		    	//write_line("A.ProgF/H B.For");
		    	write_second_line();
		    	write_line("A. B. C. D.");
//		    	write_character('a');
//		    	imprimirA();
		    	xSemaphoreGive(mutexLCD);

		    	lcd_render_state=1;
	    	}
	    	// si se recibe algo de la cola estando en este estado

	    	if(lcd_render_state==1){
	    		if(uxQueueMessagesWaiting(ColaInterfaz)){///sobra
	    			xQueueReceive(ColaInterfaz,&dato_cola,0);//Retirar de una vez
//	    			xSemaphoreTake(mutexLCD, portMAX_DELAY);
//			    	clear_and_home();
//			    	 write_character(dato_cola);
//			    	 xSemaphoreGive(mutexLCD);

			    	 switch (dato_cola){
			    	 	 case 'A':
			    	 		xSemaphoreTake(mutexLCD, portMAX_DELAY);
			 		    	//clear_and_home();
			    	 		write_second_line();
			 		    	write_line("Programing State");
			 		    	xSemaphoreGive(mutexLCD);

			 		    	lcd_render_state=2;
			    	 		 break;
			    	 	 case 'B':
			    	 		xSemaphoreTake(mutexLCD, portMAX_DELAY);
				 		    //clear_and_home();
			    	 		write_second_line();
				 		    write_line("Mode Forzado");
				 		   xSemaphoreGive(mutexLCD);

				 		   lcd_render_state=2;
			    	 		 break;
			    	 	 case 'C':
			    	 		xSemaphoreTake(mutexLCD, portMAX_DELAY);
					 		 //clear_and_home();
			    	 		write_second_line();
					 		write_line("A/D Monitoreo");
					 		 xSemaphoreGive(mutexLCD);
					 		lcd_render_state=2;
			    	 		 break;
			    	 	 case 'D':
			    	 		xSemaphoreTake(mutexLCD, portMAX_DELAY);
					 		 //clear_and_home();
			    	 		write_second_line();
					 		write_line("Alarma");
					 		xSemaphoreGive(mutexLCD);
					 		lcd_render_state=2;
			    	 		 break;
			    	 	 default:
			    	 		xSemaphoreTake(mutexLCD, portMAX_DELAY);
					 		//clear_and_home();
			    	 		write_second_line();
					 		write_line("Wrong Key");
					 		vTaskDelay( lcd_time );
					 		xSemaphoreGive(mutexLCD);
					 		lcd_render_state=0;


			    	 }


	    			}
	    	}

	    	// yo que escriba en el teclado cuando este mostrando 0


	    }
}

