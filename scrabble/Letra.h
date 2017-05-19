#ifndef _LETRA_H_
#define _LETRA_H_
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include "Constants.h" 


using namespace std;

class Letra
{
  friend ostream& operator<<(ostream &os,const Letra &l);
private:
  char simbolo;
  
public:
  Letra(char simbolo = CASILLAVACIA);
  int getPuntuacion()const;
  char getSimbolo()const;
  void setSimbolo(char simbolo);
};

#endif