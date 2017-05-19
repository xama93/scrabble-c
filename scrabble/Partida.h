#ifndef _PARTIDA_H_
#define _PARTIDA_H_
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include "Constants.h" 
#include "Letra.h"
#include "Jugador.h"
#include "Tablero.h"
#include "Movimiento.h"


using namespace std;

class Partida
{
private:
  int turno;
  vector<Letra>bolsa;  // En constants tenemos su limite
  vector<Movimiento>movimientos;
  Letra letras[kFILAS][kCOLUMNAS];
  Tablero tablero;
  vector<Jugador>jugadores; 
  Movimiento leerMovimiento(string orden);
  Coordenada leerCoordenada(string coord,const Orientacion &orientacion); 
  string imprimirMovimiento(Movimiento m)const;
  void limpiarBuffer(); 
public:
  Partida(int numJugadores = 1);
  Partida(const Partida &p);
  void jugar();
  bool guardar(string nombreFichero)const;
  bool cargar(string nombreFichero);
  bool comprobarMovimiento(Movimiento &m, Rack &r);
  void guardarMovimiento(Movimiento m);
  bool palabraEnDiccionario(string palabra)const;
  void inicializarSemilla();
  vector<Letra>getBolsa()const;
  Letra getLetra(int fila, int columna)const;
  vector<Movimiento>getMovimientos()const;
  Jugador getJugador(int numJugador)const;
};

#endif