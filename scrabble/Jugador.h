#ifndef _JUGADOR_H_
#define _JUGADOR_H_
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include "Constants.h" 
#include "Rack.h"


using namespace std;

class Jugador
{
private:
  int puntuacion;
  Rack rack;
public:    
  Jugador();
  Rack getRack()const;
  void setRack(Rack r);
  int getPuntuacion()const;
  void setPuntuacion(int puntuacion);
};

#endif
