/* CtlSalidas.c   Implementación del modulo de control de salidas */

#include "CtlSalidas.h"
#include "MKL46Z4.h"

//#include "Comunicacion.h"

//extern Com_Control c_comunicacion;
//extern
//#define PUERTO
extern QueueHandle_t ColaMonitoreo;

uint32_t PIN_SALIDAS [8] = {16,13,11,10,7,6,4,0};

#define LONG_STACK      (configMINIMAL_STACK_SIZE + 100)
#define MAX_MENSAJES    10

typedef struct Salida Salida;
#define SAL_E_ON             1
#define SAL_E_ON_RETARDADO   2
#define SAL_E_OFF            3
#define SAL_E_OFF_RETARDADO  4
struct Salida
   {
   char estado;
   unsigned short retardo; /* En segundos */
   };

#define FACTOR_RETARDO        60

char CSal_Inicie (CSal_Control *cscp,
                  UBaseType_t prioridad)
   {
   char i;
   CSal_Cfg_salida *csp;

   if ( xTaskCreate(CSal_Procese, "CtlSalida", LONG_STACK, cscp,
                    prioridad, &(cscp->tarea)) != pdPASS )
      return NO;

   for (csp = cscp->t_cfg, i =  CSAL_NUM_SALIDAS;
        i;
        ++ csp, --i)
      {
      csp->on.banderas = 0;
      csp->off.banderas = 0;
      };
   cscp->modo_monitoreo = NO;

   cscp->cola_ev = xQueueCreate(MAX_MENSAJES, sizeof(CSal_Mensaje));
   if (cscp->cola_ev == NULL)
      return NO;

   cscp->mutex_cfg = xSemaphoreCreateMutex();
   if (cscp->mutex_cfg == NULL)
      return NO;

   return SI;
   };


static char Es_momento (CSal_Momento *mp,
                        Tiempo *tp)
   {
   switch (mp->tipo)
      {
      case CSAL_TP_M_ANIO:
         if (mp->t.f.mes != tp->f.mes)
            return NO;
      case CSAL_TP_M_MES:
      case CSAL_TP_M_SEMANA:
         if (mp->tipo == CSAL_TP_M_SEMANA)
            {
            if (mp->t.s != tp->s)
               return NO;
            }
            else
            {
            if (mp->t.f.dia != tp->f.dia)
               return NO;
            };
      case CSAL_TP_M_DIA:
         if (mp->t.h.hora != tp->h.hora)
            return NO;
      case CSAL_TP_M_HORA:
         return (mp->t.h.minuto == tp->h.minuto);
      default:
         return NO;
      };

   return NO ; /* Aquí no debe llegar */
   };
   
