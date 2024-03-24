#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

#include "sprites.h"
#include "definiciones.h"

u16* gfxMario;
u16* gfxbola;
u16* gfxMario_saltando;


void memoriaReserva()
{
	gfxMario= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxbola= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxMario_saltando= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
}

void EstablecerPaletaPrincipal() {

	SPRITE_PALETTE[1] = RGB15(31,0,0); // rojo
    SPRITE_PALETTE[2] = RGB15(31,31,0); // Amarillo fuerte
    SPRITE_PALETTE[3] = RGB15(31,31,31); // Blanco
    SPRITE_PALETTE[12] = RGB15(31,19,0); //Naranja
    SPRITE_PALETTE[14] = RGB15(25,0,0); // Marron
    SPRITE_PALETTE[13] = RGB15(19,0,4); //Rojo
	SPRITE_PALETTE[22] = RGB15(16,16,0); //Verde
	SPRITE_PALETTE[6] = RGB15(0,0,0); //Negro
}

u8 bola[256]={
0	,	0	,	0	,	0	,	0	,	0	,	0	,	6	,	0	,	0	,	0	,	0	,	0	,	6	,	6	,	6	,
0	,	0	,	0	,	0	,	6	,	6	,	6	,	0	,	0	,	0	,	0	,	6	,	6	,	3	,	6	,	6	,
0	,	0	,	6	,	6	,	3	,	3	,	6	,	6	,	0	,	6	,	3	,	6	,	3	,	3	,	6	,	6	,
0	,	6	,	3	,	3	,	3	,	3	,	6	,	6	,	6	,	6	,	6	,	3	,	3	,	6	,	6	,	6	,
6	,	6	,	6	,	6	,	0	,	0	,	6	,	6	,	0	,	0	,	0	,	0	,	6	,	6	,	0	,	0	,
6	,	6	,	6	,	6	,	6	,	0	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,
6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,
6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	3	,	3	,	6	,	6	,	6	,	6	,	6	,
6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	3	,	3	,
6	,	6	,	6	,	6	,	6	,	3	,	3	,	3	,	0	,	6	,	6	,	6	,	6	,	3	,	3	,	3	,
0	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	0	,	0	,	6	,	6	,	6	,	6	,	6	,	6	,
0	,	0	,	0	,	0	,	6	,	6	,	6	,	6	,	0	,	0	,	0	,	0	,	0	,	0	,	6	,	6	,
6	,	3	,	3	,	3	,	6	,	6	,	6	,	6	,	6	,	3	,	3	,	3	,	6	,	6	,	6	,	6	,
3	,	3	,	3	,	6	,	6	,	6	,	6	,	6	,	3	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,
6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,
6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	0	,	0	,	0	,	6	,
};

