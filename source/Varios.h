/* Definiciones generales */
#if !defined(VARIOS_H)

#define VARIOS_H

#define SI	1
#define NO	0

typedef struct Fecha Fecha;
struct Fecha
   {
   int anio;
   char  mes,
         dia;
   };
   
typedef struct Hora Hora;
struct Hora
   {
   char  hora,
         minuto,
         segundo;
   };
   
typedef struct Tiempo Tiempo;
struct Tiempo
   {
   Fecha f;
   Hora h;
   char s;  /* Dia de la semana: 0 es lunes, 6 es domingo */
   };

#endif