void CSal_Procese (CSal_Control *cscp)
/* void CSal_Procese (void *pp) */
   {
   /* CSal_Control *cscp = (CSal_Control *) pp; */
   Salida salidas[CSAL_NUM_SALIDAS];
   Salida *sp;
   char i;
   CSal_Mensaje msj;
   CSal_Cfg_salida *csp;
   uint32_t  bits_on,
             bits_off;

   char modo_monitoreo;

   /* Condicion inicial */
   //PUERTO = 0;    igualar puertos a 0

   for (sp = salidas, i = CSAL_NUM_SALIDAS; i; ++sp, --i)
      {
      sp->estado = SAL_E_OFF;
      sp->retardo = 0;
      };
   
   while (SI)
      {
      if ( xQueueReceive(cscp->cola_ev, &msj, portMAX_DELAY) != pdTRUE )
         continue;

      bits_on = bits_off = 0;
      switch (msj.tipo)
         {
         case CSAL_TMSG_EVENTO:
            xSemaphoreTake(cscp->mutex_cfg, portMAX_DELAY);
            for (csp = cscp->t_cfg, sp = salidas, i =  0;
                 i < CSAL_NUM_SALIDAS;
                 ++ csp, ++sp, ++i)
               {
               switch (sp->estado)
                  {
                  case SAL_E_ON:
                  case SAL_E_OFF_RETARDADO:
                     if ( (csp->off.banderas & CSAL_B_OFF_EVENTO) &&
                          (csp->off.e.entrada == msj.v.entrada) )
                        {
                        if (csp->off.e.retardo)
                           {
                           unsigned short tmp = csp->off.e.retardo * FACTOR_RETARDO;
                           
                           if ( (sp->estado != SAL_E_OFF_RETARDADO) || (tmp < sp->retardo) )
                              sp->retardo = tmp;
                           sp->estado = SAL_E_OFF_RETARDADO;
                           }
                           else
                           {
                           sp->estado = SAL_E_OFF;
                           bits_off |= (1 << PIN_SALIDAS[i]);
                           };
                        };
                     break;
                  case SAL_E_OFF:
                  case SAL_E_ON_RETARDADO:
                     if ( (csp->on.banderas & CSAL_B_ON_EVENTO) &&
                          (csp->on.e.entrada == msj.v.entrada) )
                        {
                        if (csp->on.e.retardo)
                           {
                           unsigned short tmp = csp->on.e.retardo * FACTOR_RETARDO;
                           
                           if ( (sp->estado != SAL_E_ON_RETARDADO) || (tmp < sp->retardo) )
                              sp->retardo = tmp;
                           sp->estado = SAL_E_ON_RETARDADO;
                           }
                           else
                           {
                           if (csp->off.banderas & CSAL_B_OFF_RETARDO)
                              {
                              sp->estado = SAL_E_OFF_RETARDADO;
                              sp->retardo = csp->off.retardo * FACTOR_RETARDO;
                              }
                              else
                              sp->estado = SAL_E_ON;
                           bits_on |= (1 << PIN_SALIDAS[i]);
                           };
                        };
                     break;
                  };
               };
            xSemaphoreGive(cscp->mutex_cfg);
			break;
		 case CSAL_TMSG_FORZADO:
            sp = salidas + msj.v.forzado.salida;
            /* sp = &(salidas[msj.v.forzado.salida]); */
            if (msj.v.forzado.encender)
               { /* Se enciende */
               xSemaphoreTake(cscp->mutex_cfg, portMAX_DELAY);
               csp = cscp->t_cfg + msj.v.forzado.salida;
               if (csp->off.banderas & CSAL_B_OFF_RETARDO)
                  {
                  sp->estado = SAL_E_OFF_RETARDADO;
                  sp->retardo = csp->off.retardo * FACTOR_RETARDO;
                  }
                  else
                  sp->estado = SAL_E_ON;
               xSemaphoreGive(cscp->mutex_cfg);
               bits_on |= (1 << PIN_SALIDAS[msj.v.forzado.salida]);
               }
               else
               { /* Se apaga */
               sp->estado = SAL_E_OFF;
               bits_off |= (1 << PIN_SALIDAS[msj.v.forzado.salida]);
               };
			break;
		 case CSAL_TMSG_RTC:
            xSemaphoreTake(cscp->mutex_cfg, portMAX_DELAY);
            for (csp = cscp->t_cfg, sp = salidas, i =  0;
                 i < CSAL_NUM_SALIDAS;
                 ++ csp, ++sp, ++i)
               {
               switch (sp->estado)
                  {
                  case SAL_E_ON:
                  case SAL_E_OFF_RETARDADO:
                     if ( (csp->off.banderas & CSAL_B_OFF_MOMENTO) &&
                          Es_momento(&(csp->off.m), &(msj.v.tiempo)) )
                        {
                        sp->estado = SAL_E_OFF;
                        bits_off |= (1 << PIN_SALIDAS[i]);
                        };
                     break;
                  case SAL_E_OFF:
                  case SAL_E_ON_RETARDADO:
                     if ( (csp->on.banderas & CSAL_B_ON_MOMENTO) &&
                          Es_momento(&(csp->on.m), &(msj.v.tiempo)) )
                        {
                        if (csp->off.banderas & CSAL_B_OFF_RETARDO)
                           {
                           sp->estado = SAL_E_OFF_RETARDADO;
                           sp->retardo = csp->off.retardo * FACTOR_RETARDO;
                           }
                           else
                           sp->estado = SAL_E_ON;
                        bits_on |= (1 << PIN_SALIDAS[i]);
                        };
                     break;
                  };
               };
            xSemaphoreGive(cscp->mutex_cfg);
			break;
		 case CSAL_TMSG_PERIODO:
            xSemaphoreTake(cscp->mutex_cfg, portMAX_DELAY);
            for (csp = cscp->t_cfg, sp = salidas, i =  0;
                 i < CSAL_NUM_SALIDAS;
                 ++ csp, ++sp, ++i)
               {
               switch (sp->estado)
                  {
                  case SAL_E_OFF_RETARDADO:
                     --(sp->retardo);
                     if ( !(sp->retardo) )
                        {
                        sp->estado = SAL_E_OFF;
                        bits_off |= (1 << PIN_SALIDAS[i]);
                        };
                     break;
                  case SAL_E_ON_RETARDADO:
                     --(sp->retardo);
                     if ( !(sp->retardo) )
                        {
                        if (csp->off.banderas & CSAL_B_OFF_RETARDO)
                           {
                           sp->estado = SAL_E_OFF_RETARDADO;
                           sp->retardo = csp->off.retardo * FACTOR_RETARDO;
                           }
                           else
                           sp->estado = SAL_E_ON;
                        bits_on |= (1 << PIN_SALIDAS[i]);
                        };
                     break;
                  };
               };
            xSemaphoreGive(cscp->mutex_cfg);
            break;
		 };
         
      /* Enciende o apaga bits */
      //PUERTO = (PUERTO & ~bits_off) | bits_on;   Manejo de puertos
      PTC->PSOR = bits_on; /*Set Logic 1*/
      PTC->PCOR = bits_off; /*Set Logic 0*/

      xSemaphoreTake(cscp->mutex_cfg, portMAX_DELAY);
      modo_monitoreo = cscp->modo_monitoreo;
      xSemaphoreGive(cscp->mutex_cfg);
      
      if (modo_monitoreo)
         {
         char txt[5];
         
         txt[0] = 'S';
         txt[3] = '\n';
         txt[4] = '\0';
         for (i =  0; i < CSAL_NUM_SALIDAS; ++i)
            {
            if (bits_on & (1 << i))
               {
               txt[1] = '0' + i;
               txt[2] = '1';

               //Com_Tx_texto(&c_comunicacion, txt, portMAX_DELAY);
               for(i=0;i<5;i++){

            	   xQueueSend(ColaMonitoreo,(void *)txt[i],0);
               }

               };
            if (bits_off & (1 << i))
               {
               txt[1] = '0' + i;
               txt[2] = '0';

               //Com_Tx_texto(&c_comunicacion, txt, portMAX_DELAY);
               for(i=0;i<5;i++){

				    xQueueSend(ColaMonitoreo,(void *)txt[i],0);

               }
               };
            };




         };
      };
   };

BaseType_t CSal_Envie_mensaje (CSal_Control *cscp,
                               CSal_Mensaje *msg,
                               TickType_t espera)
   {
   return xQueueSend(cscp->cola_ev, msg, espera);
   };

void CSal_Cambie_monitoreo (CSal_Control *cscp, 
                            char monitoreo)
   {
   xSemaphoreTake(cscp->mutex_cfg, portMAX_DELAY);
   cscp->modo_monitoreo = monitoreo;
   xSemaphoreGive(cscp->mutex_cfg);
   };

void CSal_Configure_encendido (CSal_Control *cscp,
                               char salida,
                               CSal_Encendido *on)
   {
   xSemaphoreTake(cscp->mutex_cfg, portMAX_DELAY);
   cscp->t_cfg[salida].on = *on;
   xSemaphoreGive(cscp->mutex_cfg);
   };

void CSal_Configure_apagado (CSal_Control *cscp,
                             char salida,
                             CSal_Apagado *off)
   {
   xSemaphoreTake(cscp->mutex_cfg, portMAX_DELAY);
   cscp->t_cfg[salida].off = *off;
   xSemaphoreGive(cscp->mutex_cfg);

   };
