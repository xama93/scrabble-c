#ifndef _MOVIMIENTO_H_
#define _MOVIMIENTO_H_
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include "Constants.h" 
#include "Coordenada.h"
#include "Letra.h"

using namespace std;


class Movimiento
{
  friend ostream& operator<<(ostream &os,const Movimiento &m);
private:
  int puntuacion;
  vector<Letra> palabra;
  Coordenada origen;
  Orientacion orientacion;
public:
  Movimiento();
  Movimiento(string orden);
  Coordenada getOrigen()const;
  Orientacion getOrientacion()const;
  int getPuntuacion()const;
  vector<Letra>getPalabra()const;
  string getPalabraString()const;
  void setPuntuacion(int puntuacion);
  
};

#endif