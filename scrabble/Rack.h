#ifndef _RACK_H_
#define _RACK_H_
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include "Constants.h" 
#include "Letra.h"
#include <vector>


using namespace std;

class Rack
{
  friend ostream& operator<<(ostream &os,const Rack &r);
  friend istream& operator>>(istream &os,Rack &r);
  
private:

  vector<Letra>letras;
 
public:
  Rack();
  void completar(vector<Letra> &bolsa);
  bool sacarLetra(Letra l);
  string getString()const;
  int size()const;
};

#endif