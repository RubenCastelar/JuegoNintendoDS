/*-------------------------------------
perifericos.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"


int tecla; //variable para guardar la tecla pulsada



int TeclaDetectada() 
{
	//Devuelve TRUE si detecta que se ha pulsado alguna tecla.
	if ((~TECLAS_DAT & 0x03ff)!=0) return 1;
	else return 0;

}

int TeclaPulsada() 
{
	if((~TECLAS_DAT & 0x0001)!=0)return A;
	else if((~TECLAS_DAT & 0X0004)!=0)return SELECT;
	else if((~TECLAS_DAT & 0X0008)!=0)return START;
	else if((~TECLAS_DAT & 0X0010)!=0)return DERECHA;
	else if((~TECLAS_DAT & 0X0020)!=0)return IZQUIERDA;
	else if((~TECLAS_DAT & 0X0040)!=0)return ARRIBA;
	else if((~TECLAS_DAT & 0X0080)!=0)return ABAJO;
	else if((~TECLAS_DAT & 0X0100)!=0)return R;
	else if((~TECLAS_DAT & 0X0200)!=0)return L;
	//Devuelve el código de la tecla pulsada utilizando para ello las constantes definidas en 
	//definiciones.h:  A=0;B=1;SELECT=2;START=3;IZQUIERDA=4;DERECHA=5;
	//ARRIBA=6;ABAJO=7;R=8;L=9;
	else return -1;
}

void ConfigurarTeclado(int Conf_Tec)
{
	//Configuración del teclado. Modificar su registro de control en base a los bits
        //activados en el parametro Conf_Tec
	TECLAS_CNT |= Conf_Tec;
}

void ConfigurarTemporizador(int Latch, int Conf_Tempo)
{
	TIMER0_DAT = Latch; //Configuración del temporizador. El latch es el valor del registro de datos del temporizador
	TIMER0_CNT |= Conf_Tempo; //Activar los bits del registro de control necesarios en base a los bits activados en el parámetro Conf_Tempo
}

void HabilitarInterrupciones() {
	HabilitarIntTeclado();
	HabilitarIntTempo();
}
void HabilitarIntTeclado()
{
	IME = 0; //Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	IE |= 0x00001000; //Habilitar las interrupciones del teclado
	IME = 1; //y después volver a habilitar las interrupciones de forma general 
}

void InhibirIntTeclado()
{
	IME = 0;  //Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	IE &= 0xFFFFEFFF; //Deshabilitar las interrupciones del teclado
	IME = 1; //y después volver a habilitar las interrupciones de forma general 
}  

void HabilitarIntTempo()
{
	IME = 0; //Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	IE |= 0x00000008; //Habilitar las interrupciones del temporizador (timer0)
	IME = 1; //y después volver a habilitar las interrupciones de forma general 
}

void InhibirIntTempo()
{
	IME = 0; //Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	IE &= 0xFFFFFFF7;//Deshabilitar las interrupciones del temporizado (timer0)
	IME = 1; //y después volver a habilitar las interrupciones de forma general 
}

void PonerEnMarchaTempo()
{
	TIMER0_CNT |= 0x0080;
}

void PararTempo()
{
	TIMER0_CNT &= 0xFF7F;
}
