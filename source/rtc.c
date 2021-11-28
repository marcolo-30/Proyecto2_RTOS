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
extern SemaphoreHandle_t mutexRTC;
int hora_ones,hora_tens,minuto_ones,minuto_tens,anio_ones,anio_tens,anio_hundreds,anio_thousands,mes_ones,mes_tens,dia_ones,dia_tens;

static   uint8_t diasMes[]={31,29,31,30,31,30,31,31,30,31,30,31}; //Array para los dias del mes


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
	int flag_dato;

	const TickType_t one_second = 1000/ portTICK_PERIOD_MS;

	while (SI){

		vTaskDelayUntil( &xLastWakeTime, one_second );
		 flag_dato=0;
		 xSemaphoreTake(mutexRTC, portMAX_DELAY);
	//	cRtcsp->TiempoRTC.h.segundo++;
		(cRtcsp->TiempoRTC.h.segundo)+=60;  //Prueba con minutos
	//	(cRtcsp->TiempoRTC.h.minuto)+=60; //Prueba con horas
	//	(cRtcsp->TiempoRTC.h.hora)+=24;

		//Just for Show RTC is working
//		if(state==0){
//			GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_LED_RED_PIN,1);
//			state=1;
//		}
//		else{
//			GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_LED_RED_PIN,0);
//			state=0;
//		}
		//--------------------Segundos------------------------------------------
		if((cRtcsp->TiempoRTC.h.segundo)>59){
			cRtcsp->TiempoRTC.h.minuto ++;
			cRtcsp->TiempoRTC.h.segundo=0;
			flag_dato=1;

		}

		//--------------------Minutos------------------------------------------
		if((cRtcsp->TiempoRTC.h.minuto)>59){
			cRtcsp->TiempoRTC.h.hora ++;
			cRtcsp->TiempoRTC.h.minuto=0;
			flag_dato=1;

		}

		//--------------------Horas------------------------------------------
		if((cRtcsp->TiempoRTC.h.hora)>23){
			cRtcsp->TiempoRTC.f.dia ++;
			cRtcsp->TiempoRTC.h.hora=0;
			flag_dato=1;

		}

		//-------------------- Días ------------------------------------------
		//Los días dependen del mes actual
		if((cRtcsp->TiempoRTC.f.dia)>=diasMes[(cRtcsp->TiempoRTC.f.mes)-1]){//Enero es el mes 1 pero es el que yo quiero en la posicion 0
			cRtcsp->TiempoRTC.f.mes ++;
			cRtcsp->TiempoRTC.f.dia = 1;
			flag_dato=1;

		}

		//-------------------- Mes ------------------------------------------
		//Los días dependen del mes actual
		if((cRtcsp->TiempoRTC.f.dia)>=diasMes[(cRtcsp->TiempoRTC.f.mes)-1]){//Enero es el mes 1 pero es el que yo quiero en la posicion 0
			cRtcsp->TiempoRTC.f.mes ++;
			cRtcsp->TiempoRTC.f.dia = 1;
			flag_dato=1;
		}

		// ------------------ Anios------------------------------------------
		if( cRtcsp->TiempoRTC.f.mes > 12 ){
			cRtcsp->TiempoRTC.f.anio ++;
			 cRtcsp->TiempoRTC.f.mes = 1;
			 flag_dato=1;


			//Biciesto Library
			int bis =cRtcsp->TiempoRTC.f.anio;
			if (bis % 4 == 0 && bis % 100 != 0 || bis % 400 == 0)
				diasMes[1] = 29;
			else
				diasMes[1] = 28;
		}
		 xSemaphoreGive(mutexRTC);
		if(flag_dato){
			RTC_envie(cRtcsp);
			flag_dato=0;
		}

	}
}

/*Enviar datos al LCD*/
void RTC_envie(RTC_Control *cRtcsp){

	int anio=cRtcsp->TiempoRTC.f.anio;
	anio_ones=anio%10;
	anio_tens=(anio/10)%10;
	anio_hundreds=(anio/100)%10;
	anio_thousands=anio/1000;


	int mes=cRtcsp->TiempoRTC.f.mes;
	mes_ones=mes%10;
	mes_tens=(mes/10)%10;

	int dia=cRtcsp->TiempoRTC.f.dia;
	dia_ones=dia%10;
	dia_tens=(dia/10)%10;

	int hora=cRtcsp->TiempoRTC.h.hora;
	int minuto = cRtcsp->TiempoRTC.h.minuto;

	hora_ones=hora%10;
	hora_tens=(hora/10)%10;
	minuto_ones=minuto%10;
	minuto_tens=(minuto/10)%10;


    char trama[16]={anio_thousands+48,anio_hundreds+48,anio_tens+48,anio_ones+48,'/',mes_tens+48,mes_ones+48,'/',dia_tens+48,dia_ones+48,' ',hora_tens+48,hora_ones+48,':',minuto_tens+48,minuto_ones+48};


    //Mirar si el semaforo esta disponible, si no pues no entra
   if( xSemaphoreTake(mutexLCD, ( TickType_t ) 10)==pdTRUE ){
   home();
    for (int i=0;i<=16;i++){

    	write_character(trama[i]);
    }

    xSemaphoreGive(mutexLCD);
   };

}
