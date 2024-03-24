
#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

/* Si queremos visualizar distintos fondos, aquí se debe incluir el fichero de cabecera (fichero .h) de cada fondo. Estos ficheros de cabecera se generan automáticamente durante la compilación. */

#include "fondos.h"
#include "graficos.h"
#include "FondoInGame.h"
#include "FondoInicio.h"
#include "FondoInGameEXPLICACION.h"
#include "FondoInGameStart.h"

/* Se elige el canal de DMA que se utilizará para copiar las imágenes en memoria.*/
static const int DMA_CHANNEL = 3;

/* Para cada fondo que se quiera visualizar hay que escribir un procedimiento como el siguiente */

void visualizarFondoInicio() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     FondoInicioBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     FondoInicioBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

void visualizarFondoInGame() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     FondoInGameBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     FondoInGameBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */  

}
void visualizarFondoInGameStart() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     FondoInGameStartBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     FondoInGameStartBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */  

}
void visualizarFondoInGameEXPLICACION() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     FondoInGameEXPLICACIONBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     FondoInGameEXPLICACIONBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */  

}

