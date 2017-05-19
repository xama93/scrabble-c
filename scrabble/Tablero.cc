#include "Tablero.h"
#include "Constants.h"
#include <stdlib.h>


using namespace std;

Tablero::Tablero()
{
  inicializar();
}

void Tablero::inicializar()
{
  const Casilla inicializacionTablero[8][8] = {
    	{TRIPLEPALABRA, NORMAL,       NORMAL,       DOBLELETRA,   NORMAL,       NORMAL,      NORMAL,     TRIPLEPALABRA}, 
    	{NORMAL,        DOBLEPALABRA, NORMAL,       NORMAL,       NORMAL,       TRIPLELETRA, NORMAL,     NORMAL}, 
    	{NORMAL,        NORMAL,       DOBLEPALABRA, NORMAL,       NORMAL,       NORMAL,      DOBLELETRA, NORMAL}, 
    	{DOBLELETRA,    NORMAL,       NORMAL,       DOBLEPALABRA, NORMAL,       NORMAL,      NORMAL,     DOBLELETRA}, 
    	{NORMAL,        NORMAL,       NORMAL,       NORMAL,       DOBLEPALABRA, NORMAL,      NORMAL,     NORMAL}, 
    	{NORMAL,        TRIPLELETRA,  NORMAL,       NORMAL,       NORMAL,       TRIPLELETRA, NORMAL,     NORMAL}, 
	{NORMAL,        NORMAL,       DOBLELETRA,   NORMAL,       NORMAL,       NORMAL,      DOBLELETRA, NORMAL}, 
	{TRIPLEPALABRA, NORMAL,       NORMAL,       DOBLELETRA,   NORMAL,       NORMAL,      NORMAL,     DOBLEPALABRA}
    };

    for (int i=0; i<kFILAS; i++) 
    {
    	for (int j=0; j<kCOLUMNAS; j++) 
    	{
		int fila = (i<= kFILAS / 2 ? i : kFILAS - i - 1 );
		int columna = (j<= kCOLUMNAS / 2 ? j : kCOLUMNAS - j - 1 );
		
		tablero[i][j] = inicializacionTablero[fila][columna];
	}
    }
}

Casilla Tablero::getCasilla(int fila, int columna)const
{
  return(tablero[fila][columna]);
}

void Tablero::imprimir(Letra letras[15][15])const
{
  int i,j,k;
  k = 0;
  
  
  cout << LETR << endl;
  
  for(i = 0; i < kFILAS; i++)
  {
    cout << k + 1;        // Numeracion de las casillas izquierda
    
    if(k < 9)
    {
      cout << DOSESPACIO; // Espacios de numeracion derecha 1-10
    }
    else
    {
      cout << UNESPACIO;  // Espacios de numeracion derecha 11-15
    }
    
    for(j = 0; j < kCOLUMNAS; j++) 
    {
      if(tablero[i][j] == TRIPLEPALABRA)
      {
	if(letras[i][j].getSimbolo() >= 'A' && letras[i][j].getSimbolo() <= 'Z')
	{
	  cout << ROJO << letras[i][j] << RESETCOLOR;   
	}
	else
	{
	  cout << ROJO << DOSESPACIO << RESETCOLOR;
	}
      }
      else if(tablero[i][j] == DOBLELETRA)
      {
	if(letras[i][j].getSimbolo() >= 'A' && letras[i][j].getSimbolo() <= 'Z')
	{
	  cout << CYAN << letras[i][j] << RESETCOLOR;   
	}
	else
	{
	  cout << CYAN << DOSESPACIO << RESETCOLOR;
	}
      }
      else if(tablero[i][j] == DOBLEPALABRA)
      {
	if(letras[i][j].getSimbolo() >= 'A' && letras[i][j].getSimbolo() <= 'Z')
	{
	  cout << ROSA << letras[i][j] << RESETCOLOR;   
	}
	else
	{
	  cout << ROSA << DOSESPACIO << RESETCOLOR;
	}
      }
      else if(tablero[i][j] == TRIPLELETRA)
      {
	if(letras[i][j].getSimbolo() >= 'A' && letras[i][j].getSimbolo() <= 'Z')
	{
	  cout << AZUL << letras[i][j] << RESETCOLOR;   
	}
	else
	{
	  cout << AZUL << DOSESPACIO << RESETCOLOR;
	}
      }
      else
      {
	if(letras[i][j].getSimbolo() >= 'A' && letras[i][j].getSimbolo() <= 'Z')
	{
	  cout << letras[i][j];   
	}
	else
	{
	  cout << CASILLAVACIA << CASILLAVACIA;
	}
      }
    }
    cout << UNESPACIO << k + 1;// Numeracion de las casillas derecha y sus espacios
    k++;
    cout << endl;
  }
  cout << LETR << endl;
}
