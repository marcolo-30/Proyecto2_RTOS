/* Interprete.c   Implementación del modulo de Interprete de Comandos */


#include "MKL46Z4.h"
//#include "CtlEntradas.h"
#include "CtlSalidas.h"
#include "Interprete.h"
#include "fsl_debug_console.h"

//#include "Comunicacion.h"
#define LONG_STACK      (configMINIMAL_STACK_SIZE + 50)
#define MAX_MENSAJES    30

extern CSal_Control c_salidas;
extern CSal_Mensaje c_sal_mensaje;
//extern CEnt_Control c_entrada;

CSal_Encendido inter_Enc;
CSal_Apagado   inter_Apa;
Interprete_mensaje mensaje;


char Interprete_Inicie (Interprete_Control *interp_contp, UBaseType_t prioridad){

	   if ( xTaskCreate( Interprete_Procese, "Interprete", LONG_STACK, interp_contp,
	                    prioridad, &(interp_contp->tarea)) != pdPASS )
	      return NO;

	   interp_contp->cola_com = xQueueCreate(MAX_MENSAJES, sizeof(Interprete_mensaje));
	   if (interp_contp->cola_com == NULL)
	      return NO;

return SI;
};


void Interprete_Procese (Interprete_Control *interp_contp){

	char minp[4];
	char ret[4];
	char num [2];
	int i=0,j=0,k=0;


    while (SI)
    {
        if ( xQueueReceive(interp_contp->cola_com, &mensaje, portMAX_DELAY) != pdTRUE )
         continue;


		switch (mensaje.msg[0]){

			case'E':

				switch(mensaje.msg[1]){
					case 'E':



							c_sal_mensaje.tipo=1;
							c_sal_mensaje.v.forzado.salida=0;
							c_sal_mensaje.v.forzado.encender=k;
							CSal_Envie_mensaje(&c_salidas, &c_sal_mensaje, 0);


							//c_salidas.t_cfg.on=1;



					break;
					case 'A':
						//c_salidas.t_cfg.on=1;
										c_sal_mensaje.tipo=1;
										c_sal_mensaje.v.forzado.salida=1;
										c_sal_mensaje.v.forzado.encender=1;

										CSal_Envie_mensaje(&c_salidas, &c_sal_mensaje, 0);
										break;
					default:
					break;

				}
				break;

			case'S':

				switch(mensaje.msg[1]){
									case 'E':
										i=3;
										while(mensaje.msg[i] != 110){ //110 corresponde a n en ascci
											switch(mensaje.msg[i]){
											case 'E':

												j=i+2;
												k=0;
												while(mensaje.msg[j]!=59){
														ret[k]=mensaje.msg[j];c_sal_mensaje.tipo=1;
														j++;k++;
												}
												inter_Enc.e.retardo = atoi(ret);
												i=j+1;
												break;

											case 'F':

												c_sal_mensaje.tipo=1;
												c_sal_mensaje.v.forzado.salida=i;
												c_sal_mensaje.v.forzado.encender=1;
												CSal_Envie_mensaje(&c_salidas, &c_sal_mensaje, 0);
												i++;
												break;
											default:
												i++;



											}


										}
										break;
										//c_salidas.t_cfg.on=1;

									case 'A':
										i=3;
										//c_salidas.t_cfg.on=1;
														c_sal_mensaje.tipo=1;
														c_sal_mensaje.v.forzado.salida=3;
														c_sal_mensaje.v.forzado.encender=1;

														CSal_Envie_mensaje(&c_salidas, &c_sal_mensaje, 0);
														break;
									default:
										i++;
									break;

								}

				break;

			case'M':

				switch(mensaje.msg[3]){             //Activo o inactivo

				                case 'A':
				                    CSal_Cambie_monitoreo(&c_salidas, SI);
				                    break;
				                case 'I':
				                    CSal_Cambie_monitoreo(&c_salidas, NO);
				                    break;
						};
				 break;

			default:
				break;
		};
    };
};


BaseType_t InterCom_Envie_mensaje(Interprete_Control *interp_contp, Interprete_mensaje *mensaje, TickType_t espera)
   {
   return xQueueSend(interp_contp->cola_com, mensaje, espera);
   };




