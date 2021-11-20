/*
 * lcd.c
 *
 *  Created on: 10 nov. 2021
 *      Author: Diego Avellaneda
 */
#include "lcd.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"


// ---------------------- Function to initialize display----------------
//void init_LCD_display(){
//	// Hardcodeamos el RW que en principio no lo necesitamos por que lo trabajamos en write mode
//	GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_RW_PIN,0);
//	// En el comienzo RS esta en 0 pero cuando vamos a escribir se pone en 1
//	GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_RS_PIN,0);
//	// El enable segun el diagrama de tiempos para la escritura arranca en LOW
//	GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_E_PIN,0);
//
//	//4-Bit mode
//	//Se empieza a enviar los comandos, el primero corresponse a 0011 0000
//	//teniendo en cuenta que ya se tienen los LSB en 0000 se envia unicamente 0010
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
//	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,1);
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,1);
//
//	enable_click_routine();
//
//
//	 //--------------------------------------------Return Home
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
//	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,0);
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,0);
//
//	enable_click_routine();
//
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
//	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,1);
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,0);
//
//	enable_click_routine();
//	 //--------------------------------------------Turn display On, without cursos
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
//	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,0);
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,0);
//
//	enable_click_routine();
//
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,1);
//	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,1);
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,1);
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,1);
//
//	enable_click_routine();
//
//	 //------------------------------------------Clear the display
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
//	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,0);
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,0);
//
//	enable_click_routine();
//
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
//	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,0);
//	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,1);
//
//	enable_click_routine();
//
//
//}

void init_LCD_display(){
	// Hardcodeamos el RW que en principio no lo necesitamos por que lo trabajamos en write mode
	GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_RW_PIN,0);
	// En el comienzo RS esta en 0 pero cuando vamos a escribir se pone en 1
	GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_RS_PIN,0);
	// El enable segun el diagrama de tiempos para la escritura arranca en LOW
	GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_E_PIN,0);

	//4-Bit mode
	//Se empieza a enviar los comandos, el primero corresponse a 0011 0000
	//teniendo en cuenta que ya se tienen los LSB en 0000 se envia unicamente 0010
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,1);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,0);

	enable_click_routine();

	 //--------------------------------------------Turn display On, without cursos
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,0);

	enable_click_routine();

	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,1);
	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,1);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,1);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,1);

	enable_click_routine();


	 //--------------------------------------------Return Home
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,0);

	enable_click_routine();

	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,1);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,0);

	enable_click_routine();

	 //------------------------------------------Clear the display
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,0);

	enable_click_routine();

	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,1);

	enable_click_routine();


}


void enable_click_routine(){
	const TickType_t eDelay = 3 / portTICK_PERIOD_MS;

	GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_E_PIN,1);
	vTaskDelay( eDelay );
	GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_E_PIN,0);
}

void write_character(char render_char){
	 //--------------------------------------------Transmit data
	GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_RS_PIN,1);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,render_char & 0x80 );
	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,render_char & 0x40);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,render_char & 0x20);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,render_char & 0x10);

	enable_click_routine();

	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,render_char & 0x08);
	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,render_char & 0x04);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,render_char & 0x02);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,render_char & 0x01);

	enable_click_routine();
}



void write_second_line(){
	 //--------------------------------------------Transmit data
	GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_RS_PIN,0);
	 //------------------------------------------Escribir en la segunda linea
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,1);
	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,1);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,0);

	enable_click_routine();

	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,0);

	enable_click_routine();
}

void write_line(char *line){

	while(*line !='\0'){
		write_character(*line);
		line++;
	}
}

void clear_and_home(){
	// Hardcodeamos el RW que en principio no lo necesitamos por que lo trabajamos en write mode
	GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_RW_PIN,0);
	// En el comienzo RS esta en 0 pero cuando vamos a escribir se pone en 1
	GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_RS_PIN,0);
	 //------------------------------------------Clear the display
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,0);

	enable_click_routine();

	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,1);

	enable_click_routine();

	 //--------------------------------------------Return Home
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,0);

	enable_click_routine();

	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
	GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,1);
	GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,0);

	enable_click_routine();


}

void home(){
	 //--------------------------------------------Transmit data
	GPIO_WritePinOutput(GPIOA,BOARD_INITPINS_RS_PIN,0);
	 //--------------------------------------------Return Home
		GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
		GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
		GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,0);
		GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,0);

		enable_click_routine();

		GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D7_PIN,0);
		GPIO_WritePinOutput(GPIOB,BOARD_INITPINS_D6_PIN,0);
		GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D5_PIN,1);
		GPIO_WritePinOutput(GPIOE,BOARD_INITPINS_D4_PIN,0);

		enable_click_routine();
}
