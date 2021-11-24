/* CtlEntradas.h   Definiciones del modulo de monitoreo de entradas */
#if !defined(CTLENTRADAS_H)
#define CTLENTRADAS_H
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "Varios.h"
#include "pin_mux.h"
#include "fsl_gpio.h"

#define CENT_NUM_ENTRADAS        8

typedef struct CEnt_Cfg_entrada CEnt_Cfg_entrada;
#define CENT_B_ACTIVO      0x01
#define CENT_B_ALARMA      0x02
#define CENT_TIPO_SUBIDA   'S'
#define CENT_TIPO_BAJADA   'B'
#define CENT_TIPO_PULSO    'P'

struct CEnt_Cfg_entrada
   {
   unsigned char banderas;
   char tipo;
   unsigned short ancho;
   };

typedef struct CEnt_Control CEnt_Control;
struct CEnt_Control
   {
   TaskHandle_t tarea;

   /* Area protegida con mutex */
   CEnt_Cfg_entrada t_cfg[CENT_NUM_ENTRADAS];
   
   SemaphoreHandle_t mutex_cfg;
   };

char CEnt_Inicie (CEnt_Control *cesp, UBaseType_t prioridad);
   
void CEnt_Procese (CEnt_Control *cesp);

void CEnt_Configure_evento(CEnt_Control *cesp, char entrada, char activo, char tipo, unsigned short ancho);

void CEnt_Configure_alarma(CEnt_Control *cesp, char entrada, char activa);

unsigned char readPort();

#endif
