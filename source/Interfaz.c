/*
 * Interfaz.c
 *
 *  Created on: 10 nov. 2021
 *      Author: Diego Avellaneda
 */

#include<stdlib.h>
#include "Interfaz.h"
#include "lcd.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "CtlSalidas.h"
#include "Interprete.h"
#include "Varios.h"
#include "rtc.h"

extern QueueHandle_t ColaInterfaz;
extern SemaphoreHandle_t mutexLCD;
extern SemaphoreHandle_t mutexRTC;

extern Interprete_Control inter_cont;
extern Interprete_mensaje inter_mensaje;
extern CSal_Control c_salidas;
extern RTC_Control c_rtc;
//Interfaz de Usuario

#define LONG_STACK      (configMINIMAL_STACK_SIZE + 166)






char Interfaz_Inicie (Interfaz_Control *iucp, UBaseType_t prioridad){

	if ( xTaskCreate(Interfaz_Procese, "Interfaz Usuario", LONG_STACK, iucp,
                    prioridad, &(iucp->tarea)) != pdPASS )
      return NO;


	return SI;
}

void Interfaz_Procese (Interfaz_Control *iucp){


		 TickType_t xLastWakeTime;
		 xLastWakeTime = xTaskGetTickCount();

		 const TickType_t lcd_time = 1000/ portTICK_PERIOD_MS;
		 const TickType_t waiting_time = 10000/ portTICK_PERIOD_MS;

		 xSemaphoreTake(mutexLCD, portMAX_DELAY);
		 init_LCD_display();
		 xSemaphoreGive(mutexLCD);

		 int lcd_render_state=0;
		 		 char dato_fecha[8];
		 		 char anio[4] = {0,0,0,0};
		 		 char mes[2];
		 		 char dia[2];
		 		 char hora[2];
		 		 char min[2];
		 		 char dato_hora[8];
		 		 char dato_cola;
		 		 int i;
		 		 int A;
		 		 char B;
		 		 uint32_t C;

	    for( ;; )
	    {

	    	xSemaphoreTake(mutexLCD, portMAX_DELAY);
			write_second_line();
			write_line("A.Da B.F C.M D.A");
			xSemaphoreGive(mutexLCD);

			if( xQueueReceive (ColaInterfaz,&dato_cola,portMAX_DELAY) == pdPASS )

			switch (dato_cola){
					 case 'A':

						xSemaphoreTake(mutexLCD, portMAX_DELAY);
						write_second_line();
						write_line("Programing Date ");
						write_second_line();
						write_line("A. Fecha B. Hora");
						xSemaphoreGive(mutexLCD);
						//vTaskDelay( waiting_time );
						//break;
						i=0;
						if( xQueueReceive (ColaInterfaz,&dato_cola,waiting_time) == pdPASS ){
							switch (dato_cola){
										    	 	 case 'A':

										    	 		xSemaphoreTake(mutexLCD, portMAX_DELAY);
										 		    	write_second_line();
										 		    	write_line("Introduzca Fecha");
										 		    	xSemaphoreGive(mutexLCD);
										 		    	while (true){

										 		    		if( xQueueReceive (ColaInterfaz,&dato_cola,portMAX_DELAY) == pdPASS )
										 		    			if(dato_cola=='#'){
										 		    				//Hay que crear un mutex para esta informacion//
										 		    													 		    				anio[0]=dato_fecha[0];
										 		    													 		    				anio[1]=dato_fecha[1];
										 		    													 		    				anio[2]=dato_fecha[2];
										 		    													 		    				anio[3]=dato_fecha[3];
										 		    													 		    				A=0;
										 		    													 		    				for (int j=0;j<4;j++){
										 		    													 		    					A=A*10+anio[j]-48;
										 		    													 		    				}

										 		    													 		    				mes[0]=dato_fecha[4];
										 		    																				mes[1]=dato_fecha[5];


										 		    																				dia[0]=dato_fecha[6];
										 		    																				dia[1]=dato_fecha[7];

										 		    																				xSemaphoreTake(mutexRTC, portMAX_DELAY);
										 		    																				c_rtc.TiempoRTC.f.anio=(int)A;
										 		    																				c_rtc.TiempoRTC.f.mes=atoi(mes);
										 		    																				c_rtc.TiempoRTC.f.dia=atoi(dia);
										 		    																				 xSemaphoreGive(mutexRTC);
										 		    													 		    				//envia la funcion de configuracion de fecha
										 		    													 		    				break;
										 		    			}else if(dato_cola=='*'){
										 		    				xSemaphoreTake(mutexLCD, portMAX_DELAY);
																		write_second_line();
																		write_line("Cancelado");
																		xSemaphoreGive(mutexLCD);
																		break;
										 		    			} else {
										 		    				xSemaphoreTake(mutexLCD, portMAX_DELAY);
																						write_second_line();
																						write_line("guardando info ");
																						write_character(dato_cola);
																						xSemaphoreGive(mutexLCD);//guarda en la cola
																						dato_fecha[i]=dato_cola;
																						i++;
										 		    			}

										 		    		}

										 		    	break;



													 case'B':
															xSemaphoreTake(mutexLCD, portMAX_DELAY);
															write_second_line();
															write_line("Introduzca Hora ");
															xSemaphoreGive(mutexLCD);
															i=0;
															 while (true){

																	if( xQueueReceive (ColaInterfaz,&dato_cola,portMAX_DELAY) == pdPASS )
																		if(dato_cola=='#'){
																			hora[0]=dato_hora[0];
																			hora[1]=dato_hora[1];

																			min[0]=dato_hora[2];
																			min[1]=dato_hora[3];

																			xSemaphoreTake(mutexRTC, portMAX_DELAY);
																			c_rtc.TiempoRTC.h.hora=atoi(hora);
																			c_rtc.TiempoRTC.h.minuto=atoi(min);
																			xSemaphoreGive(mutexRTC);

																			//envia la funcion de configuracion de fecha
																			break;
																			//envia la funcion de configuracion de fecha
																			break;
																		}else if(dato_cola=='*'){
																			xSemaphoreTake(mutexLCD, portMAX_DELAY);
																				write_second_line();
																				write_line("Cancelado");
																				xSemaphoreGive(mutexLCD);
																				break;
																		} else {
																			xSemaphoreTake(mutexLCD, portMAX_DELAY);
																								write_second_line();
																								write_line("guardando info ");
																								write_character(dato_cola);
																								xSemaphoreGive(mutexLCD);//guarda en la cola
																								dato_hora[i]=dato_cola;
																								i++;
																		}

																	}
															 break;

													 	default:
													 		xSemaphoreTake(mutexLCD, portMAX_DELAY);
													 								write_second_line();
													 								write_line("Opcion no valida");
													 								xSemaphoreGive(mutexLCD);
													 		break;
							}
						}
						else {
							xSemaphoreTake(mutexLCD, portMAX_DELAY);
							write_second_line();
							write_line("  Time Out !!!  ");
							xSemaphoreGive(mutexLCD);
							break;
						}
						break;

						case'B':
							  xSemaphoreTake(mutexLCD, portMAX_DELAY);
							                            write_second_line();
							                            write_line("Forzado On/Off  ");
							                            write_second_line();
							                            write_line("   A.On B.Off   ");
							                            xSemaphoreGive(mutexLCD);
							                            //vTaskDelay( lcd_time );

							                            if( xQueueReceive (ColaInterfaz,&dato_cola,waiting_time) == pdPASS ){
							                                                                                    switch (dato_cola){
							                                                                                        case 'A':

							                                                                                            xSemaphoreTake(mutexLCD, portMAX_DELAY);
							                                                                                            write_second_line();
							                                                                                            write_line("Force Encendido ");
							                                                                                            write_second_line();
							                                                                                            write_line("Digite el puerto");
							                                                                                            xSemaphoreGive(mutexLCD);
							                                                                                            //vTaskDelay( lcd_time );
							                                                                                            if( xQueueReceive (ColaInterfaz,&dato_cola,portMAX_DELAY) == pdPASS ){
							                                                                                            	if (dato_cola >= 48 && dato_cola<=55 ){
							                                                                                                        xSemaphoreTake(mutexLCD, portMAX_DELAY);
							                                                                                                        write_second_line();
							                                                                                                        write_line("Encendiendo Pto ");
							                                                                                                        xSemaphoreGive(mutexLCD);

							                                     //---------ENvia mensaje encendido a interprete -----------------------------------------------------------------------------------------------------

							                                                                                                        inter_mensaje.msg[0]='S';
							                                                                                                        inter_mensaje.msg[1]='E';
							                                                                                                        inter_mensaje.msg[2]= dato_cola;
							                                                                                                        inter_mensaje.msg[3]='n';


							                                                                                                        Interprete_envie_mensaje(&inter_cont,&inter_mensaje,portMAX_DELAY);


							                                    //-----------------------------------------------------------------------------------------------------------------
							                                                                                                        break;
							                                                                                                   }

							                                                                                                    else {
							                                                                                                        xSemaphoreTake(mutexLCD, portMAX_DELAY);
							                                                                                                        write_second_line();
							                                                                                                        write_line("Puerto no valido");
							                                                                                                        xSemaphoreGive(mutexLCD);
							                                                                                                        break;
							                                                                                                    }

							                                                                                                //envia el mensaje de encender puerto;
							                                                                                            }



							                                                                                            case 'B':

							                                                                                                xSemaphoreTake(mutexLCD, portMAX_DELAY);
							                                                                                                write_second_line();
							                                                                                                write_line("Force Apagado   ");
							                                                                                                write_second_line();
							                                                                                                write_line("Digite el puerto");
							                                                                                                xSemaphoreGive(mutexLCD);
							                                                                                                //vTaskDelay( lcd_time );
							                                                                                                if( xQueueReceive (ColaInterfaz,&dato_cola,portMAX_DELAY) == pdPASS ){
							                                                                                                	if (dato_cola >= 48 && dato_cola<=55 ){
							                                                                                                            xSemaphoreTake(mutexLCD, portMAX_DELAY);
							                                                                                                            write_second_line();
							                                                                                                            write_line("Apagando Puerto ");
							                                                                                                            xSemaphoreGive(mutexLCD);

							                                                                                                            inter_mensaje.msg[0]='S';
																																		inter_mensaje.msg[1]='A';
																																		inter_mensaje.msg[2]= dato_cola;
																																		inter_mensaje.msg[3]='n';

																																	  //  Interprete_mensaje.msg = mensaje_interp;
																																		Interprete_envie_mensaje(&inter_cont,&inter_mensaje,portMAX_DELAY);


							                                                                                                            break;
							                                                                                                        }

							                                                                                                        else {
							                                                                                                            xSemaphoreTake(mutexLCD, portMAX_DELAY);
							                                                                                                            write_second_line();
							                                                                                                            write_line("Puerto no valido");
							                                                                                                            xSemaphoreGive(mutexLCD);
							                                                                                                            break;
							                                                                                                        }

							                                                                                                   // envia el mensaje de encender puerto;
							                                                                                                }

							                                                                                                break;

							                                                                                            default:
							                                                                                                xSemaphoreTake(mutexLCD, portMAX_DELAY);
							                                                                                                write_second_line();
							                                                                                                write_line("Opcion no valida");
							                                                                                                xSemaphoreGive(mutexLCD);
							                                                                                                break;
							                                                                                        }
							                                                                                    }
							else {
														xSemaphoreTake(mutexLCD, portMAX_DELAY);
														write_second_line();
														write_line("  Time Out !!!  ");
														xSemaphoreGive(mutexLCD);
														break;
													}


							break;

                    case 'C':
                        xSemaphoreTake(mutexLCD, portMAX_DELAY);
                        write_second_line();
                        write_line("Monitoreo On/Off");
                        write_second_line();
                        write_line("   A.On B.Off   ");
                        xSemaphoreGive(mutexLCD);
                        if( xQueueReceive (ColaInterfaz,&dato_cola,waiting_time) == pdPASS ){
                              switch (dato_cola){
                                case 'A':
                                    xSemaphoreTake(mutexLCD, portMAX_DELAY);
                                    write_second_line();
                                    write_line("   Mon Activo   ");
                                    xSemaphoreGive(mutexLCD);

                                    inter_mensaje.msg[0]='M';
									inter_mensaje.msg[1]='A';
									inter_mensaje.msg[2]='n';


									Interprete_envie_mensaje(&inter_cont,&inter_mensaje,portMAX_DELAY);



                                break;
                                case 'B':
                                    xSemaphoreTake(mutexLCD, portMAX_DELAY);
                                    write_second_line();
                                    write_line("Mon desactivado ");
                                    xSemaphoreGive(mutexLCD);
                                    CSal_Cambie_monitoreo(&c_salidas, NO);
                                    inter_mensaje.msg[0]='M';
									inter_mensaje.msg[1]='I';
									inter_mensaje.msg[2]='n';


									Interprete_envie_mensaje(&inter_cont,&inter_mensaje,portMAX_DELAY);

                                    break;
                                default:
                                    xSemaphoreTake(mutexLCD, portMAX_DELAY);
                                    write_second_line();
                                    write_line("Opcion no valida");
                                    xSemaphoreGive(mutexLCD);
                                break;
                            }
                        }
                        else{
                        	xSemaphoreTake(mutexLCD, portMAX_DELAY);
                        								write_second_line();
                        								write_line("  Time Out !!!  ");
                        								xSemaphoreGive(mutexLCD);
                        								break;
                        }

                    break;

                    case 'D':
                        xSemaphoreTake(mutexLCD, portMAX_DELAY);
                        write_second_line();
                        write_line("  Alarma On/Off ");
                        write_second_line();
                        write_line("   A.On B.Off   ");
                        xSemaphoreGive(mutexLCD);
                        if( xQueueReceive (ColaInterfaz,&dato_cola,waiting_time) == pdPASS ){
                              switch (dato_cola){
                                case 'A':
                                    xSemaphoreTake(mutexLCD, portMAX_DELAY);
                                    write_second_line();
                                    write_line(" Activar Alarma ");
                                    write_second_line();
							        write_line("Digite el puerto");
                                    xSemaphoreGive(mutexLCD);
                                    if( xQueueReceive (ColaInterfaz,&dato_cola,portMAX_DELAY) == pdPASS ){
                                       // if (dato_cola=='1'){
                                            xSemaphoreTake(mutexLCD, portMAX_DELAY);
                                            write_second_line();
                                            write_line(" Alarma config  ");
                                            xSemaphoreGive(mutexLCD);

											inter_mensaje.msg[0]='E';
											inter_mensaje.msg[1]='A';
											inter_mensaje.msg[2]=dato_cola;
											inter_mensaje.msg[3]='A';
											inter_mensaje.msg[4]='n';

											Interprete_envie_mensaje(&inter_cont,&inter_mensaje,portMAX_DELAY);
                                           // break;
                                    }


                                break;
                                case 'B':
                                	 xSemaphoreTake(mutexLCD, portMAX_DELAY);
                                	 write_second_line();
                                	 write_line("Desactiva Alarma");
                                	 write_second_line();
                                	 write_line("Digite el puerto");
                                	 xSemaphoreGive(mutexLCD);

                                    if( xQueueReceive (ColaInterfaz,&dato_cola,portMAX_DELAY) == pdPASS ){
                                       // if (dato_cola=='1'){
                                            xSemaphoreTake(mutexLCD, portMAX_DELAY);
                                            write_second_line();
                                            write_line(" Alarma deconfig");
                                            xSemaphoreGive(mutexLCD);

											inter_mensaje.msg[0]='E';
											inter_mensaje.msg[1]='A';
											inter_mensaje.msg[2]=dato_cola;
											inter_mensaje.msg[3]='I';
											inter_mensaje.msg[4]='n';

											Interprete_envie_mensaje(&inter_cont,&inter_mensaje,portMAX_DELAY);
                                           // break;
                                    }


                                break;


                                default:
                                    xSemaphoreTake(mutexLCD, portMAX_DELAY);
                                    write_second_line();
                                    write_line("Opcion no valida");
                                    xSemaphoreGive(mutexLCD);
                                break;
                            }

                        }else{
                        	xSemaphoreTake(mutexLCD, portMAX_DELAY);
							write_second_line();
							write_line("  Time Out !!!  ");
							xSemaphoreGive(mutexLCD);
							break;
                        }
                    break;


					default:
						xSemaphoreTake(mutexLCD, portMAX_DELAY);
						write_second_line();
						write_line("Opcion no valida");
						xSemaphoreGive(mutexLCD);
					break;
        }
    }

}


