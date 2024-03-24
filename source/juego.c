/*---------------------------------------------------------------------------------
Este código se ha desarrollado basándose en el código de dovoto "Simple sprite demo" 
y en otro ejemplo de Jaeden Ameronen
---------------------------------------------------------------------------------*/

#include <windows.h>
#include <nds.h> 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estándar de C
#include <stdlib.h>		//librería estándar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarrolladas por nosotros para el proyecto
	
#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"
#include "sprites.h"

int tiempo, saltar, tecla, x, y, xdir, ESTADO ,xbola, ybola, puntuacion, aux;
bool bajando, lanzarbala, habilitarSalto;
touchPosition pos_pantalla;


void juego()
{		
	saltar = 0;
	bajando = false;
	habilitarSalto = true;
	xdir = 0;
	ESTADO=ESPERA;
	EstablecerVectorInt();
	visualizarFondoInicio();
	

	while(1) {
		if (ESTADO==ESPERA) {		//Primer estado, pantalla de espera
			iprintf("\x1b[11;5H PULSA A PARA COMENZAR");

			if (TeclaDetectada()==1) {
				tecla = TeclaPulsada();
				if (tecla==A) {  
					consoleClear();	
					iprintf("\x1b[11;3HSTART PARA COMENZAR");
					iprintf("\x1b[13;3HDESPLAZATE CON LAS FLECHAS");
					visualizarFondoInGameStart();
					ESTADO = START;			
				}
			}
		}

		if (ESTADO==START) {		//Menú, con la opcion de START seleccionada (de pulsarse la tecla START empieza el juego)

			if(TeclaDetectada()==1) {
				tecla = TeclaPulsada();
				if (tecla==START) {
					consoleClear();
					visualizarFondoInGame();
					iprintf("\x1b[11;3HSELECT PARA PAUSAR");
					x = 127;
	 				y = 110;
					ESTADO = JUEGO;
					MostrarMario(0,x,y);
				} 
			}
		}

		if (ESTADO==PANTALLA_EXPLICACION) {		//Menú, con la opcion de EXPLICACION seleccionada (de pulsarse la tecla START empieza la explicación)
			if (TeclaDetectada()==1) {
				tecla = TeclaPulsada();
				if (tecla==START) {
					consoleClear();
					iprintf("\x1b[8;5HMuevete con las flechas");					
					iprintf("\x1b[11;9HSalta con la A");
					iprintf("\x1b[14;6HPista: Evita la bala");
					iprintf("\x1b[17;7HSELECT para volver");
					ESTADO = EXPLICACION_DENTRO;
					visualizarFondoInicio();
				}
			}
		}

		if (ESTADO==EXPLICACION_DENTRO) { 	//Estado de dentro de la explicación, de pulsarse SELECT vuelve al menú
		
			if(TeclaDetectada()==1) {
				tecla=TeclaPulsada();
				if (tecla==SELECT){
					ESTADO = PANTALLA_EXPLICACION;
					consoleClear();
					visualizarFondoInGameEXPLICACION();
					iprintf("\x1b[11;3HSTART PARA EXPLICACION");
					iprintf("\x1b[13;3HDESPLAZATE CON LAS FLECHAS");
				}
			}
		}

		if (ESTADO==JUEGO) {		//Comienza el juego. Con la tecla A, se salta. Con la tecla SELECT se pausa, y con el START se reanuda. 

			if (TeclaDetectada()==1) {
				tecla = TeclaPulsada();
				if (y == 110){
					if (tecla == A && habilitarSalto){
						saltar = 1;
					}	
				}
				if (tecla==DERECHA) {
					xdir = 1;
					aux = 1;
				} else if (tecla==IZQUIERDA) {
					xdir = -1;
					aux = -1;
				}
			} else {
				xdir = 0;
			}

			if (x<=xbola + 14 && x+14>=xbola && y<=ybola+16 && y + 16 >= ybola) {
				saltar = 0;
				bajando = false;
				ESTADO = ELIMINADO;
				habilitarSalto = false;
				consoleClear();
				aux=puntuacion;
				iprintf("\x1b[7;3HTU PUNTUACION HA SIDO:%d",aux );
				iprintf("\x1b[10;3HHAS SIDO ELIMINADO!");
		 		iprintf("\x1b[13;3HA PARA VOLVER A EMPEZAR");
		 		iprintf("\x1b[16;3HPANTALLA TACTIL PARA MENU");
			}

			else if (tecla == SELECT){
				consoleClear();
				iprintf("\x1b[11;5HESTAS EN PAUSA");
				iprintf("\x1b[14;5HSTART PARA REANUDAR");
				ESTADO = PAUSA;
				visualizarFondoInicio();
				PararTempo();
			}
		}

		if (ESTADO == PAUSA){		//Estado de pausa
			if (TeclaDetectada()==1){
				tecla = TeclaPulsada();
				if (tecla == START){
				PonerEnMarchaTempo();
				ESTADO = JUEGO;
				consoleClear();
				visualizarFondoInGame();
				iprintf("\x1b[11;3HSELECT PARA PAUSAR");
				}
			}
		}

		if (ESTADO==ELIMINADO) {		//Estado eliminado. Tocando la pantalla táctil vuelve al menú, y con la tecla A vuelve a empezar el juego
			while (pos_pantalla.px==0 && pos_pantalla.py==0 && TeclaDetectada()==0){
			touchRead(&pos_pantalla);
			}
			if(pos_pantalla.px!=0 && pos_pantalla.py!=0) {
				BorrarBolaFuego(1, xbola, ybola);
				BorrarMario(0, x, y);
				BorrarMario_saltando(0,x,y);	
				BorrarMarioIzquierda(0,x,y);				
				consoleClear();
				visualizarFondoInGameStart(); 
				iprintf("\x1b[11;3HSTART PARA COMENZAR");
				iprintf("\x1b[13;3HDESPLAZATE CON LAS FLECHAS");	
				ESTADO = START;
				puntuacion = 0;
				lanzarbala = false;
				xbola = 256;
				pos_pantalla.px = 0;
				pos_pantalla.py = 0;
		 	}		 
			}
	}
}








