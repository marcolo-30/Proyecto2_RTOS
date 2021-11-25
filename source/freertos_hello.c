/*
 * The Clear BSD License
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_gpio.h"

/* Custom Libraries. */
#include "CtlSalidas.h"
#include "CtlEntradas.h"
#include "Interprete.h"
#include "Keyboard.h"
#include "lcd.h"
#include "Interfaz.h"
#include "rtc.h"

/* UART import for Interrupts. */
#include "fsl_uart.h"
#include "pin_mux.h"



/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define PROJ_UART UART1
#define PROJ_UART_CLKSRC BUS_CLK
#define PROJ_UART_CLK_FREQ CLOCK_GetFreq(BUS_CLK)
#define PROJ_UART_IRQn UART1_IRQn
#define PROJ_UART_IRQHandler UART1_IRQHandler

/*******************************************************************************
* Handlers
******************************************************************************/
CSal_Control c_salidas;
CEnt_Control c_entrada;
CSal_Mensaje c_sal_mensaje;
Interprete_Control inter_cont;
Interprete_mensaje inter_mensaje;
Keyboard_Control c_keyboard;
Interfaz_Control c_interfaz;
RTC_Control c_rtc;
/*******************************************************************************
* Task Priorities
******************************************************************************/
#define hello_task_PRIORITY (configMAX_PRIORITIES - 1)
#define comRxUart_task_PRIORITY (configMAX_PRIORITIES - 2)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void hello_task(void *pvParameters);
static void comRxUart_task(void *pvParameters);

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t g_tipString[] =
    "Proyect 2 RTOS\r\n";

QueueHandle_t ColaRx;
QueueHandle_t ColaKeyboard;
QueueHandle_t ColaTx;
QueueHandle_t ColaInterfaz;
QueueHandle_t ColaMonitoreo;
SemaphoreHandle_t mutexLCD;



char dato_rx;
int mensaje_completo = NO;
char TX_texto[5];
char mensajes[50];
char *cadena_mensaje = mensajes;

/*******************************************************************************
* UART interrupt
******************************************************************************/
void PROJ_UART_IRQHandler(void) {
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	// si es una interruption de recepción
    if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & UART_GetStatusFlags(PROJ_UART)){
    		//Se recibe el dato, se guarda en dato_rx
			dato_rx = UART1->D; // Recepcion del dato
			UART_WriteBlocking(PROJ_UART, &dato_rx, 1);
			// Enviar el dato a la cola
			xQueueSendFromISR(ColaRx , ( void * ) &dato_rx,&xHigherPriorityTaskWoken);

	}

    else if((kUART_TxDataRegEmptyFlag) & UART_GetStatusFlags(PROJ_UART) ){

    	   if ( xQueueReceiveFromISR(ColaTx, &TX_texto, 0) == pdTRUE ){
    		   uint8_t *data = TX_texto;
    		        UART1->D = *(data);

    	   }

	else{

		   UART_DisableInterrupts(PROJ_UART, kUART_TxDataRegEmptyInterruptEnable );

	};
    // si es una interruption de transmision
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}
}

/*******************************************************************************
* Main Code
******************************************************************************/

int main(void)
{

	uart_config_t config;
	BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();


    /*******************************************************************************
    * Uart Interrupt Initilization
    ******************************************************************************/

    /*
        * config.baudRate_Bps = 115200U;
        * config.parityMode = kUART_ParityDisabled;
        * config.stopBitCount = kUART_OneStopBit;
        * config.txFifoWatermark = 0;
        * config.rxFifoWatermark = 1;
        * config.enableTx = false;
        * config.enableRx = false;
    */

    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
    config.enableTx = true;
    config.enableRx = true;
    UART_Init(PROJ_UART, &config, PROJ_UART_CLK_FREQ);
    UART_WriteBlocking(PROJ_UART, g_tipString, sizeof(g_tipString) / sizeof(g_tipString[0]));
    UART_EnableInterrupts(PROJ_UART, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable | kUART_TxDataRegEmptyInterruptEnable );
    EnableIRQ(PROJ_UART_IRQn);

    /*******************************************************************************
    * Task Initialization
    ******************************************************************************/

//    if (xTaskCreate(hello_task, "Hello_task", configMINIMAL_STACK_SIZE + 10, NULL, hello_task_PRIORITY, NULL) != pdPASS)
//    {
//        PRINTF("Task creation failed!.\r\n");
//        while (1);
//    }
    if(CEnt_Inicie  (&c_entrada , tskIDLE_PRIORITY + 5)){
    	PRINTF("No fue posible inicializar el modulo ENTRADAS !.\r\n");
    };

    if (xTaskCreate(comRxUart_task, "comRxUart_task", configMINIMAL_STACK_SIZE + 10, NULL,  comRxUart_task_PRIORITY, NULL) != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1);
    }
    Interfaz_Inicie(&c_interfaz,  tskIDLE_PRIORITY + 3);

    Keyboard_Inicie(&c_keyboard,  tskIDLE_PRIORITY + 4);

    RTC_Inicie(&c_rtc,  tskIDLE_PRIORITY + 3);

    if(CSal_Inicie (&c_salidas , tskIDLE_PRIORITY + 3)){
    	PRINTF("No fue posible inicializar el modulo salidas !.\r\n");
    };



    Interprete_Inicie (&inter_cont,tskIDLE_PRIORITY + 3);
    mutexLCD = xSemaphoreCreateMutex();


    ColaRx = xQueueCreate( 64, sizeof(char));
    ColaKeyboard = xQueueCreate( 64, sizeof(char));
    ColaTx = xQueueCreate( 64, sizeof(char));
    ColaInterfaz = xQueueCreate( 10, sizeof(char));
    ColaMonitoreo = xQueueCreate( 64, sizeof(char));

    if(ColaRx==NULL){
    	while(1);
    };

    vTaskStartScheduler();
    for (;;){

    };
}

