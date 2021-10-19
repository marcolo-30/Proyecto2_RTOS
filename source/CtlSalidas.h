/* CtlSalidas.h   Definiciones del modulo de control de salidas */
#if !defined(CTLSALIDAS_H)

#define CTLSALIDAS_H
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "Varios.h"

#define CSAL_NUM_SALIDAS        8

typedef struct CSal_Evento CSal_Evento;
struct CSal_Evento
   {
   char entrada;
   size_t retardo;
   };
   
typedef struct CSal_Momento CSal_Momento;
#define CSAL_TP_M_ANIO        0
#define CSAL_TP_M_MES         1
#define CSAL_TP_M_SEMANA      2
#define CSAL_TP_M_DIA         3
#define CSAL_TP_M_HORA        4
struct CSal_Momento
   {
   char tipo;
   Tiempo t;
   };

typedef struct CSal_Encendido CSal_Encendido;
#define CSAL_B_ON_MOMENTO        0x01
#define CSAL_B_ON_EVENTO         0x02
struct CSal_Encendido
   {
   unsigned char banderas;
   CSal_Momento m;
   CSal_Evento e;
   };

typedef struct CSal_Apagado CSal_Apagado;
#define CSAL_B_OFF_MOMENTO       0x04
#define CSAL_B_OFF_EVENTO        0x08
#define CSAL_B_OFF_RETARDO       0x10
struct CSal_Apagado
   {
   unsigned char banderas;
   CSal_Momento m;
   CSal_Evento e;
   size_t retardo;
   };

typedef struct CSal_Cfg_salida CSal_Cfg_salida;
struct CSal_Cfg_salida
   {
   CSal_Encendido on;
   CSal_Apagado off;
   };

/* Estructura de un mensaje en la cola de eventos de la tarea */
typedef struct CSal_Mensaje CSal_Mensaje;
#define CSAL_TMSG_EVENTO         0
#define CSAL_TMSG_FORZADO        1
#define CSAL_TMSG_RTC            2
#define CSAL_TMSG_PERIODO        3
struct CSal_Mensaje
   {
   char tipo;
   union
      {
      char entrada;           /* 0 */
      struct
         {
         char encender;       /* 0 */
         char salida;         /* 1 */
         } forzado;
      Tiempo tiempo;          /* 0 */
      } v;
   };


typedef struct CSal_Control CSal_Control;
struct CSal_Control
   {
   TaskHandle_t tarea;

   /* Area protegida con mutex */
   CSal_Cfg_salida t_cfg[CSAL_NUM_SALIDAS];

   char modo_monitoreo;
   
   QueueHandle_t cola_ev;
   SemaphoreHandle_t mutex_cfg;
   };

char CSal_Inicie (CSal_Control *cscp, UBaseType_t prioridad);
   
void CSal_Procese (CSal_Control *cscp);

BaseType_t CSal_Envie_mensaje(CSal_Control *cscp, CSal_Mensaje *msga, TickType_t espera);

void CSal_Cambie_monitoreo(CSal_Control *cscp, char monitoreo);

void CSal_Configure_encendido(CSal_Control *cscp, char salida, CSal_Encendido *on);

void CSal_Configure_apagado(CSal_Control *cscp, char salida, CSal_Apagado *off);

#endif
