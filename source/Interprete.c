/*
 * InterpreteGood.c
 *
 *  Created on: 12 nov. 2021
 *      Author: User
 */

#include "Interprete.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include <queue.h>
#include "CtlEntradas.h"
#include "CtlSalidas.h"
#include "pin_mux.h"
#include "Varios.h"

#define LONG_STACK      (configMINIMAL_STACK_SIZE + 166)
#define MAX_MENSAJES    30

extern CSal_Control c_salidas;
extern CSal_Mensaje c_sal_mensaje;
extern CEnt_Control c_entrada;

CSal_Encendido inter_Enc;
CSal_Apagado   inter_Apa;
Interprete_mensaje mensaje;

char Interprete_Inicie (Interprete_Control *interp_contp, UBaseType_t prioridad){


		   if ( xTaskCreate(Interprete_Procese, "Keyboard_Procese", LONG_STACK, interp_contp,
		                    prioridad, &(interp_contp->tarea)) != pdPASS )
		      return NO;

		   interp_contp->cola_com = xQueueCreate(MAX_MENSAJES, sizeof(Interprete_mensaje));
		   if (interp_contp->cola_com == NULL)
		      return NO;



	   return SI;

}



void Interprete_Procese (Interprete_Control *interp_contp){
	const TickType_t oneSecond = 1000 / portTICK_PERIOD_MS;
	int state=0;
	char minp[4]={0,0,0,0};
	char ret[4]={0,0,0,0};
	char num [2]={0,0};
	char num_pulso[4]={0,0,0,0};
	int i=0,j=0,k=0;
	unsigned short ancho_pulso;
	int llevo_msg=0;

	 while (SI)
	    {

//			vTaskDelayUntil( &xLastWakeTime, oneSecond );
//
//			if(state==0){
//				GPIO_WritePinOutput(GPIOC,BOARD_INITPINS_S6_PIN,1);
//				state=1;
//			}
//			else{
//				GPIO_WritePinOutput(GPIOC,BOARD_INITPINS_S6_PIN,0);
//				state=0;
//			}
		 if(uxQueueMessagesWaiting(interp_contp->cola_com)){

			xQueueReceive(interp_contp->cola_com, &mensaje, portMAX_DELAY);
			switch (mensaje.msg[0]){


						case 'E':


							switch(mensaje.msg[1]){
								case 'E':

									if(mensaje.msg[3] == 'P' ){
										num_pulso[0]=mensaje.msg[4];
										num_pulso[1]=mensaje.msg[5];
										num_pulso[2]=mensaje.msg[6];
										num_pulso[3]=mensaje.msg[7];
									}

									ancho_pulso=atoi(num_pulso);
									CEnt_Configure_evento(&c_entrada,mensaje.msg[2]-48,mensaje.msg[3],mensaje.msg[3], ancho_pulso );
								break;

								case 'A':
									CEnt_Configure_alarma(&c_entrada,mensaje.msg[2]-48,mensaje.msg[3]);
									//CEnt_Configure_alarma(CEnt_Control *cesp, char entrada, char activa);
								break;
								default:
								break;

							}
							break;

						case 'S':
							llevo_msg=0;
							c_sal_mensaje.tipo=CSAL_TMSG_FORZADO;

							switch(mensaje.msg[1]){
												case 'E':

													i=3;

													while(mensaje.msg[i] != 110){ //110 corresponde a n en ascci

														if(llevo_msg){
															CSal_Configure_encendido(&c_salidas, mensaje.msg[2]-48, &inter_Enc);
															llevo_msg=0;
														}

														switch(mensaje.msg[i]){
															case 'E':

																c_sal_mensaje.tipo=CSAL_TMSG_EVENTO;

																j=i+2;
																k=0;

																inter_Enc.banderas  |=   CSAL_B_ON_EVENTO;
																inter_Enc.e.entrada = mensaje.msg[4]-48;
																llevo_msg=1;

																while(mensaje.msg[j]!=59){ // 59 corresponde a ;
																		ret[k]=mensaje.msg[j];
																		j++;k++;
																}
																inter_Enc.e.retardo = atoi(ret);

																i=j+1;

																break;

															case 'F':
																 c_sal_mensaje.tipo=CSAL_TMSG_RTC ;
																 inter_Enc.banderas  |=   CSAL_B_ON_MOMENTO;
																 j=i+1;

																 while(mensaje.msg[j]!=59){

																	 switch(mensaje.msg[j]){

																	 	case 'A':

									                                        inter_Enc.m.tipo = CSAL_TP_M_ANIO;
									                                        num[0]=mensaje.msg[j+1];
									                                        num[1]=mensaje.msg[j+2];
									                                        inter_Enc.m.t.f.mes =atoi(num);
									                                        num[0]=mensaje.msg[j+3];
									                                        num[1]=mensaje.msg[j+4];
									                                        inter_Enc.m.t.f.dia = atoi(num);
									                                        num[0]=mensaje.msg[j+5];
									                                        num[1]=mensaje.msg[j+6];
									                                        inter_Enc.m.t.h.hora = atoi(num);
									                                        num[0]=mensaje.msg[j+7];
									                                        num[1]=mensaje.msg[j+8];
									                                        inter_Enc.m.t.h.minuto = atoi(num);
									                                        j=j+9;
									                                        i=j;
									                                        llevo_msg=1;
																	 		break;

																	 	case'M':

																			inter_Enc.m.tipo = CSAL_TP_M_MES;
																			num[0]=mensaje.msg[j+1];
																			num[1]=mensaje.msg[j+2];
																			inter_Enc.m.t.f.dia = atoi(num);
																			num[0]=mensaje.msg[j+3];
																			num[1]=mensaje.msg[j+4];
																			inter_Enc.m.t.h.hora = atoi(num);
																			num[0]=mensaje.msg[j+5];
																			num[1]=mensaje.msg[j+6];
																			inter_Enc.m.t.h.minuto = atoi(num);
																			j=j+7;
																			i=j;
																			llevo_msg=1;
																	 		break;

																	 	case 'S':

									                                        inter_Enc.m.tipo = CSAL_TP_M_SEMANA;
									                                        num[0]=0;
									                                        num[1]=mensaje.msg[j+1];
									                                        inter_Enc.m.t.s = atoi(num);
									                                        num[0]=mensaje.msg[j+2];
									                                        num[1]=mensaje.msg[j+3];
									                                        inter_Enc.m.t.h.hora = atoi(num);
									                                        num[0]=mensaje.msg[j+4];
									                                        num[1]=mensaje.msg[j+5];
									                                        inter_Enc.m.t.h.minuto = atoi(num);
									                                        j=j+6;
									                                        i=j;
									                                        llevo_msg=1;

																	 		break;

																	 	case'D':
																	 		inter_Enc.m.tipo = CSAL_TP_M_DIA;
																			num[0]=mensaje.msg[j+1];
																			num[1]=mensaje.msg[j+2];
																			inter_Enc.m.t.h.hora = atoi(num);
																			num[0]=mensaje.msg[j+3];
																			num[1]=mensaje.msg[j+4];
																			inter_Enc.m.t.h.minuto = atoi(num);
																			j=j+5;
																			i=j;
																			llevo_msg=1;
																			break;

																		case 'H':
																			inter_Enc.m.tipo = CSAL_TP_M_HORA;
																			num[0]=mensaje.msg[j+1];
																			num[1]=mensaje.msg[j+2];
																			inter_Enc.m.t.h.minuto = atoi(num);
																			j=j+3;
																			i=j;
																			llevo_msg=1;
																			break;

																	 }

																 }

																i++;

																break;

															default:
																i++;

													   }

													}

													//c_sal_mensaje.v.forzado.salida=mensaje.msg[2]-48;
													//c_sal_mensaje.v.forzado.encender= 1;
													//CSal_Envie_mensaje(&c_salidas, &c_sal_mensaje, 0);

													//(cola de salidas, puerto de salida a encender, condiciones de encendido)

													if(c_sal_mensaje.tipo != CSAL_TMSG_FORZADO){

														CSal_Configure_encendido(&c_salidas, mensaje.msg[2]-48, &inter_Enc);
													}
													else {

														c_sal_mensaje.v.forzado.salida=mensaje.msg[2]-48;
														c_sal_mensaje.v.forzado.encender= SI;
														CSal_Envie_mensaje(&c_salidas, &c_sal_mensaje, 0);
													}

													break;


												case 'A':

													i=3;

													while(mensaje.msg[i] != 110){ //110 corresponde a n en ascci

														if(llevo_msg){
															CSal_Configure_encendido(&c_salidas, mensaje.msg[2]-48, &inter_Enc);
															llevo_msg=0;
														}

														switch(mensaje.msg[i]){
															case 'E':
																c_sal_mensaje.tipo=CSAL_TMSG_EVENTO;
																j=i+2;
																k=0;
																inter_Apa.banderas  |=   CSAL_B_OFF_EVENTO;
																inter_Apa.e.entrada = mensaje.msg [4]-48 ;

																while(mensaje.msg[j]!=59){ // 59 corresponde a ;
																		ret[k]=mensaje.msg[j];
																		j++;k++;
																}
																inter_Apa.e.retardo = atoi(ret);
																llevo_msg=1;
																i=j+1;

																break;

															case 'F':
																c_sal_mensaje.tipo=CSAL_TMSG_RTC ;
																 inter_Apa.banderas  |=   CSAL_B_OFF_MOMENTO;
																 j=i+1;

																 while(mensaje.msg[j]!=59){

																	 switch(mensaje.msg[j]){

																		case 'A':

																			inter_Apa.m.tipo = CSAL_TP_M_ANIO;
																			num[0]=mensaje.msg[j+1];
																			num[1]=mensaje.msg[j+2];
																			inter_Apa.m.t.f.mes =atoi(num);
																			num[0]=mensaje.msg[j+3];
																			num[1]=mensaje.msg[j+4];
																			inter_Apa.m.t.f.dia = atoi(num);
																			num[0]=mensaje.msg[j+5];
																			num[1]=mensaje.msg[j+6];
																			inter_Apa.m.t.h.hora = atoi(num);
																			num[0]=mensaje.msg[j+7];
																			num[1]=mensaje.msg[j+8];
																			inter_Apa.m.t.h.minuto = atoi(num);
																			j=j+9;
																			i=j;
																			llevo_msg=1;
																			break;

																		case 'M':

																			inter_Apa.m.tipo = CSAL_TP_M_MES;
																			num[0]=mensaje.msg[j+1];
																			num[1]=mensaje.msg[j+2];
																			inter_Apa.m.t.f.dia = atoi(num);
																			num[0]=mensaje.msg[j+3];
																			num[1]=mensaje.msg[j+4];
																			inter_Apa.m.t.h.hora = atoi(num);
																			num[0]=mensaje.msg[j+5];
																			num[1]=mensaje.msg[j+6];
																			inter_Apa.m.t.h.minuto = atoi(num);
																			j=j+7;
																			i=j;
																			llevo_msg=1;
																			break;

																		case 'S':

																			inter_Apa.m.tipo = CSAL_TP_M_SEMANA;
																			num[0]=0;
																			num[1]=mensaje.msg[j+1];
																			inter_Apa.m.t.s = atoi(num);
																			num[0]=mensaje.msg[j+2];
																			num[1]=mensaje.msg[j+3];
																			inter_Apa.m.t.h.hora = atoi(num);
																			num[0]=mensaje.msg[j+4];
																			num[1]=mensaje.msg[j+5];
																			inter_Apa.m.t.h.minuto = atoi(num);
																			j=j+6;
																			i=j;
																			llevo_msg=1;
																			break;

																		case 'D':
																			inter_Apa.m.tipo = CSAL_TP_M_DIA;
																			num[0]=mensaje.msg[j+1];
																			num[1]=mensaje.msg[j+2];
																			inter_Apa.m.t.h.hora = atoi(num);
																			num[0]=mensaje.msg[j+3];
																			num[1]=mensaje.msg[j+4];
																			inter_Apa.m.t.h.minuto = atoi(num);
																			j=j+5;
																			i=j;
																			llevo_msg=1;
																			break;
																		case 'H':
																			inter_Apa.m.tipo = CSAL_TP_M_HORA;
																			num[0]=mensaje.msg[j+1];
																			num[1]=mensaje.msg[j+2];
																			inter_Apa.m.t.h.minuto = atoi(num);
																			j=j+3;
																			i=j;
																			llevo_msg=1;

																			break;
																	 }

																 }
																i++;

																break;


															case 'R':

																inter_Apa.banderas  |=   CSAL_B_OFF_RETARDO;
																j=i+1;
																k=0;

																while(mensaje.msg[j]!=59){
																	num[k]=mensaje.msg[j];
																	j++;
																	k++;
																}
																inter_Apa.retardo = atoi(num);
																break;


															default:
																i++;
													   }


													}
													i++;

//													c_sal_mensaje.tipo=1;
//													c_sal_mensaje.v.forzado.salida=mensaje.msg[2]-48;
//													c_sal_mensaje.v.forzado.encender= 0;
//													CSal_Envie_mensaje(&c_salidas, &c_sal_mensaje, 0);
//			                                       // CSal_Configure_apagado(&c_salidas, mensaje.msg[2]-45, &inter_Apa);

													if(c_sal_mensaje.tipo != CSAL_TMSG_FORZADO ){

														CSal_Configure_apagado(&c_salidas, mensaje.msg[2]-48, &inter_Apa);
													}
													else {

														c_sal_mensaje.v.forzado.salida=mensaje.msg[2]-48;
														c_sal_mensaje.v.forzado.encender= NO;
														CSal_Envie_mensaje(&c_salidas, &c_sal_mensaje, 0);
													}

			                                        break;

							}

							break;

						case'M':

							switch(mensaje.msg[1]){
								//Activo o inactivo

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
};



BaseType_t Interprete_envie_mensaje(Interprete_Control *interp_contp, Interprete_mensaje *msg, TickType_t espera)
	   {
	   return xQueueSend(interp_contp->cola_com, msg, espera);
	   };

