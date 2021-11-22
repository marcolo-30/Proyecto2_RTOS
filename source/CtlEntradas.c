/* CtlEntradas.c   Implementaci�n del modulo de monitoreo de entradas */

//#include "Comunicacion.h"
#include "CtlEntradas.h"
#include "CtlSalidas.h"
#include "MKL46Z4.h"


//extern Com_Control c_comunicacion;
extern CSal_Control c_salidas;
extern char LCDB;


#define PUERTO          GPIOE

#define LONG_STACK      (configMINIMAL_STACK_SIZE + 50)

#define PERIODO_1SEG    400

uint32_t PIN_Entradas [8] = {2U,3U,6U,16U,17U,18U,19U,31U};

int state=0;

char CEnt_Inicie (CEnt_Control *cesp, 
                  UBaseType_t prioridad)
   {
   char i;
   CEnt_Cfg_entrada *cep;
   
   if ( xTaskCreate(CEnt_Procese, "CtlEntrada", LONG_STACK, cesp,
                    prioridad, &(cesp->tarea)) != pdPASS )
      return NO;
      
   cesp->mutex_cfg = xSemaphoreCreateMutex();
   if (cesp->mutex_cfg == NULL)
      return NO;
      
   for (cep = cesp->t_cfg, i =  CENT_NUM_ENTRADAS;
        i;
        ++cep, --i)
      cep->banderas = 0;
      

  // vTaskDelay(400);
  // LCDB = 1;
   return SI;
   };
   
void CEnt_Procese (CEnt_Control *cesp)
/* void CEnt_Procese (void *pp) */
   {


   /* CEnt_Control *cecp = (CEnt_Control *) pp; */
   TickType_t tickactualA;
   uint32_t  anterior,
                  actual;
   char i;
   CEnt_Cfg_entrada *cep;
   unsigned char  bit_mask,
                  alarmas;

   uint32_t bits_maskSalida;
   CSal_Mensaje msj;
   unsigned short anchos[CENT_NUM_ENTRADAS];
   char txt_alarma[4] = { 'A', '0', '\n', '\0' };
   
   //anterior = PUERTO;
   anterior = PUERTO->PDIR; // Lectura de los puertos anterior
   tickactualA = xTaskGetTickCount();
   while (SI)
      {
		if(state==0){
			GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_LED_RED_PIN,1);
			state=1;
		}
		else{
			GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_LED_RED_PIN,0);
			state=0;
		}
      vTaskDelayUntil(&tickactualA, PERIODO_1SEG);
 //     actual = PUERTO;
      actual = PUERTO->PDIR; // lectura de los puertos actual
      xSemaphoreTake(cesp->mutex_cfg, portMAX_DELAY);
      for (cep = cesp->t_cfg, i =  0, bit_mask = 0x01, alarmas = 0;
           i < CENT_NUM_ENTRADAS;
           ++cep, ++i, bit_mask <<= 1)
         {
    	   PUERTO->PDIR;
    	   bits_maskSalida = 0x0000; // Nuevo
    	   bits_maskSalida |= (1 << PIN_Entradas[i]);// Nuevo
    	  if (cep->banderas & CENT_B_ACTIVO)
            {
            switch (cep->tipo)
               {
               case CENT_TIPO_SUBIDA:
                  //if ( !(anterior & bit_mask) && (actual & bit_mask) )
            	   if ( !(anterior & bits_maskSalida) && (actual & bits_maskSalida) )
                     {
                     msj.tipo = CSAL_TMSG_EVENTO;
                     msj.v.entrada = i;
                     CSal_Envie_mensaje(&c_salidas, &msj, portMAX_DELAY);
                     if (cep->banderas & CENT_B_ALARMA)
                        alarmas |= bit_mask;
                     };
                  break;
               case CENT_TIPO_BAJADA:
              //    if ( (anterior & bit_mask) && !(actual & bit_mask) )
            	    if ( (anterior & bits_maskSalida) && !(actual & bits_maskSalida) )
                     {
                     msj.tipo = CSAL_TMSG_EVENTO;
                     msj.v.entrada = i;
                     CSal_Envie_mensaje(&c_salidas, &msj, portMAX_DELAY);
                     if (cep->banderas & CENT_B_ALARMA)
                        alarmas |= bit_mask;
                     };
                  break;
               case CENT_TIPO_PULSO:
                  //if (anterior & bit_mask)
            	   if (anterior & bits_maskSalida)
                     { /* Estaba alto */
                     //if (actual & bit_mask)
            		   if (actual & bits_maskSalida)
                        { /* Sigue alto => contin�a el pulso */
                        if (anchos[i])
                           --(anchos[i]);
                        }
                        else
                        { /* Baj� => termin� el pulso */
                        if ( !(anchos[i]) )
                           { /* El pulso tuvo la duraci�n m�nima configurada */
                           msj.tipo = CSAL_TMSG_EVENTO;
                           msj.v.entrada = i;
                           CSal_Envie_mensaje(&c_salidas, &msj, portMAX_DELAY);
                           if (cep->banderas & CENT_B_ALARMA)
                              alarmas |= bit_mask;
                           };
                        };
                     }
                     else
                     { /* Estaba bajo */
                     if (actual & bits_maskSalida)
                        /* Hubo borde de subida */
                        anchos[i] = cep->ancho;
                     };
                  break;
               };
            };
         };
      xSemaphoreGive(cesp->mutex_cfg);

      anterior = actual;   /* El valor actual del puerto se vuelve el siguiente valor anterior */
      for (i =  0, bit_mask = 0x01;
           i < CENT_NUM_ENTRADAS;
           ++i, bit_mask <<= 1)
         if (alarmas & bit_mask)
            {
            txt_alarma[1] = '0' + i;
       //     Com_Tx_texto(&c_comunicacion, txt_alarma, portMAX_DELAY);
            };
      };
   };

void CEnt_Configure_evento (CEnt_Control *cesp,
                            char entrada,
                            char activo,
                            char tipo,
                            unsigned short ancho)
   {
   CEnt_Cfg_entrada *cep = cesp->t_cfg + entrada;
   /* CEnt_Cfg_entrada *cep = &(cesp->t_cfg[entrada]); */

   xSemaphoreTake(cesp->mutex_cfg, portMAX_DELAY);
   if (activo!='I')
      {
      cep->banderas |= CENT_B_ACTIVO;
      cep->tipo = tipo;
      cep->ancho = ancho;
      }
      else
      cep->banderas &= ~CENT_B_ACTIVO; /* 0x01 -> 0xfe */
   xSemaphoreGive(cesp->mutex_cfg);
   };

void CEnt_Configure_alarma (CEnt_Control *cesp,
                            char entrada,
                            char activa)
   {
   CEnt_Cfg_entrada *cep = cesp->t_cfg + entrada;
   /* CEnt_Cfg_entrada *cep = &(cesp->t_cfg[entrada]); */

   xSemaphoreTake(cesp->mutex_cfg, portMAX_DELAY);
   if (activa=='A')
      cep->banderas |= CENT_B_ALARMA;
      else
      cep->banderas &= ~CENT_B_ALARMA;
   xSemaphoreGive(cesp->mutex_cfg);
   };

