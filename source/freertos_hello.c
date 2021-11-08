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
#include "CtlSalidas.h"
#include "Interprete.h"

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


CSal_Control c_salidas;
CSal_Mensaje c_sal_mensaje;
Interprete_Control inter_cont;
Interprete_mensaje inter_mensaje;

char dato_rx;
/* Task priorities. */
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

uint8_t pmesage[] =
    "Hola \r\n";


QueueHandle_t ColaRx;
int mensaje_completo = NO;





/*******************************************************************************
 * Code
 ******************************************************************************/
void PROJ_UART_IRQHandler(void) {
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	// si es una interruption de recepción
    if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & UART_GetStatusFlags(PROJ_UART)){
			dato_rx = UART1->D; // Recepcion del dato
			UART_WriteBlocking(PROJ_UART, &dato_rx, 1);
			if(dato_rx != 'n'){
				xQueueSendFromISR(ColaRx , ( void * ) &dato_rx,&xHigherPriorityTaskWoken);
			}
			else{

				mensaje_completo = SI;
			}
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



/*!
 * @brief Application entry point.
 */
int main(void)
{
	//Confing UART
	 uart_config_t config;
    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
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
    /* Enable RX interrupt. */
    UART_EnableInterrupts(PROJ_UART, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable | kUART_TxDataRegEmptyInterruptEnable );
    /* Enable TX interrupt. */
    //UART_EnableInterrupts(PROJ_UART, kUART_TxDataRegEmptyInterruptEnable );
    EnableIRQ(PROJ_UART_IRQn);

    //interp_contp->cola_com = xQueueCreate(MAX_MENSAJES, sizeof(Interprete_mensaje));

    if (xTaskCreate(hello_task, "Hello_task", configMINIMAL_STACK_SIZE + 10, NULL, hello_task_PRIORITY, NULL) != pdPASS)
    {

        PRINTF("Task creation failed!.\r\n");
        while (1)
            ;
    }

    if(CSal_Inicie (&c_salidas , tskIDLE_PRIORITY + 3)){
    	PRINTF("No fue posible inicializar el modulo salidas !.\r\n");
    };

    if(Interprete_Inicie (&inter_cont,tskIDLE_PRIORITY + 2)){
        	PRINTF("No fue posible inicializar el modulo salidas !.\r\n");
        };


    ColaRx = xQueueCreate( 64, sizeof(char));
    if(ColaRx==NULL){
    	while(1);
    };

    vTaskStartScheduler();
    for (;;){


    }

        ;
}

/*!
 * @brief Task responsible for printing of "Hello world." message.
 */

static void comRxUart_task(void *pvParameters){

	char comando[25];
	int i=0;

	for (;;)
	    {
		 if(mensaje_completo==SI){

			 while (!uxQueueMessagesWaiting( ColaRx )){

				 xQueueReceive(ColaRx,&comando[i],0);
				 i++;

			  }

			 InterCom_Envie_mensaje(&inter_cont,&comando,0);
			 mensaje_completo==NO;
			 i=0;
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
    {/*	//c_salidas.t_cfg.on=1;
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





    	inter_mensaje.msg[0]='S';
    	inter_mensaje.msg[1]='E';
    	inter_mensaje.msg[2]='1';
    	inter_mensaje.msg[3]='F';
    	inter_mensaje.msg[4]='1';
    	inter_mensaje.msg[5]=';';
    	inter_mensaje.msg[6]='E';
    	inter_mensaje.msg[7]='1';
    	inter_mensaje.msg[8]='1';
    	inter_mensaje.msg[9]=';';
    	inter_mensaje.msg[10]='n';
    	inter_mensaje.msg[11]=';';
    	inter_mensaje.msg[12]='n';


    	InterCom_Envie_mensaje(&inter_cont,&inter_mensaje,0);
    	vTaskDelayUntil( &xLastWakeTime, time_pin );



    }
}

