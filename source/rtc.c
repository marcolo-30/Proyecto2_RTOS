/*
 * rtc.c
 *
 *  Created on: 11 nov. 2021
 *      Author: Diego Avellaneda
 */
#include "rtc.h"
#include "fsl_debug_console.h"
#include "CtlSalidas.h"
#include "lcd.h"


#define LONG_STACK      (configMINIMAL_STACK_SIZE + 100)


char RTC_Inicie (RTC_Control *cRtcsp,
                  UBaseType_t prioridad)
   {
	   if ( xTaskCreate(RTC_Procese, "RTC_Procese", LONG_STACK, cRtcsp,
	                    prioridad, &(cRtcsp->tarea)) != pdPASS )
	      return NO;
	   // Arrancamos laestructura en un default

	   cRtcsp->TiempoRTC.f.anio = 2021;
	   cRtcsp->TiempoRTC.f.mes = 1;
	   cRtcsp->TiempoRTC.f.dia = 1;
	   cRtcsp->TiempoRTC.h.hora=0;
	   cRtcsp->TiempoRTC.h.minuto=0;
	   cRtcsp->TiempoRTC.h.segundo=0;


   return SI;
   };


void RTC_Procese (RTC_Control *cRtcsp){
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	const TickType_t one_second = 1000/ portTICK_PERIOD_MS;
	int state=0;
	while (SI){

		vTaskDelayUntil( &xLastWakeTime, one_second );

		//Just for Show RTC is working
		if(state==0){
			GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_LED_RED_PIN,1);
			state=1;
		}
		else{
			GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_LED_RED_PIN,0);
			state=0;
		}

	}
}
