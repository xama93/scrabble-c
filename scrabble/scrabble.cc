// 48675238Q JOAQUIN VASALO VICEDO 
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string.h>
#include <ctype.h>
#include <fstream>

#include"Coordenada.h"
#include"Letra.h"
#include"Tablero.h"
#include"Movimiento.h"
#include"Constants.h"
#include"Rack.h"
#include"Jugador.h"
#include"Partida.h"

using namespace std;


/***********************************************************************************************************/

// Limpiar el buffer
void limpiarBuffer() 
{ 
    while(cin.get() != '\n'); 
}

// Cabeceras de las funciones que deben implementarse. No hace falta que esten declarados los prototipos, 
// pero si que deben estar implementadas con estos nombres y parametros

void comenzarPartida();
bool ProcesarArgumentos(int argc,char *argv[]);



int main(int argc, char *argv[])
{
  char opc;
  bool cargado;
  bool argu = true;
  string nombrefich;
  

  if(argc > 1)				// Si detecta argumentos los analizamos y ejecutamos
  {
  
    argu = ProcesarArgumentos(argc,argv);
    
    if (argu == false)
    {
      cout <<"Sintaxis: "<< argv[0] << " [-C <fichero.txt>] [-J <numjugadores>]" << endl;
    }
  }
  
  if(argu)
  {
    do
    {
      cout << RALLAS << endl;
      cout << SCRABBLE << endl;
      cout << RALLAS << endl;
      cout << NUEVA << endl;
      cout << CARGA << endl;
      cout << SAL << endl;
      cout << OPCI;
      cin >> opc;
    
    
      if(opc == '1')
      {
	limpiarBuffer();
	comenzarPartida();
      }
    
      if(opc == '2')
      {
	limpiarBuffer();
	Partida p;			// Inicializamos las varibles bases del programa
	p.inicializarSemilla();
	cout << NOMGUARDA;		
	getline(cin,nombrefich);
	cargado = p.cargar(nombrefich);
	if(cargado == false)
	{
	  cout << ERRORAPERT << endl;
	}
	else
	{
	  p.jugar();
	}
      }
      if(opc != 'q' && opc != '1' && opc != '2')
      {
	cout << ERRO << endl;
      }
    
    }while(opc != 'q');
  }
}


/*Funcion que se llama desde el menu principal para comenzar una nueva partida. En ella se pedira al usuario el numero de jugadores y 
creara una variable de tipo Partida, invocando posteriormente a las funciones inicializarPartida y jugar.*/
void comenzarPartida()
{
  
  int jugadores;
 
  
  do
  { 
    cout << NUMJUG;
    cin >> jugadores;
    
  }while(jugadores < 1 || jugadores > 4);
 
  limpiarBuffer();
  Partida p(jugadores);
  p.jugar();
}


/*Modulo que procesa si hay error en la introduccion de parametros al programa*/
bool ProcesarArgumentos(int argc,char *argv[])
{
  bool correcto = true;
  bool cargado;
  int n;
  string carga;
  
 
  if(argc != 3)		// Comprobamos que el numero de argumentos sea 3(ej.scrabble -J n)
  {
    correcto = false;
  }
  else
  { 
    if(strcmp(argv[1],"-C") == 0)	// Si encontramos -C
    {
      carga = argv[2];			// Pasamos el parametro a un string auxiliar
      Partida p;			// Inicializamos las varibles bases del programa y cargamos
      p.inicializarSemilla();
      cargado = p.cargar(carga);
      
      if(cargado == false)
      {
	cout << ERRORAPERT << endl;
      }
      else
      {
	p.jugar();
      }
    }
    else if(strcmp(argv[1],"-J") == 0)	// Si encontramos -J
    {
      n = atoi(argv[2]);		// Convierte el numero de jugadores de char a int
	
      if(n >= 1 && n <= 4)
      {
	Partida p(n);			// Inicializamos la partida 
	p.jugar();  
      }
      else
      {
	cout << ERRONUMJUG << endl;
      }	
    }
    else
    {
      correcto = false;
    }
  }
  return(correcto);
}


