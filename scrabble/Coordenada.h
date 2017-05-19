#ifndef _COORDENADA_H_
#define _COORDENADA_H_
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include "Constants.h" 


using namespace std;

enum Orientacion {HORIZONTAL, VERTICAL};

class Coordenada 
{
  private:
 	int fila;
 	int columna;

  public:
  	Coordenada(int fila=-1, int columna=-1); // Constructor por defecto
	Coordenada(string coord, Orientacion &orientacion); // Constructor a partir de un string. Devuelve la orientacion por referencia
 	int getFila() const { return fila; } // Devuelve el valor de la fila (inline)
 	int getColumna() const { return columna; } // Devuelve el valor de la columna (inline)
 	void setFila(int fila); // Establece el valor de la fila
	void setColumna(int columna); // Establece el valor de la columna
	bool isError() const; // Devuelve true si la coordenada es erronea

	static const Coordenada coordenadaError; // Coordenada por defecto (-1,-1)
};

#endif
