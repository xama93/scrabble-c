#include"Rack.h"
#include<iostream>

using namespace std;

Rack::Rack()
{
}

void Rack::completar(vector<Letra> &bolsa)
{
  int numero;
  int numelementos;
  int i;
  
  if(letras.size()>0)
  {
  if(letras[0].getSimbolo() >= 'A' && letras[0].getSimbolo() <= 'Z')  // En caso de rellenar un rack en las siguientes tiradas
  {               
    for(i = this->size(); i < KRACK; i++)// i toma como valor el tamaño inicial del string y lo completa hasta llegar a 7  
    {
      numelementos = bolsa.size();      // Con esto controlamos que no salte error en caso de sacar 97-96-97 en random al disminuir el tamanyo de la bolsa
    
      if(bolsa.size() == 0)
      {
	i = KRACK;                      // Si no quedan elementos en la bolsa sal del bucle
      }
      else
      {
	numero = rand() % numelementos; // Random 
	letras.push_back(bolsa[numero]);    // Añadimos al rack las letras de la bolsa
	bolsa.erase(bolsa.begin() + numero);          // Eliminamos los elementos de la bolsa
      }
    }
  }
  else
  {
    for(i = 0; i < KRACK; i++)    
    {
      numelementos = bolsa.size();     // Con esto controlamos que no salte error en caso de sacar 97-96-97 en random al disminuir el tamanyo de la bolsa
    
      if(bolsa.size() == 0)
      {
	i = KRACK;                     // Si no quedan elementos en la bolsa sal del bucle
      
      }
      else
      {
	numero = rand() % numelementos; // Random 
	letras.push_back(bolsa[numero]);    // Añadimos al rack las letras de la bolsa
	bolsa.erase(bolsa.begin() + numero);          // Eliminamos los elementos de la bolsa
      }
    }
  }
  }else
  {
	  for(i = 0; i < KRACK; i++)
	      {
	        numelementos = bolsa.size();     // Con esto controlamos que no salte error en caso de sacar 97-96-97 en random al disminuir el tamanyo de la bolsa

	        if(bolsa.size() == 0)
	        {
	  	i = KRACK;                     // Si no quedan elementos en la bolsa sal del bucle

	        }
	        else
	        {
				if(bolsa.size()!=7){
					numero = rand() % numelementos; // Random
				}else{
					numero=i;
				}
				letras.push_back(bolsa[numero]);    // Añadimos al rack las letras de la bolsa
				if(bolsa.size()!=7){
					bolsa.erase(bolsa.begin() + numero);
				}// Eliminamos los elementos de la bolsa
	        }
	      }
  }
}

bool Rack::sacarLetra(Letra l)
{
  bool mov = false;
  int i;
  
  for(i = 0; i < this->size(); i++)
  {
    if(l.getSimbolo() == letras[i].getSimbolo())
    {
      letras.erase(letras.begin() + i);
      mov = true;
      i = this->size();
    }
  }
  return(mov);
}

string Rack::getString()const
{
  string aux;
  
  for(int i = 0; i < this->size(); i++)
  {
	aux += letras[i].getSimbolo();
  }
  
  return(aux);
}
  
int Rack::size()const
{
  return(letras.size());
}

ostream& operator<<(ostream &os,const Rack &r)
{
	for(int i=0;i<r.size();i++){
		os<<r.letras[i];
	}
  return(os);
}

istream& operator>>(istream &os,Rack &r)
{
  string aux = "";
  os >> aux;
  
  for(unsigned int i = 0; i < aux.size(); i++)
  {
    Letra l(aux[i]);
    r.letras.push_back(l);
  }
  
  return(os);
}
