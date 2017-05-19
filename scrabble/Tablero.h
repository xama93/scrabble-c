#ifndef _TABLERO_H_
#define _TABLERO_H_
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include "Constants.h" 
#include "Letra.h" 


using namespace std;

enum Casilla {NORMAL, DOBLELETRA, TRIPLELETRA, DOBLEPALABRA, TRIPLEPALABRA};

class Tablero
{
private:
  Casilla tablero[kFILAS][kCOLUMNAS];
  
public:
  Tablero();
  void inicializar();
  Casilla getCasilla(int fila, int columna)const;
  void imprimir(Letra letras[15][15])const;
};

#endif