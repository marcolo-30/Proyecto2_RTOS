/*
 * Interfaz.h
 *
 *  Created on: 10 nov. 2021
 *      Author: User
 */

#ifndef INTERFAZ_H_
#define INTERFAZ_H_

#include "FreeRTOS.h"
#include <queue.h>
#include <semphr.h>
#include <task.h>
#include <Varios.h>
#include "fsl_gpio.h"

typedef struct Interfaz_Control Interfaz_Control;
struct Interfaz_Control
   {
   TaskHandle_t tarea;
   /* Area protegida con mutex */
   };

char Interfaz_Inicie (Interfaz_Control *iucp, UBaseType_t prioridad);

void  Interfaz_Procese (Interfaz_Control *iucp);

BaseType_t Interface_send_message(Interfaz_Control *iucp, char *msg, TickType_t espera);



#endif /* INTERFAZ_H_ */
