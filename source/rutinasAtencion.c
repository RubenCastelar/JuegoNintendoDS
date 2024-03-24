/*-------------------------------------
rutinasAtencion.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"
#include "perifericos.h"
#include "fondos.h"
#include "sprites.h"

int tiempo;
int x = 127;
int y = 110;
int tick = 0;
bool lanzarbala = false;
int ybola;
int xbola = 256;
int puntuacion;
int aux;
bool habilitarSalto;


void RATeclado() {

    tecla=TeclaPulsada();

	if (ESTADO == START && tecla==ABAJO) {
		consoleClear();
		visualizarFondoInGameEXPLICACION();
		iprintf("\x1b[11;3HSTART PARA EXPLICACION");
		iprintf("\x1b[13;3HDESPLAZATE CON LAS FLECHAS ⬇ ↑");
		ESTADO = PANTALLA_EXPLICACION;
	}

	if (ESTADO == PANTALLA_EXPLICACION && tecla == ARRIBA) {
        consoleClear();
		visualizarFondoInGameStart();
		iprintf("\x1b[11;3HSTART PARA COMENZAR");
		iprintf("\x1b[13;3HDESPLAZATE CON LAS FLECHAS");
		ESTADO=START;       
    }

	if(ESTADO == ELIMINADO && tecla==A) {
		lanzarbala = false;
		saltar = 0;
		xdir = 0;
		bajando = false;
		ESTADO = JUEGO;
		xbola = 256;
		x = 127;
		y = 110;
		puntuacion = 0;
		consoleClear();
		visualizarFondoInGame();
		iprintf("\x1b[11;3HSELECT PARA PAUSAR");	
		MostrarMario(0,x,y);	
	}

}

void RATiempo() {

	if(ESTADO==JUEGO) {
		tick++;

		if (tick % 100 == 0){		//Una vez entras en el juego, el salto tarda unos instantes en permitirse
			habilitarSalto = true;
		}

		iprintf("\x1b[6;3HTU PUNTUACION ACTUAL ES: %d",puntuacion);
		if (saltar == 1){ 				//Rutina para controlar hacia que lado mira Mario y cambiar la dirección de su cuerpo
            if (xdir == -1 || aux==-1){
                MostrarMario_saltandoIzquierda(0,x,y);
            }
            else{
                MostrarMario_saltando(0,x,y);
            }
        }
        else if (y==110 || !saltar){
            if (xdir == 1 || aux==1){
                MostrarMario(0,x,y);
            }
            else if (xdir == -1|| aux==-1){
                MostrarMarioIzquierda(0,x,y);
            }
        }		
	
		MostrarBolaFuego(1,xbola,ybola);

				
			if(saltar == 1 && !bajando) {	//Rutina para controlar si Mario está saltando, bajando, o a nivel del suelo 
				if (y > 60){
					y-=2;
				} else if (y == 60){
					bajando = true;
				}
			} else if (saltar == 1 && bajando){
				if (y < 110){
					y+=2;
				} else if (y == 110){
					bajando = false;
					saltar = 0;
				}
			}
			if (xdir == 1 && x < 240){
				x+=2;
			}
			if (xdir == -1 && x > 0){
				x-=2;
			}
		

		if (lanzarbala == false){		//Rutina para lanzamiento de la Bala (altura aleatoria comprendida entre 2 valores)
			lanzarbala = true;
			ybola = rand() % 30 + 80;
		}

		if (lanzarbala == true && xbola > 0){
			if (tick % 1 == 0){
				xbola = xbola - (puntuacion / 5 +1);
			}
			if (xbola <= 1){
				lanzarbala = false;
				puntuacion++;
				xbola = 256;
			}
		}

		if (puntuacion <4 ) iprintf("\x1b[15;3HVelocidad: Lenta");	//Rutina para controlar el nivel en el que te encuentras
        else if (puntuacion ==4 && xbola == 256){
            consoleClear();
            iprintf("\x1b[6;3HPuntuacion actual=%d", puntuacion);
            iprintf("\x1b[11;3HSELECT PARA PAUSAR");
            iprintf("\x1b[15;3HAumentando velocidad!");}
        else if (puntuacion >= 5 && puntuacion <9 && xbola == 256)
        {
            consoleClear();
            iprintf("\x1b[6;3HPuntuacion actual=%d", puntuacion);
            iprintf("\x1b[11;3HSELECT PARA PAUSAR");
            iprintf("\x1b[15;3HVelocidad: Intermedia");}
        else if (puntuacion == 9 && xbola == 256){
            consoleClear();
            iprintf("\x1b[6;3HPuntuacion actual=%d", puntuacion);
            iprintf("\x1b[11;3HSELECT PARA PAUSAR");
            iprintf("\x1b[15;3HAumentando velocidad!");}
        else if (puntuacion > 9 && puntuacion <14 && xbola == 256){
            consoleClear();
            iprintf("\x1b[6;3HPuntuacion actual=%d", puntuacion);
            iprintf("\x1b[11;3HSELECT PARA PAUSAR");
            iprintf("\x1b[15;3HVelocidad: Rapida");}
        else if (puntuacion == 15 && xbola == 256){
            consoleClear();
            iprintf("\x1b[6;3HPuntuacion actual=%d", puntuacion);
            iprintf("\x1b[11;3HSELECT PARA PAUSAR");
            iprintf("\x1b[15;3HQUE BARBARIDAD!!");
            iprintf("\x1b[15;3HCuidado con la velocidad...!");
		}
	}	
}	


void EstablecerVectorInt() {
    irqSet(IRQ_TIMER0, RATiempo);
    irqSet(IRQ_KEYS, RATeclado);    
}








