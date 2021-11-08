/* Interprete.h   Definiciones del modulo de Interfaz de comandos */

#if !defined(INTERPRETE_H)

#define INTERPRETE_H

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "Varios.h"
#include <stdlib.h>

#define MSG_INT_SIZE 25

typedef struct Interprete_Control Interprete_Control;
struct Interprete_Control
{
   TaskHandle_t tarea;
   /* Area protegida con mutex */
   QueueHandle_t cola_com;

};



typedef  struct Interprete_mensaje Interprete_mensaje;
struct Interprete_mensaje
{
    char msg [MSG_INT_SIZE];
};


char Interprete_Inicie (Interprete_Control *interp_contp, UBaseType_t prioridad);
void Interprete_Procese (Interprete_Control *interp_contp);
BaseType_t Interprete_envie_mensaje(Interprete_Control *interp_contp, Interprete_mensaje *msg, TickType_t espera);


#endif
