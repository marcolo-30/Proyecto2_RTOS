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
//#define RAPIDISIMO

extern SemaphoreHandle_t mutexLCD;
int hora_ones,hora_tens,minuto_ones,minuto_tens;

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

	const TickType_t one_second = 10/ portTICK_PERIOD_MS;

	while (SI){

		vTaskDelayUntil( &xLastWakeTime, one_second );

		//Just for Show RTC is working
//		if(state==0){
//			GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_LED_RED_PIN,1);
//			state=1;
//		}
//		else{
//			GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_LED_RED_PIN,0);
//			state=0;
//		}
		if((cRtcsp->TiempoRTC.h.segundo)>59){
			cRtcsp->TiempoRTC.h.minuto ++;
			cRtcsp->TiempoRTC.h.segundo=0;
			RTC_envie(cRtcsp);
		}
		else{
			cRtcsp->TiempoRTC.h.segundo++;
		}


		if((cRtcsp->TiempoRTC.h.minuto)>59){
			cRtcsp->TiempoRTC.h.hora ++;
			cRtcsp->TiempoRTC.h.minuto=0;
			RTC_envie(cRtcsp);
		}


		if((cRtcsp->TiempoRTC.h.hora)>23){
			cRtcsp->TiempoRTC.f.dia ++;
			cRtcsp->TiempoRTC.h.hora=0;
			RTC_envie(cRtcsp);
		}






	}
}

void RTC_envie(RTC_Control *cRtcsp){



	//    int ones=anio%10;
	//    int tens = (anio/10)%10;
	//    int hundreds = (anio/100)%10;
	//    int thousands = (anio/1000);

	int hora=cRtcsp->TiempoRTC.h.hora;
	int minuto = cRtcsp->TiempoRTC.h.minuto;

	hora_ones=hora%10;
	hora_tens=(hora/10)%10;
	minuto_ones=minuto%10;
	minuto_tens=(minuto/10)%10;


    char trama[5]={hora_tens+48,hora_ones+48,':',minuto_tens+48,minuto_ones+48};



    xSemaphoreTake(mutexLCD, portMAX_DELAY);
   home();
    for (int i=0;i<=4;i++){

    	write_character(trama[i]);
    }

    xSemaphoreGive(mutexLCD);

}
