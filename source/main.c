/*---------------------------------------------------------------------------------
Este código se ha desarrollado basándose en el código de dovoto "Simple sprite demo" 
y en otro ejemplo de Jaeden Ameronen
---------------------------------------------------------------------------------*/

#include <nds.h> 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estandar de C
#include <stdlib.h>		//librería estandar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarrolladas por nosotros para el proyecto

#include "graficos.h"		
#include "definiciones.h"
#include "sprites.h"
#include "juego.h"


//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	inicializarGraficosSprites();
	HabilitarInterrupciones();
	ConfigurarTemporizador(56798,0x00C1); //60 ticks segundo 
	ConfigurarTeclado(0x40F1); //A y las flechas por interrupción.

	juego();

	return(0);

}