/*!
 * @brief Task responsible for printing of "Hello world." message.
 */

static void comRxUart_task(void *pvParameters){

	int i=0;
	int j=0;
	uint8_t keyboard_data = 'a';
	char dato_monitoreo;
	const TickType_t oneSecond = 1000 / portTICK_PERIOD_MS;
	uint8_t uart_data ;


	for (;;)
	    {

		// Esto es para revisar la cola del teclado e imprimirla no more
		if(uxQueueMessagesWaiting(ColaKeyboard)){
			xQueueReceive(ColaKeyboard,&keyboard_data,0);
			xQueueSend(ColaTx,(void *)&keyboard_data,0);
			UART_EnableInterrupts(PROJ_UART, kUART_TxDataRegEmptyInterruptEnable );
			//UART_WriteBlocking(PROJ_UART, &keyboard_data, 1);
		}


		if(uxQueueMessagesWaiting(ColaMonitoreo)){
					xQueueReceive(ColaMonitoreo,&dato_monitoreo,0);
					xQueueSend(ColaTx,(void *)&dato_monitoreo,0);
					UART_EnableInterrupts(PROJ_UART, kUART_TxDataRegEmptyInterruptEnable );
					//UART_WriteBlocking(PROJ_UART, &keyboard_data, 1);
				}


		// Si hay mensajes en la cola de recepcion deberiamos hacer append al array

			 if(uxQueueMessagesWaiting(ColaRx)){
				 //Guarda en cadena_mensaje lo que venga por la interrupcion por la UART
				 xQueueReceive(ColaRx,&uart_data,portMAX_DELAY);
				 //enviar al interprete de comandos cuando se oprima el enter

				 if( uart_data == 0xd){
					   /* GPIO_WritePinOutput(GPIOC,BOARD_INITPINS_S7_PIN,1);
					    vTaskDelay( oneSecond );
					    GPIO_WritePinOutput(GPIOC,BOARD_INITPINS_S7_PIN,0);
*/
					    //inter_mensaje.msg[0]='G';
					 // enviamos la estructura que necesita el interprete de comandos
					    Interprete_envie_mensaje(&inter_cont,&inter_mensaje,portMAX_DELAY);

						for (j=i;j>0;j--){
							inter_mensaje.msg[j] = '\0';
						}

						i=0;
						}
				 	 //Si no es enter que se vaya guardando en el array
				 	 else{
				 		 //Diferent to backspace
				 		 if(uart_data!= 0x08){
					 		 // guardar lo que este en la cadena del mensaje en la estructura
					 		 inter_mensaje.msg[i]=uart_data;
					 		 i++;
				 		 }

				 	}

				 }


			 }

	    }


static void hello_task(void *pvParameters)
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	const TickType_t time_pin = 1000/ portTICK_PERIOD_MS;
	int i = 0;

    for (;;)
    {
    	/*	//c_salidas.t_cfg.on=1;
    	c_sal_mensaje.tipo=1;
    	c_sal_mensaje.v.forzado.salida=i;
    	c_sal_mensaje.v.forzado.encender=1;

    	CSal_Envie_mensaje(&c_salidas, &c_sal_mensaje, 0);


        //PRINTF("Hello world.\r\n");

        vTaskDelayUntil( &xLastWakeTime, time_pin );
        i++;

        if (i==8){
        	i=0;
        };*/

//
//    	inter_mensaje.msg[0]='S';
//    	inter_mensaje.msg[1]='E';
//    	inter_mensaje.msg[2]='1';
//    	inter_mensaje.msg[3]='F';
//    	inter_mensaje.msg[4]='1';
//    	inter_mensaje.msg[5]=';';
//    	inter_mensaje.msg[6]='E';
//    	inter_mensaje.msg[7]='1';
//    	inter_mensaje.msg[8]='1';
//    	inter_mensaje.msg[9]=';';
//    	inter_mensaje.msg[10]='n';
//    	inter_mensaje.msg[11]=';';
//    	inter_mensaje.msg[12]='n';
//
//
//    	InterCom_Envie_mensaje(&inter_cont,&inter_mensaje,0);
    	vTaskDelayUntil( &xLastWakeTime, time_pin );



    }
}

