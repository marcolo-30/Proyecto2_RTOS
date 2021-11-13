/*
 * rtc.h
 *
 *  Created on: 11 nov. 2021
 *      Author: Diego Avellaneda
 */

#ifndef RTC_H_
#define RTC_H_

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "Varios.h"
#include "pin_mux.h"
#include "fsl_gpio.h"

typedef struct RTC_Control RTC_Control;
struct RTC_Control
   {
   TaskHandle_t tarea;
   //Estructura de tipo varios
   Tiempo TiempoRTC;
   };

char RTC_Inicie (RTC_Control *cRtcsp, UBaseType_t prioridad);

void RTC_Procese (RTC_Control *cRtcsp);

#endif /* RTC_H_ */
