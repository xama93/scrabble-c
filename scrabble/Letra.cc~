#include"Letra.h"
#include"Constants.h"
#include<iostream>

using namespace std;

Letra::Letra(char simbolo)
{
  this -> simbolo = toupper(simbolo);
}

int Letra::getPuntuacion()const
{
  int index;
  int numletra;
  
  numletra = simbolo - 'A'; // Pasar la letra l a un numero
  if(simbolo == CASILLAVACIA)
  {
   index = 0;
  }
  else
  {
    if(PUNTUACIONLETRAS[numletra] == 0)
    {
      index = 0;
    }
    else if(PUNTUACIONLETRAS[numletra] == 1)
    {
      index = 1;
    }
    else if(PUNTUACIONLETRAS[numletra] == 2)
    {
      index = 2;
    }
    else if(PUNTUACIONLETRAS[numletra] == 3)
    {
      index = 3;
    }
    else if(PUNTUACIONLETRAS[numletra] == 4)
    {
      index = 4;
    }
    else if(PUNTUACIONLETRAS[numletra] == 5)
    {
      index = 5;
    }
    else if(PUNTUACIONLETRAS[numletra] == 8)
    {
      index = 8;
    }
    else 
    {
      index = 0;
    }
  }
  return(index);
}

char Letra::getSimbolo()const
{
  return(simbolo);
}

void Letra::setSimbolo(char simbolo)
{
  this -> simbolo = simbolo;
}

ostream& operator<<(ostream &os,const Letra &l)//no seria simbolo? en lugar de l
{
  os << l.getSimbolo();
  int numletra;
  
  numletra = l.getSimbolo() - 'A'; // Pasar la letra l a un numero
  
  if(PUNTUACIONLETRAS[numletra] == 0)
  {
    os << SUPERINDEX[0]; 
  }
  else if(PUNTUACIONLETRAS[numletra] == 1)
  {
    os << SUPERINDEX[1];
  }
  else if(PUNTUACIONLETRAS[numletra] == 2)
  {
    os << SUPERINDEX[2];
  }
  else if(PUNTUACIONLETRAS[numletra] == 3)
  {
    os << SUPERINDEX[3];
  }
  else if(PUNTUACIONLETRAS[numletra] == 4)
  {
    os << SUPERINDEX[4];
  }
  else if(PUNTUACIONLETRAS[numletra] == 5)
  {
    os << SUPERINDEX[5];
  }
  else if(PUNTUACIONLETRAS[numletra] == 8)
  {
    os << SUPERINDEX[8];
  }
  else 
  {
    os << SUPERINDEX[0];
  }
  return(os);
}