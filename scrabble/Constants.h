#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string.h>
#include <ctype.h>
#include <fstream>

using namespace std;

// Dimensiones del tablero
const int kFILAS=15;
const int kCOLUMNAS=15;

// Colores para el terminal. Ejemplo: cout << Azul << "Hola" << ResetColor;
const string Cyan="\e[46m";
const string Rosa="\e[45m\e[37m";
const string Azul="\e[44m\e[37m";
const string Rojo="\e[41m\e[37m";
const string ResetColor="\e[m";

// Array que indica la puntuación de cada una de las 26 letras, desde la A hasta la Z. Las letras con puntuacion=0
// no se usan porque no estan en la bolsa, por lo que no hay que hacer nada especial para este caso.
const int PUNTUACIONLETRAS[]={1,3,3,2,1,4,2,4,1,8,0,1,3,1,1,3,5,1,1,1,1,4,0,8,4,10}; 

// Array que indica la cantidad de letras que debe haber inicialmente en la bolsa (por ejemplo, 12 letras A pero solo una Z).
// Por tanto, la bolsa será un string que contiene "AAAAAAAAAAAABBCCCCC...".
const int NUMLETRAS[]={12,2,5,5,12,1,2,2,6,1,0,5,2,5,9,2,1,6,6,4,5,1,0,1,1,1}; // 97 piezas

// Array para imprimir un superindice por el terminal. Ejemplo para imprimir el numero 1: cout << SUPERINDEX[1];
const string SUPERINDEX[]={"\u2070","\u00B9","\u00B2","\u00B3","\u2074","\u2075","\u2076","\u2077","\u2078","\u2079"};

// Caracter para indicar que una casilla no tiene ninguna letra
const char CASILLAVACIA=' ';

// Tamaño de las palabras de diccionario
const int KPALA = 16;

// Numero maximo de letras en el rack
const int KRACK = 7;

// Maximo numero de letras 
const int KLETRAS = 26;

// Menu principal
const string RALLAS = "--------------------------------";
const string SCRABBLE = "---- Scrabble Programacion 2 ---";
const string NUEVA = "1- Nueva partida";
const string CARGA = "2- Cargar partida";
const string SAL = "q- Salir";
const string OPCI = "Opcion: ";
const string ERRO = "Error: Opcion incorrecta";

// ProcesarArgumentos
const string ERRONUMJUG = "Error: Numero de jugadores incorrecto";

// Comenzar partida
const string NUMJUG = "Numero de jugadores (1-4): ";

// Imprimir tablero
const string LETR = "   A B C D E F G H I J K L M N O ";
const string DOSESPACIO = "  ";
const string UNESPACIO = " ";

// Menu de ayuda
const string EJEM = "Ejemplo de movimiento: XY PALABRA";
const string OTRAS = "Otras opciones:";
const string OPCH = " h: Ayuda ";
const string OPCG = " g: Guardar partida";
const string OPCQ = " q: Salir de la partida";

// Jugar
const string LETJUG = "Letras jugador ";
const string PALAYUD = "Palabra (h para ayuda): ";
const string DOSPUNTOS = ": ";
const string ERRROR = "Error: Orden incorrecta";
const string PERRROR = "Error: Movimiento incorrecto";
const string TERMINA = "Final del juego";
const string ERRORAPERT = "Error: El fichero no se ha podido abrir";
const string NOMGUARDA = "Nombre de fichero:";
const string ERRODICCI = "Error: La palabra no esta en el diccionario";

// Colores para el terminal. Ejemplo: cout << AZUL << "Hola" << RESETCOLOR;
const string CYAN = "\e[46m";
const string ROSA = "\e[45m\e[37m";
const string AZUL = "\e[44m\e[37m";
const string ROJO = "\e[41m\e[37m";
const string RESETCOLOR = "\e[m";

#endif