u8 Mario[256] = 
{
0	,	0	,	1	,	1	,	1	,	1	,	1	,	1	,	0	,	0	,	1	,	1	,	1	,	1	,	1	,	1	,
0	,	0	,	22	,	22	,	22	,	22	,	12	,	12	,	0	,	22	,	12	,	22	,	12	,	12	,	12	,	12	,
0	,	22	,	12	,	22	,	12	,	12	,	12	,	12	,	0	,	22	,	12	,	22	,	22	,	22	,	12	,	12	,
0	,	22	,	22	,	12	,	12	,	12	,	12	,	12	,	0	,	0	,	0	,	12	,	12	,	12	,	12	,	12	,
1	,	1	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	1	,	1	,	1	,	1	,	0	,	0	,	0	,
12	,	22	,	12	,	0	,	0	,	0	,	0	,	0	,	12	,	22	,	12	,	0	,	0	,	0	,	0	,	0	,
12	,	22	,	12	,	12	,	12	,	0	,	0	,	0	,	12	,	12	,	22	,	12	,	12	,	12	,	0	,	0	,
12	,	22	,	22	,	22	,	22	,	0	,	0	,	0	,	12	,	12	,	12	,	12	,	0	,	0	,	0	,	0	,
0	,	0	,	22	,	22	,	1	,	22	,	22	,	22	,	0	,	22	,	22	,	22	,	1	,	22	,	22	,	22	,
0	,	22	,	22	,	22	,	1	,	22	,	22	,	22	,	22	,	22	,	22	,	1	,	1	,	2	,	1	,	1	,
12	,	12	,	22	,	1	,	1	,	1	,	1	,	1	,	12	,	12	,	12	,	1	,	1	,	1	,	1	,	1	,
0	,	0	,	22	,	22	,	0	,	0	,	0	,	0	,	0	,	22	,	22	,	22	,	0	,	0	,	0	,	0	,
22	,	22	,	22	,	22	,	0	,	0	,	0	,	0	,	22	,	22	,	1	,	22	,	22	,	0	,	0	,	0	,
22	,	22	,	1	,	22	,	22	,	22	,	0	,	0	,	1	,	2	,	1	,	1	,	22	,	22	,	22	,	0	,
1	,	1	,	1	,	1	,	12	,	12	,	12	,	0	,	1	,	1	,	1	,	1	,	12	,	12	,	12	,	0	,
0	,	0	,	0	,	22	,	22	,	0	,	0	,	0	,	0	,	0	,	0	,	22	,	22	,	22	,	0	,	0	,
};
u8 Mario_saltando[256] = 
{
0	,	0	,	1	,	1	,	1	,	1	,	1	,	1	,	0	,	0	,	1	,	1	,	1	,	1	,	1	,	1	,
0	,	0	,	22	,	22	,	22	,	22	,	12	,	12	,	0	,	22	,	12	,	22	,	12	,	12	,	12	,	12	,
0	,	22	,	12	,	22	,	12	,	12	,	12	,	12	,	0	,	22	,	12	,	22	,	22	,	22	,	12	,	12	,
0	,	22	,	22	,	12	,	12	,	12	,	12	,	12	,	0	,	0	,	0	,	12	,	12	,	12	,	12	,	12	,
1	,	1	,	0	,	0	,	12	,	12	,	12	,	0	,	1	,	1	,	1	,	1	,	1	,	12	,	12	,	0	,
12	,	22	,	12	,	0	,	22	,	22	,	22	,	0	,	12	,	22	,	12	,	0	,	22	,	22	,	22	,	0	,
12	,	22	,	12	,	12	,	12	,	22	,	22	,	0	,	12	,	12	,	22	,	12	,	12	,	12	,	22	,	0	,
12	,	22	,	22	,	22	,	22	,	22	,	22	,	0	,	12	,	12	,	12	,	12	,	22	,	0	,	0	,	0	,
0	,	22	,	22	,	1	,	22	,	22	,	22	,	22	,	0	,	22	,	22	,	22	,	1	,	22	,	22	,	22	,
12	,	22	,	22	,	22	,	1	,	22	,	22	,	22	,	12	,	12	,	22	,	0	,	1	,	2	,	1	,	1	,
12	,	12	,	0	,	0	,	1	,	1	,	1	,	1	,	0	,	22	,	22	,	22	,	1	,	1	,	1	,	1	,
22	,	22	,	22	,	1	,	1	,	1	,	1	,	1	,	22	,	22	,	0	,	1	,	1	,	1	,	1	,	0	,
22	,	22	,	22	,	22	,	22	,	0	,	0	,	0	,	22	,	22	,	1	,	22	,	0	,	0	,	0	,	0	,
22	,	22	,	1	,	22	,	0	,	0	,	0	,	22	,	1	,	2	,	1	,	1	,	0	,	0	,	0	,	22	,
1	,	1	,	1	,	1	,	1	,	22	,	22	,	22	,	1	,	1	,	1	,	1	,	1	,	22	,	22	,	22	,
1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,
};


void GuardarSpritesMemoria(){ 
	
int i;
	//sprite de 16*16
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxMario[i] = Mario[i*2] | (Mario[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxMario_saltando[i] = Mario_saltando[i*2] | (Mario_saltando[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxbola[i] = bola[i*2] | (bola[(i*2)+1]<<8);				
	}	


}

/* Esta función dibuja un rombo en la posición x-y de pantalla. A cada rombo que se quiera mostrar en pantalla se le debe asignar un índice distinto, un valor entre 0 y 126 */

void MostrarMario(int indice, int x, int y)
{ 
 
	oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxMario,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
	oamUpdate(&oamMain);  
}

void MostrarMarioIzquierda(int indice, int x, int y)
{ 
 
	oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxMario,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		true, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
	oamUpdate(&oamMain);  
}

void MostrarMario_saltando(int indice, int x, int y)
{ 
 
	oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxMario_saltando,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
	oamUpdate(&oamMain);  
}

/* Esta función borra de la pantalla el Rombo con el índice indicado */
void BorrarMario(int indice, int x, int y)
{

	oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxMario,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}

void BorrarMarioIzquierda(int indice, int x, int y)
{

	oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxMario,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		true, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}

void MostrarMario_saltandoIzquierda(int indice, int x, int y)
{ 
 
	oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxMario_saltando,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		true, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
	oamUpdate(&oamMain);  
}

void BorrarMario_saltandoIzquierda(int indice, int x, int y)
{

	oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxMario_saltando,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		true, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}

void BorrarMario_saltando(int indice, int x, int y)
{

	oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxMario_saltando,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}


void MostrarBolaFuego(int indice, int x, int y)
{ 
 	oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxbola,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain);
}

void BorrarBolaFuego(int indice, int x, int y)
{
	oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxbola,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}

void MostrarBolaFuego2(int indice, int x, int y)
{ 
 	oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxbola,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain);
}

void BorrarBolaFuego2(int indice, int x, int y)
{
	oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxbola,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}

