#include "Movimiento.h"
#include <iostream>

using namespace std;

Movimiento::Movimiento()
{
  origen = Coordenada::coordenadaError;
  puntuacion = 0;
}

Movimiento::Movimiento(string orden)
{
	unsigned int j = 1;

	for(int i = 0; orden[i]!=' '; i++ )
	{
		j++;
	}

  for(unsigned int i = j;i < orden.size(); i++)
  {
    Letra l(orden[i]);
    palabra.push_back(l);
  }
  
  if(orden[0] >= 'A' && orden[0] <= 'O') // Establecemos si la palabra se posiciona en vertical u horizontal
  {
    orientacion = VERTICAL;
    
  }
  else
  {
    orientacion = HORIZONTAL;
  }
  puntuacion=0;

    string aux;
    int numletra;
    int un,dos,suma;


    if(orientacion == VERTICAL)
    {
      if((orden[0] >= 'A' && orden[0] <= 'Z') && (orden[1] >= 'A' && orden[1] <= 'Z')) // Comprobacion de que no se introducen 2 letras
      {
        origen.setFila(-1);
        origen.setColumna(-1);

      }
      else if(orden[0] < 'A' || orden[0] > 'O')
      {
    	origen.setFila(-1);
        origen.setColumna(-1);
      }
      else
      {
        numletra = orden[0] - 'A'; // Paso la posicion 0 a un numero
        origen.setColumna(numletra);

        if(j-1 == 2)
        {
  	un = orden[1] - 49;      // El 48 es para que si hay un 1 en el string no salga el numero 49 y salga el 1 como numero  y el 49 para pasarlo a matriz [0]
  	origen.setFila(un);
        }
        else
        {
  	un = orden[1];
  	dos = orden[2];
  	suma = un + dos;
  	suma = suma - 88;        // El 87 es para pasar al numero natural que corresponde y el 88 para para trabajar con la matriz[0]

  	if(suma > 15 || suma < 0)
  	{
  	  origen.setFila(-1);
  	}
  	else
  	{
  	  origen.setFila(suma);
  	}
        }
      }
    }
    else
    {
      if(j-1 == 2)
      {
        if(orden[1] < 'A' || orden[1] > 'O')
        {
  	origen.setFila(-1);
  	origen.setColumna(-1);
        }
        else if((orden[0] >= 'A' && orden[0] <= 'Z') && (orden[1] >= 'A' && orden[1] <= 'Z'))
        {
  	origen.setFila(-1);
  	origen.setColumna(-1);
        }
        else
        {
  	numletra = orden[1] - 'A';
  	origen.setColumna(numletra);
  	un = orden[0] - 49;      // El 48 es para que si hay un 1 en el string no salga el numero 49 y salga el 1 como numero
  	origen.setFila(un);
        }
      }
      else
      {
        if(orden[2] < 'A' || orden[2] > 'O')
        {
  	origen.setFila(-1);
  	origen.setColumna(-1);
        }
        else if((orden[2] >= 'A' && orden[2] <= 'Z') && (orden[1] >= 'A' && orden[1] <= 'Z'))
        {
  	origen.setFila(-1);
  	origen.setColumna(-1);
        }
        else
        {
  	numletra = orden[2] - 'A';
  	origen.setColumna(numletra);
  	un = orden[0];
  	dos = orden[1];
  	suma = un + dos;
  	suma = suma - 88;
  	if(suma > 15 || suma < 0)
  	{
  	  origen.setFila(-1);
  	}
  	else
  	{
  	  origen.setFila(suma);
  	}
        }
      }
    }
}

Coordenada Movimiento::getOrigen()const
{
  return(origen);
}

Orientacion Movimiento::getOrientacion()const
{
  return(orientacion);
}

int Movimiento::getPuntuacion()const
{
  return(puntuacion);
}

vector<Letra> Movimiento::getPalabra()const
{
  return(palabra);
}

string Movimiento::getPalabraString()const
{
  string aux;
  
  for(unsigned int i = 0; i < palabra.size(); i++)
  {
    aux += palabra[i].getSimbolo();
  }
  return(aux);
}

void Movimiento::setPuntuacion(int puntuacion)
{
  this -> puntuacion = puntuacion;
}

ostream& operator<<(ostream &os,const Movimiento &m)
{
  string guarda = "";
  string x,y,z,puntua,puntu;               // Coordenadas para pasarlas a string
  int aux;		                   // Auxiliar para convertir la coordenada de int a string
  
  
  if(m.getOrientacion() == VERTICAL)
  {
    if(m.getOrigen().getFila() >= 10)
    {
      x = m.getOrigen().getColumna() + 'A';             // Para la letra en vertical
      aux = m.getOrigen().getFila() / 10;
      z = aux + '0'; 		   	      // Para el primer numero
      y = (m.getOrigen().getFila() - (aux * 10)) + '1'; // Para el segundo numero
      
      if(m.getPuntuacion() >= 10)
      {
	aux = m.getPuntuacion() / 10;
	puntua = aux + '0';
	puntu = (m.getPuntuacion() - (aux * 10)) + '0';
	guarda += x + z + y + " " + m.getPalabraString() + " " + puntua + puntu;
	
      }
      else
      {
	puntua = m.getPuntuacion() + '0'; 
	guarda += x + z + y + " " + m.getPalabraString() + " " + puntua;
      }
    }
    else
    {
      x = m.getOrigen().getColumna() + 'A';      // Para la letra en vertical
      y = m.getOrigen().getFila() + '1';         // Para el numero en vertical
      
      if(m.getPuntuacion() >= 10)
      {
	aux = m.getPuntuacion() / 10;
	puntua = aux + '0';
	puntu = (m.getPuntuacion() - (aux * 10)) + '0';
	guarda += x + y + " " + m.getPalabraString() + " " + puntua + puntu;
	
      }
      else
      {
	puntua = m.getPuntuacion() + '0'; 
	guarda += x + y + " " + m.getPalabraString() + " " + puntua;
      }
    }
  }
  else
  {
    if(m.getOrigen().getFila() >= 10)
    {
      x = m.getOrigen().getColumna() + 'A';		  // Para la letra en horizontal
      aux = m.getOrigen().getFila() / 10;
      z = aux + '0'; 				  // Para el primer numero
      y = (m.getOrigen().getFila() - (aux * 10)) + '1'; 	  // Para el segundo numero
      
      if(m.getPuntuacion() >= 10)
      {
	aux = m.getPuntuacion() / 10;
	puntua = aux + '0';
	puntu = (m.getPuntuacion() - (aux * 10)) + '0';
	guarda += z + y + x + " " + m.getPalabraString() + " " + puntua + puntu;
	
      }
      else
      {
	puntua = m.getPuntuacion() + '0'; 
	guarda += z + y + x + " " + m.getPalabraString() + " " + puntua;
      }
      
    }
    else
    {
      x = m.getOrigen().getFila() + '1';      // Para la letra en horizontal
      y = m.getOrigen().getColumna() + 'A';   // Para el numero en horizontal
      
      if(m.getPuntuacion() >= 10)
      {
	aux = m.getPuntuacion() / 10;
	puntua = aux + '0';
	puntu = (m.getPuntuacion() - (aux * 10)) + '0';
	guarda += x + y + " " + m.getPalabraString() + " " + puntua + puntu;
	
      }
      else
      {
	puntua = m.getPuntuacion() + '0'; 
	guarda += x + y + " " + m.getPalabraString() + " " + puntua;
      }
    } 
  }
  os << guarda;
  return os;
}
