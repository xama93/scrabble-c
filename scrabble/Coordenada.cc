#include "Coordenada.h"
#include <stdlib.h>

// Declaracion de variable static
const Coordenada Coordenada::coordenadaError;

// Constructor
Coordenada::Coordenada(int fila, int columna)
{ 
	this->fila=fila; 
	this->columna=columna; 
}

// Constructor a partir de un string (equivalente a leerCoordenada)
Coordenada::Coordenada(string coord, Orientacion &orientacion)
{
	bool error=false;
	orientacion=HORIZONTAL;
	unsigned int len=coord.length();
	
	fila=columna=-1;
	
	if (len>=2)
	{
		if (coord[0]>='A' && coord[0]<='O')
		{
			orientacion=VERTICAL;
				
			string num;
			for (unsigned int i=1; i<len; i++)
				num+=coord[i];
		
			fila=atoi(num.c_str())-1;
			columna=coord[0]-'A';
		}
		else {
			orientacion=HORIZONTAL;
				
			if (coord[0]>='0' && coord[0]<='9')
			{
				string num;
				for (unsigned int i=0; i<len && coord[i]>='0' && coord[i]<='9'; i++)
					num+=coord[i];

				fila=atoi(num.c_str())-1;
				columna=coord[len-1]-'A';
			}
			else 
			{
				error=true;
			}
		}
	}
	else 
	{
		error=true;
	}

	if (fila<0 || fila>kFILAS-1 || columna<0 || columna>kCOLUMNAS-1)
	{
		error=true; 
	}
	
	if (error)
	{
		*this=coordenadaError;
	}
}

// Setter de fila
void Coordenada::setFila(int fila)
{ 
	if (fila>=0 && fila<kFILAS) 
		this->fila=fila;
	else 
		*this=coordenadaError; 
}

// Setter de columna
void Coordenada::setColumna(int col)
{
	if (col>=0 && col<kCOLUMNAS)
		columna=col;
	else
		*this=coordenadaError;
}

// Devuelve si la coordenada es erronea
bool Coordenada::isError() const
{ 
	return (fila==coordenadaError.fila || columna==coordenadaError.columna); 
}
