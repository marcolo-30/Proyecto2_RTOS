#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "Varios.h"
#include "fsl_gpio.h"

typedef struct Keyboard_Control Keyboard_Control;
struct Keyboard_Control
   {
   TaskHandle_t tarea;
   };

char Keyboard_Inicie (Keyboard_Control *cKey, UBaseType_t prioridad);

void Keyboard_Procese (Keyboard_Control *cKey);


#endif /* KEYBOARD_H_ */
