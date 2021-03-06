#include "Partida.h"
#include <iostream>

using namespace std;

Partida::Partida(int numJugadores)
{
  char letra;
  int i,j,k,l;
 
    
  inicializarSemilla();
  jugadores.resize(numJugadores);
  turno = 1;
  
  for(k = 0; k < numJugadores; k++)
  {
    jugadores[k].setPuntuacion(0);       // Inicializo las puntuaciones
  }

  for(j = 0; j < KLETRAS; j++)
  {
    
    letra = j + 'A';			// Paso el numero del vector de enteros a la letra correspondiente
  
    for(i = 0; i < NUMLETRAS[j]; i++)
    {
      bolsa.push_back(letra);
    }
  }
  
  for(i = 0 ;i < kFILAS; i++)		// Inicializar matriz de letras
  {
    for(j = 0 ;j < kCOLUMNAS; j++)
    {
      letras[i][j] = ' ';
    }
  }
  
  for(l = 0;l < numJugadores;l++)	// Inicializamos los racks
  {
    Rack r = jugadores[l].getRack();
    r.completar(bolsa);
    jugadores[l].setRack(r);

  }

  tablero.inicializar();
}

Partida::Partida(const Partida &p)
{
  this->turno = p.turno;
  this->bolsa = p.bolsa;
  this->movimientos = p.movimientos;
  for(int i = 0 ;i < kFILAS; i++)		// Inicializar matriz de letras
  {
    for(int j = 0 ;j < kCOLUMNAS; j++)
    {
      letras[i][j] = p.letras[i][j];
    }
  }
  this->jugadores = p.jugadores; 
}

void Partida::jugar()
{
  bool guardado;
  bool diccionario;
  bool terminada = false;
  bool perror;
  bool turn;
  unsigned int i;
  int control;
  string indexletra;
  string ordenes;
  string nomfich;
  Movimiento m;

  
  do
  {
    tablero.imprimir(letras);
  
    if(turno == 1)                             
    {
      indexletra = "";                              	   // Reiniciamos index para evitar mostrar rack ekivokado al cambiar de turno
      turn = false;                                	   // Comienza el turno y tiene k ser true para cambiar de turno en caso de jugadores > 1
      if(jugadores[turno-1].getRack().size() < 7)
      {
	Rack r = jugadores[turno-1].getRack();
	r.completar(bolsa);
	jugadores[turno-1].setRack(r);
      }
      cout << LETJUG << turno << DOSPUNTOS;
    
      //indexletra = indexletra + .getString());
       
      cout << jugadores[turno-1].getRack();
      cout << endl;
      cout << PALAYUD;
      
      do
      {
	getline(cin,ordenes); 
	if(ordenes == "h")
	{
	  cout << EJEM << endl;
	  cout << OTRAS << endl;
	  cout << OPCH << endl;
	  cout << OPCG << endl;
	  cout << OPCQ << endl;
	  tablero.imprimir(letras);
	  cout << LETJUG << turno << DOSPUNTOS;
	  cout << jugadores[turno-1].getRack();
	  cout << endl;
	  cout << PALAYUD;
	}
	else if(ordenes == "g")
	{
	  cout << NOMGUARDA;
	  getline(cin,nomfich);
	  guardado = guardar(nomfich);
	  if(guardado == false)
	  {
	    cout << ERRORAPERT <<endl;
	  }
	  tablero.imprimir(letras);
	  cout << LETJUG << turno << DOSPUNTOS;
	  cout << jugadores[turno-1].getRack();
	  cout << endl;
	  cout << PALAYUD;
	  
	}
	else if(ordenes != "q")
	{
	  m = leerMovimiento(ordenes);
	  
	  if(m.getOrigen().getFila() == -1)                // En caso de que las coordenadas esten mal 
	  {
	    cout << ERRROR << endl;              // Orden incorrecta
	    tablero.imprimir(letras);
	    cout << LETJUG << turno << DOSPUNTOS;
	    cout << jugadores[turno-1].getRack();
	    cout << endl;
	    cout << PALAYUD;
	  }
	  else
	  {
	    Rack r = jugadores[turno-1].getRack();
	    perror = comprobarMovimiento(m,r);
	    jugadores[turno-1].setRack(r);
	    diccionario = palabraEnDiccionario(m.getPalabraString());
	    if(perror == false)
	    {
	      cout << PERRROR << endl;         // Movimiento incorrecto
	      tablero.imprimir(letras);
	      cout << LETJUG << turno << DOSPUNTOS;
	      cout << jugadores[turno-1].getRack();
	      cout << endl;
	      cout << PALAYUD;
	    }
	    else if(diccionario == false)
	    {
	      cout << ERRODICCI << endl;		 // La palabra no esta en el diccionario
	      tablero.imprimir(letras);
	      cout << LETJUG << turno << DOSPUNTOS;
	      cout << jugadores[turno-1].getRack();
	      cout << endl;
	      cout << PALAYUD;
	    }
	    else
	    {     
	      guardarMovimiento(m);          // Situa por ultimo las letras en el tablero
	      if(jugadores.size() > 1)
	      {
		Rack r = jugadores[turno-1].getRack(); 
		r.completar(bolsa);
		jugadores[turno-1].setRack(r);    
		turno++;
		control = 0;                   // Control nos ayuda a mirar si el rack esta vacio para terminar la partida correctamente
		turn = true;
		
	      }
	      else
	      {
		Rack r = jugadores[turno-1].getRack(); // sera getrack  de jugador
		r.completar(bolsa);
		jugadores[turno-1].setRack(r);    //sera setrack() de jugador
		turn = true;
		control = 0;
	      }
	    }
	  }
	}
	else
	{
	  // No hagas nada si no es coodenada, ni ayuda(h)...sirve para salir en caso de q 
	}
      }while((ordenes == "h" || ordenes != "q") && turn == false);
      
    }
    else if(turno == 2)
    { 
      turn = false; 
      indexletra = "";                                   // Reiniciamos para el nuevo turno indexletra
      if(jugadores[turno-1].getRack().size() < KRACK)
      {
	Rack r = jugadores[turno-1].getRack(); 
	r.completar(bolsa);
	jugadores[turno-1].setRack(r);
      }      
      cout << LETJUG << turno << DOSPUNTOS;
     
      //indexletra = indexletra + getString();
      
      cout << jugadores[turno-1].getRack();
      cout << endl;
      cout << PALAYUD;
      
      do
      {
	getline(cin,ordenes); 
	if(ordenes == "h")
	{
	  cout << EJEM << endl;
	  cout << OTRAS << endl;
	  cout << OPCH << endl;
	  cout << OPCG << endl;
	  cout << OPCQ << endl;
	  tablero.imprimir(letras);
	  cout << LETJUG << turno << DOSPUNTOS;
	  cout << jugadores[turno-1].getRack();
	  cout << endl;
	  cout << PALAYUD;
	}
	else if(ordenes == "g")
	{
	  cout << NOMGUARDA;
	  getline(cin,nomfich);
	  guardado = guardar(nomfich);
	  if(guardado == false)
	  {
	    cout << ERRORAPERT <<endl;
	  }
	  tablero.imprimir(letras);
	  cout << LETJUG << turno << DOSPUNTOS;
	  cout << jugadores[turno-1].getRack();
	  cout << endl;
	  cout << PALAYUD;
	
	}
	else if(ordenes != "q")
	{
	  m = leerMovimiento(ordenes);
	  
	  if(m.getOrigen().getFila() == -1)                // En caso de que las coordenadas esten mal 
	  {
	    cout << ERRROR << endl;              // Orden incorrecta
	    tablero.imprimir(letras);
	    cout << LETJUG << turno << DOSPUNTOS;
	    cout << jugadores[turno-1].getRack();
	    cout << endl;
	    cout << PALAYUD;
	  }
	  else
	  {
	    Rack r = jugadores[turno-1].getRack();
	    perror = comprobarMovimiento(m,r);
	    jugadores[turno-1].setRack(r);
	    diccionario = palabraEnDiccionario(m.getPalabraString());
	    
	    if(perror == false)
	    {
	      cout << PERRROR << endl;         // Movimiento incorrecto
	      tablero.imprimir(letras);
	      cout << LETJUG << turno << DOSPUNTOS;
	      cout << jugadores[turno-1].getRack();
	      cout << endl;
	      cout << PALAYUD;
	    }
	    else if(diccionario == false)
	    {
	      cout << ERRODICCI << endl;		 // Diccionario error
	      tablero.imprimir(letras);
	      cout << LETJUG << turno << DOSPUNTOS;
	      cout << jugadores[turno-1].getRack();
	      cout << endl;
	      cout << PALAYUD;
	    }
	    else
	    {
	      guardarMovimiento(m);          // Situa por ultimo las letras en el tablero
	      if(jugadores.size() == 2)
	      {
		Rack r = jugadores[turno-1].getRack(); 
		r.completar(bolsa);
		jugadores[turno-1].setRack(r);
		turno = 1;
		control = 1;
		turn = true;
	      }
	      else
	      {
		Rack r = jugadores[turno-1].getRack();
		r.completar(bolsa);
		jugadores[turno-1].setRack(r);
		turno++;
		control = 1;
		turn = true;
	      }
	    }
	  }
	}
	else
	{
	  // No hagas nada si no es coodenada, ni ayuda(h)...sirve para salir en caso de q 
	}
      }while((ordenes == "h" || ordenes != "q") && turn == false);
    }
    else if(turno == 3)
    { 
      turn = false; 
      indexletra = "";                                   // Reiniciamos para el nuevo turno indexletra
      if(jugadores[turno-1].getRack().size() < KRACK)
      {
	Rack r = jugadores[turno-1].getRack();
	r.completar(bolsa);
	jugadores[turno-1].setRack(r); 
      }      
      cout << LETJUG << turno << DOSPUNTOS;
    
      //indexletra = indexletra + getString();
      
      cout << jugadores[turno-1].getRack();
      cout << endl;
      cout << PALAYUD;
      
      do
      {
	getline(cin,ordenes); 
	if(ordenes == "h")
	{
	  cout << EJEM << endl;
	  cout << OTRAS << endl;
	  cout << OPCH << endl;
	  cout << OPCG << endl;
	  cout << OPCQ << endl;
	  tablero.imprimir(letras);
	  cout << LETJUG << turno << DOSPUNTOS;
	  cout << jugadores[turno-1].getRack();
	  cout << endl;
	  cout << PALAYUD;
	}
	else if(ordenes == "g")
	{
	  cout << NOMGUARDA;
	  getline(cin,nomfich);
	  guardado = guardar(nomfich);
	  if(guardado == false)
	  {
	    cout << ERRORAPERT <<endl;
	  }
	  tablero.imprimir(letras);
	  cout << LETJUG << turno << DOSPUNTOS;
	  cout << jugadores[turno-1].getRack();
	  cout << endl;
	  cout << PALAYUD;
	  
	}
	else if(ordenes != "q")
	{
	  m = leerMovimiento(ordenes);
	  
	  if(m.getOrigen().getFila() == -1)                // En caso de que las coordenadas esten mal 
	  {
	    cout << ERRROR << endl;              // Orden incorrecta
	    tablero.imprimir(letras);
	    cout << LETJUG << turno << DOSPUNTOS;
	    cout << jugadores[turno-1].getRack();
	    cout << endl;
	    cout << PALAYUD;
	  }
	  else
	  {
	    Rack r = jugadores[turno-1].getRack();
	    perror = comprobarMovimiento(m,r);
	    jugadores[turno-1].setRack(r);
	    diccionario = palabraEnDiccionario(m.getPalabraString());

	    if(perror == false)
	    {
	      cout << PERRROR << endl;         // Movimiento incorrecto
	      tablero.imprimir(letras);
	      cout << LETJUG << turno << DOSPUNTOS;
	      cout << jugadores[turno-1].getRack();
	      cout << endl;
	      cout << PALAYUD;
	    }
	    else if(diccionario == false)
	    {
	      cout << ERRODICCI << endl;		 // Diccionario error
	      tablero.imprimir(letras);
	      cout << LETJUG << turno << DOSPUNTOS;
	      cout << jugadores[turno-1].getRack();
	      cout << endl;
	      cout << PALAYUD;
	    }
	    else
	    {
	      guardarMovimiento(m);          // Situa por ultimo las letras en el tablero
	      if(jugadores.size() == 3)
	      {
		Rack r = jugadores[turno-1].getRack();
		r.completar(bolsa);
		jugadores[turno-1].setRack(r);
		turno = 1;
		control = 2;
		turn = true;
	      }
	      else
	      {
		Rack r = jugadores[turno-1].getRack();
		r.completar(bolsa);
		jugadores[turno-1].setRack(r);
		turno++;
		control = 2;
		turn = true;
	      }
	    }
	  }
	}
	else
	{
	  // No hagas nada si no es coodenada ,ni ayuda(h)...sirve para salir en caso de q 
	}
      }while((ordenes == "h" || ordenes != "q") && turn == false);
      
    }
    else
    {
      turn = false; 
      indexletra = "";                                   // Reiniciamos para el nuevo turno indexletra
      if(jugadores[turno-1].getRack().size() < KRACK)
      {
	Rack r = jugadores[turno-1].getRack();
	r.completar(bolsa);
	jugadores[turno-1].setRack(r);
      }      
      cout << LETJUG << turno << DOSPUNTOS;
    
      //indexletra = indexletra + getString()
     
      cout << jugadores[turno-1].getRack();
      cout << endl;
      cout << PALAYUD;
      
      do
      {
	getline(cin,ordenes); 
	if(ordenes == "h")
	{
	  cout << EJEM << endl;
	  cout << OTRAS << endl;
	  cout << OPCH << endl;
	  cout << OPCG << endl;
	  cout << OPCQ << endl;
	  tablero.imprimir(letras);
	  cout << LETJUG << turno << DOSPUNTOS;
	  cout << jugadores[turno-1].getRack();
	  cout << endl;
	  cout << PALAYUD;
	}
	else if(ordenes == "g")
	{
	  cout << NOMGUARDA;
	  getline(cin,nomfich);
	  guardado = guardar(nomfich);
	  if(guardado == false)
	  {
	    cout << ERRORAPERT <<endl;
	  }
	  tablero.imprimir(letras);
	  cout << LETJUG << turno << DOSPUNTOS;
	  cout << jugadores[turno-1].getRack();
	  cout << endl;
	  cout << PALAYUD;
	  
	}
	else if(ordenes != "q")
	{
	  m = leerMovimiento(ordenes);
	  
	  if(m.getOrigen().getFila() == -1)                // En caso de que las coordenadas esten mal 
	  {
	    cout << ERRROR << endl;              // Orden incorrecta
	    tablero.imprimir(letras);
	    cout << LETJUG << turno << DOSPUNTOS;
	    cout << jugadores[turno-1].getRack();
	    cout << endl;
	    cout << PALAYUD;
	  
	  }
	  else
	  {
	    Rack r = jugadores[turno-1].getRack();
	    perror = comprobarMovimiento(m,r);
	    jugadores[turno-1].setRack(r);
	    diccionario = palabraEnDiccionario(m.getPalabraString());

	    if(perror == false)
	    {
	      cout << PERRROR << endl;         // Movimiento incorrecto
	      tablero.imprimir(letras);
	      cout << LETJUG << turno << DOSPUNTOS;
	      cout << jugadores[turno-1].getRack();
	      cout << endl;
	      cout << PALAYUD;
	    }
	    else if(diccionario == false)
	    {
	      cout << ERRODICCI << endl;		 // Diccionario error
	      tablero.imprimir(letras);
	      cout << LETJUG << turno << DOSPUNTOS;
	      cout << jugadores[turno-1].getRack();
	      cout << endl;
	      cout << PALAYUD;
	    }
	    else
	    {
	      Rack r = jugadores[turno-1].getRack(); 
	      r.completar(bolsa);
	      jugadores[turno-1].setRack(r);
	      guardarMovimiento(m);          // Situa por ultimo las letras en el tablero
	      turno = 1;
	      control = 3;
	      turn = true;
	    }
	  }
	}
	else
	{
	  // No hagas nada si no es coodenada ,ni ayuda(h)...sirve para salir en caso de q 
	}
      }while((ordenes == "h" || ordenes != "q") && turn == false);
    }
    if(bolsa.size() == 0 && jugadores[control].getRack().size() == 0)  
    {
      terminada = true;    
      cout << TERMINA <<endl;
    }
    if(ordenes != "h" && ordenes != "q")      // Muestra las puntuaciones
    { 
      for(i = 0; i < jugadores.size(); i++)
      {
	cout << "Puntuacion jugador " << i + 1 << "= " << jugadores[i].getPuntuacion() << endl;
      }
    }
  }while(terminada == false && ordenes != "q");
}

Movimiento Partida::leerMovimiento(string orden)
{
  Coordenada cor;
  Movimiento aux(orden);
  string coor;
  string pala;
  bool auxbool = true;
  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int k = 0;
  

  for(i = 0;i < orden.size(); i++)
  {
    if(orden[i] == ' ')
    {
      i = orden.size();   	          // Sal del bucle si encuentra un espacio
      
    }
    else
    {
      coor = coor + orden[i];
    }
    j++;               		          // Este contador nos permitira almacenar la palabra posterior al espacio de orden
  }
 
  
  for(i = 0; i < orden.size(); i++)      // Almacenamos la palabra en un string auxiliar
  {
    if(i == 0)
    {
      i = j - 1;           		 // Evita un bucle infinito con el for y nos estacionamos despues del espacio
    }
    else
    {
      pala = pala + orden[i];
    }
  }
  for(i = 0; i < pala.size(); i++)       // Convertimos en caso de no estarlo el string a mayus con libreria ctype.h y toupper
  {
    pala[i] = toupper(pala[i]);	   
  }
  
  cor = leerCoordenada(coor,aux.getOrientacion());
  if(cor.getFila() == -1)
  {
    auxbool = false;
  }
  
  for(i = 0; i < pala.size(); i++)
  {
    Letra l;
    l.setSimbolo(pala[i]);
  }
  
  if(auxbool == true)                  // Comprobacion de que no se sale de la matriz
  {
    if(aux.getOrientacion() == VERTICAL)
    {
      for(i = aux.getOrigen().getFila(); i < 15 ; i++)
      {
	k++;
      }
      if(pala.size() > k)
      {
    Movimiento error;
    aux = error;

	for(i = 0; i < pala.size(); i++)
	{
	  Letra l;
	  l.setSimbolo(pala[i]);
	}
	//aux.palabra = pala;WARNING
      } 
    }
    else if(aux.getOrientacion() == HORIZONTAL)
    {
      for(i = aux.getOrigen().getColumna(); i < 15 ; i++)
      {
	k++;
      }
      if(pala.size() > k)
      {
    	  Movimiento error;
    	  aux = error;
	for(i = 0; i < pala.size(); i++)
	{
	  Letra l;
	  l.setSimbolo(pala[i]);
	}
	//aux.palabra = pala;
      }
    }
  }
  return(aux);
}

Coordenada Partida::leerCoordenada(string coord,const Orientacion &orientacion)              
{
  Coordenada a;
  string aux;
  int numletra;
  int un,dos,suma;
  
  
  if(orientacion == VERTICAL)
  {
    if((coord[0] >= 'A' && coord[0] <= 'Z') && (coord[1] >= 'A' && coord[1] <= 'Z')) // Comprobacion de que no se introducen 2 letras
    {
      a.setFila(-1);
      a.setColumna(-1);
    
    }
    else if(coord[0] < 'A' || coord[0] > 'O')
    {
      a.setFila(-1);
      a.setColumna(-1);
    }
    else
    {
      numletra = coord[0] - 'A'; // Paso la posicion 0 a un numero
      a.setColumna(numletra);
      
      if(coord.size() == 2)
      {
	un = coord[1] - 49;      // El 48 es para que si hay un 1 en el string no salga el numero 49 y salga el 1 como numero  y el 49 para pasarlo a matriz [0]         
	a.setFila(un);
      }
      else
      {
	un = coord[1];
	dos = coord[2];
	suma = un + dos;
	suma = suma - 88;        // El 87 es para pasar al numero natural que corresponde y el 88 para para trabajar con la matriz[0]
	
	if(suma > 15 || suma < 0)
	{
	  a.setFila(-1);
	}
	else
	{
	  a.setFila(suma);      
	}
      }
    }
  }
  else
  {
    if(coord.size() == 2)
    {
      if(coord[1] < 'A' || coord[1] > 'O')
      {
	a.setFila(-1);
	a.setColumna(-1);
      }
      else if((coord[0] >= 'A' && coord[0] <= 'Z') && (coord[1] >= 'A' && coord[1] <= 'Z'))
      {
	a.setFila(-1);
	a.setColumna(-1);
      }
      else
      {
	numletra = coord[1] - 'A';
	a.setColumna(numletra);
	un = coord[0] - 49;      // El 48 es para que si hay un 1 en el string no salga el numero 49 y salga el 1 como numero
	a.setFila(un);
      }
    }
    else
    {
      if(coord[2] < 'A' || coord[2] > 'O')
      {
	a.setFila(-1);
	a.setColumna(-1);
      }
      else if((coord[2] >= 'A' && coord[2] <= 'Z') && (coord[1] >= 'A' && coord[1] <= 'Z'))
      {
	a.setFila(-1);
	a.setColumna(-1);
      }
      else
      {
	numletra = coord[2] - 'A';
	a.setColumna(numletra);
	un = coord[0];
	dos = coord[1];
	suma = un + dos;
	suma = suma - 88;
	if(suma > 15 || suma < 0)
	{
	  a.setFila(-1);
	}
	else
	{
	  a.setFila(suma);
	}
      }
    }
  }
  return(a); 
}


bool Partida::guardar(string nombreFichero)const
{
  ofstream  fich_guardar;
  bool completado;
  string mov;
  
    fich_guardar.open(nombreFichero.c_str(),ios::out);  // Abrimos el fichero para su escritura
    if(fich_guardar.is_open())
    {
      fich_guardar << jugadores.size() << endl;		 // Almacenamos el numero de jugadores
      
      for(unsigned int i = 0; i < jugadores.size(); i++)		 // Almacenamos el rack de cada uno de los jugadores
      {
	fich_guardar << jugadores[i].getRack().getString() << endl;
      }
      
      for(unsigned int l = 0;l < bolsa.size(); l++)
      {
	fich_guardar << bolsa[l].getSimbolo();	 // Almacenamos la bolsa
      }
      
      fich_guardar << endl; //WARNING mirar si se guarda bien 
      
      for(unsigned int j = 0; j < movimientos.size(); j++)	 // Almacenamos el string de imprimirMovimiento
      {
	mov = imprimirMovimiento(movimientos[j]);
	fich_guardar << mov << endl;
      }
      
      
      fich_guardar.close();				 // Cerramos el fichero
      
      completado = true;
      
    }
    else
    {
      completado = false;
    }
  
  return(completado);
}

bool Partida::cargar(string nombreFichero)
{
  ifstream fich_cargar;
  Movimiento mvi;
  bool cargado = false;
  int tamfich = 0;
  unsigned int i = 0;
  int j = 0;
  int k = 0;
  int m = 0;
  string vec[100];
  string bolsaletras;
  string mov;
  string coor;
  string pala;
  
  
  fich_cargar.open(nombreFichero.c_str(),ios::in); // Abrimos el fichero para su lectura
  
  if(fich_cargar.is_open())
  {
    while(!fich_cargar.eof())			 // Guarda toda la informacion del fichero en un vector de string
    {
      getline(fich_cargar,vec[i]);
      i++;
      tamfich++; 
    }
    fich_cargar.close();			 // Cerramos el fichero
    
    turno = 1; 				 // Inicializamos turno
    jugadores.resize(atoi(vec[0].c_str()));		 // Redimensionamos el vector de jugadores
    for(int l = 0 ;l < kFILAS; l++)		 // Inicializar matriz de letras (luego hay que poner las del fichero)
    {
      for(int n = 0 ;n < kCOLUMNAS; n++)
      {
	letras[l][n].setSimbolo(' ');
      }
    }
    for(i = 0; i < jugadores.size(); i++)       	 // Inicializamos racks de cada uno de los jugadores
    {
      Rack r;
      vector<Letra>rackss(vec[i+1].size());
      
      for(unsigned int j=0;j<vec[i+1].size();j++)
      {
	rackss[j]=vec[i+1][j];
      }
      r.completar(rackss);
      jugadores[i].setRack(r);
      k++;
    }
    bolsaletras = vec[k + 1];			// Guardamos la bolsa en un string auxiliar
    for(unsigned int l = 0; l < bolsaletras.size(); l++)
    {
      bolsa.push_back(bolsaletras[l]);	// Inicializamos la bolsa de letras
    }
    k = k + 2;					 // Posicionamos en vector
    for(j = k; j < tamfich - 1; j++)		 // Coordenadas y palabras
    {
      mov = vec[j];			 // Guardo las ordenes de 1 en 1
     
      for(unsigned int l = 0; l < mov.size(); l++)	 // Separo primero la coordenada
      {
	if(mov[l] == ' ')
	{
	  l = mov.size();   	          
	}
	else
	{
	  coor = coor + mov[l];
	}
	m++;
      }
      
      for(unsigned int l = m; l < mov.size(); l++)	 // Separo por ultimo la palabra de la puntuacion
      {
	if(mov[l] == ' ')
	{
	  l = mov.size();   	          
	  mov = ""; 
	}
	else
	{
	  pala = pala + mov[l];
	}
      }
      
      mov += coor + " " + pala;
      mvi = leerMovimiento(mov);
      guardarMovimiento(mvi);
      mov = "";					 // Reinicio los contadores para la coordenada/palabra
      coor = "";
      pala = "";
      m = 0;
      
      turno++;
      
      if(turno > (signed)jugadores.size())
      {
	turno = 1;
      }
    }
    
    cargado = true;
    
  }
  else
  {
    cargado = false;
  }
  return(cargado);
}

bool Partida::comprobarMovimiento(Movimiento &m, Rack &r)
{
  bool mov = true;
  bool encon = false;
  bool dic = true;
  unsigned int i = 0;
  int j = 0;
  unsigned int trampas = 0;
  unsigned int k = 0;
  Rack auxrack = r;
  string aux = "";

  for(j = 0; j < (signed)m.getPalabra().size();j++)
  {
	  aux += m.getPalabra()[j].getSimbolo();
  }
  
  for(i = 0; i < aux.size() && mov; i++)                                   // Comprobamos que las letras del rack son las mismas que la orden con un rack copia
  {
    for(j = 0; j < (signed)auxrack.getString().size() && mov; j++)
    {
      if(aux[i] == auxrack.getString()[j])
      {
	if(m.getOrientacion() == HORIZONTAL && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
	{
	  mov = auxrack.sacarLetra(aux[i]);
	  encon = true;
	  k++;
	}
	else if(m.getOrientacion() == VERTICAL && letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == ' ')
	{
	  mov = auxrack.sacarLetra(aux[i]);
	  encon = true;
	  k++;
	}
	j = (signed)auxrack.getString().size();
      }
    }
    
    if(m.getOrientacion() == HORIZONTAL && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == aux[i]  && encon == false && mov)
    {
      k++;  
      trampas++;
    }
    else if(m.getOrientacion() == VERTICAL && letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == aux[i]  && encon == false && mov)
    {
      k++;
      trampas++;
    }
    encon = false; 
  }
 
  if(k != aux.size())                                                // En caso de tener diferente extension las palabras
  {
    mov = false;
  }
  else if(trampas == aux.size())
  {
    mov = false;
  }
  else if(m.getOrigen().getFila() == 7 && m.getOrientacion() == HORIZONTAL && letras[7][7].getSimbolo() == ' ' && (m.getOrigen().getColumna() >= 1 && m.getOrigen().getColumna() <= 7 )) // Comprobar que empieza la partida tiene una letra en la casilla H8
  {
    if(m.getOrigen().getFila() == 1 && aux.size() == 7)
    {
      mov = true;
    }
    else if(m.getOrigen().getColumna() == 2 && aux.size() >= 6)
    {
      mov = true;
    }
    else if(m.getOrigen().getColumna() == 3 && aux.size() >= 5)
    {
      mov = true;
    }
    else if(m.getOrigen().getColumna() == 4 && aux.size() >= 4)
    {
      mov = true;
    }
    else if(m.getOrigen().getColumna() == 5 && aux.size() >= 3)
    {
      mov = true;
    }
    else if(m.getOrigen().getColumna() == 6 && aux.size() >= 2)
    {
      mov = true;
    }
    else if(m.getOrigen().getColumna() == 7 && aux.size() >= 1)
    {
      mov = true;
    }
    else
    {
      mov = false;
    }
  }
  else if(m.getOrigen().getColumna() == 7 && m.getOrientacion() == VERTICAL && letras[7][7].getSimbolo() == ' ' && (m.getOrigen().getFila() >= 1 && m.getOrigen().getFila() <= 7 ))      // Comprobar que empieza la partida tiene una letra en la casilla H8
  {
    if(m.getOrigen().getFila() == 1 && aux.size() == 7)
    {
      mov = true;
    }
    else if(m.getOrigen().getFila() == 2 && aux.size() >= 6)
    {
      mov = true;
    }
    else if(m.getOrigen().getFila() == 3 && aux.size() >= 5)
    {
      mov = true;
    }
    else if(m.getOrigen().getFila() == 4 && aux.size() >= 4)
    {
      mov = true;
    }
    else if(m.getOrigen().getFila() == 5 && aux.size() >= 3)
    {
      mov = true;
    }
    else if(m.getOrigen().getFila() == 6 && aux.size() >= 2)
    {
      mov = true;
    }
    else if(m.getOrigen().getFila() == 7 && aux.size() >= 1)
    {
      mov = true;
    }
    else
    {
      mov = false;
    }
  }
  else if(letras[7][7].getSimbolo() != ' ')                                    // Comprobar que se concatenan las palabras de todas las formas posibles X es la letra en comun y O son las añadidas
  {
    if(letras[m.getOrigen().getFila()][m.getOrigen().getColumna()].getSimbolo() == aux[0])   		         // XOO y en horizontal hacia arrriba
    {
      mov = true; 
      
    }
    else if(m.getOrientacion() == HORIZONTAL && (letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + aux.size() - 1].getSimbolo() == aux[aux.size() - 1])) // OOX en horizontal
    {
      mov = true;
      
    }
    else if(m.getOrientacion() == VERTICAL && (letras[m.getOrigen().getFila() + aux.size() - 1][m.getOrigen().getColumna()].getSimbolo() == aux[aux.size() - 1]))   // OOX en vertical
    {
      mov = true;
      
    }
    else if(letras[m.getOrigen().getFila()][m.getOrigen().getColumna()].getSimbolo() == ' ') 			// OXO / OOOXO / OXOOO...
    {
      if(m.getOrientacion() == HORIZONTAL)
      {
	for(i = 0; i < aux.size(); i++)
	{
	  if(letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == aux[i])
	  {
	    mov = true;
	    i = aux.size();
	  }
	  else
	  {
	    mov = false;
	  }
	}
      }
      else
      {
	for(i = 0; i < aux.size(); i++)
	{
	  if(letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == aux[i])
	  {
	    mov = true;
	    i = aux.size();
	  }
	  else
	  {
	    mov = false;
	  }
	}
      }
    }
    else
    {
      mov = false;
    }
  }
  else
  {
    mov = false;
  }
  if(palabraEnDiccionario(aux) == false)
  {
    dic = false;
  }
  if(mov == true && dic == true)	// Saca las letras del rack original
  {
    for(i = 0; i < aux.size(); i++)
    {
      if(m.getOrientacion() == HORIZONTAL && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
      {
	mov = r.sacarLetra(aux[i]);
	  
      }
      else if(m.getOrientacion() == VERTICAL && letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == ' ')
      {
	mov = r.sacarLetra(aux[i]);
      }
      if(mov == false)
      {
	i = aux.size();
      }
    }
  }
  return(mov);
}

bool Partida::palabraEnDiccionario(string palabra)const
{
  bool encontrada = false;
  ifstream diccionario;
  char cad[16];
  unsigned int k = 0;
  long int sup = 0;
  long int inf = 0;
  long int centro = 0;
  string pala = "";
  
  
  diccionario.open("diccionario-p2.dat",ios::in|ios::binary);
 
  if(diccionario.is_open())
  { 
    diccionario.seekg(0,ios::end);	 // Colocamos el puntero en el final del fichero
    sup = diccionario.tellg() / KPALA;	 // Medimos el tamaño del fichero, lo dividimos entre 16 pala que nos de el maximo de palabras 
    sup = sup - 1; 			 // y le quito 1 para situarnos al principio del ultimo registro y no al final

    centro = (sup - inf) / 2;	       	// División entera: se trunca la fracción
    
    while(inf <= sup)
    {
      
      diccionario.seekg(centro * 16,ios::beg);	// Posicionamos 
      diccionario.read(cad,sizeof(cad));	// Leemos 
      for(int i = 0; i < KPALA; i++)		// convertimos en un string 
      {
	pala += cad[i];
	cad[i]  = ' ';
      }
 
      for(unsigned int j = 0; j < palabra.size(); j++)   // comparamos con su tamaño real porque el string almacena la supuesta palabra correcta y letras de más
      {
	if(pala[j] == palabra[j])
	{
	  k++;
	}
      }
      if(k == palabra.size())
      {
	encontrada = true;
	inf = sup + 1;				// Sal del while
      }
      else if(palabra < pala)
      {
	k = 0;
	sup = centro - 1;
	centro = inf + ((sup - inf) / 2);

      }
      else
      {
	k = 0;
	inf = centro + 1;
	centro = inf + ((sup - inf) / 2);
      }
      pala = ""; 
    }
    diccionario.close();			// Cerramos el diccionario
  }
  else
  {
    encontrada = false;
  }
  return(encontrada);
}

void Partida::guardarMovimiento(Movimiento m)                                                
{
  unsigned int i,puntua;
  int doblepa = false;
  int tripa = false;
  
 
  m.setPuntuacion(0);				// Inicializo la puntuacion de la palabra
  
  if(m.getOrientacion() == HORIZONTAL)
  {
    for(i = 0;i < m.getPalabra().size(); i++)
    {
      puntua = m.getPalabraString()[i] - 'A';					// Pasar la letra l a un numero
      
      if(PUNTUACIONLETRAS[puntua] == 0)
      {
	m.setPuntuacion(m.getPuntuacion() + 0);
    
      }
      else if(PUNTUACIONLETRAS[puntua] == 1)
      {
	if(tablero.getCasilla(m.getOrigen().getFila(),m.getOrigen().getColumna() + i) == DOBLELETRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 2);
	  
	}
	else if(tablero.getCasilla(m.getOrigen().getFila(),m.getOrigen().getColumna() + i) == TRIPLELETRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 3);
	  
	}
	else
	{
	  m.setPuntuacion(m.getPuntuacion() + 1);
	}
      }
      else if(PUNTUACIONLETRAS[puntua] == 2)
      {
	if(tablero.getCasilla(m.getOrigen().getFila(),m.getOrigen().getColumna() + i) == DOBLELETRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 4);
	  
	}
	else if(tablero.getCasilla(m.getOrigen().getFila(),m.getOrigen().getColumna() + i) == TRIPLELETRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 6);
	  
	}
	else
	{
	  m.setPuntuacion(m.getPuntuacion() + 2);
	}
      }
      else if(PUNTUACIONLETRAS[puntua] == 3)
      {
	if(tablero.getCasilla(m.getOrigen().getFila(),m.getOrigen().getColumna() + i) == DOBLELETRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 6);
	  
	}
	else if(tablero.getCasilla(m.getOrigen().getFila(),m.getOrigen().getColumna() + i) == TRIPLELETRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 9);
	  
	}
	else
	{
	  m.setPuntuacion(m.getPuntuacion() + 3);
	}
      }
      else if(PUNTUACIONLETRAS[puntua] == 4)
      {
	if(tablero.getCasilla(m.getOrigen().getFila(),m.getOrigen().getColumna() + i) == DOBLELETRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 8);
	  
	}
	else if(tablero.getCasilla(m.getOrigen().getFila(),m.getOrigen().getColumna() + i) == TRIPLELETRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 12);
	  
	}
	else
	{
	  m.setPuntuacion(m.getPuntuacion() + 4);
	}
      }
      else if(PUNTUACIONLETRAS[puntua] == 5)
      {
	if(tablero.getCasilla(m.getOrigen().getFila(),m.getOrigen().getColumna() + i) == DOBLELETRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 10);
	  
	}
	else if(tablero.getCasilla(m.getOrigen().getFila(),m.getOrigen().getColumna() + i) == TRIPLELETRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 15);
	  
	}
	else
	{
	  m.setPuntuacion(m.getPuntuacion() + 5);
	}
      }
      else if(PUNTUACIONLETRAS[puntua] == 8)
      {
	if(tablero.getCasilla(m.getOrigen().getFila(),m.getOrigen().getColumna() + i) == DOBLELETRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 16);
	  
	}
	else if(tablero.getCasilla(m.getOrigen().getFila(),m.getOrigen().getColumna() + i) == TRIPLELETRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 24);
	  
	}
	else
	{
	  m.setPuntuacion(m.getPuntuacion() + 8);
	}
      }
      else 
      {
	if(tablero.getCasilla(m.getOrigen().getFila(),m.getOrigen().getColumna() + i) == DOBLELETRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 20);
	  
	}
	else if(tablero.getCasilla(m.getOrigen().getFila(),m.getOrigen().getColumna() + i) == TRIPLELETRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 30);
	  
	}
	else
	{
	  m.setPuntuacion(m.getPuntuacion() + 10);
	}
      }
      if(tablero.getCasilla(m.getOrigen().getFila(),m.getOrigen().getColumna() + i) == DOBLEPALABRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
      {
	doblepa ++;
      }
      if(tablero.getCasilla(m.getOrigen().getFila(),m.getOrigen().getColumna() + i) == TRIPLEPALABRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
      {
	tripa ++;
      } 
      letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].setSimbolo(m.getPalabraString()[i]);          // Anyado por ultimo las palabras en el tablero
    }
    if(doblepa > 0)
    {
      m.setPuntuacion(m.getPuntuacion() * 2 * doblepa);
      jugadores[turno-1].setPuntuacion(jugadores[turno-1].getPuntuacion() + m.getPuntuacion());
      
    }
    else if(tripa > 0)
    {
      m.setPuntuacion(m.getPuntuacion() * 3 * tripa);
      jugadores[turno-1].setPuntuacion(jugadores[turno-1].getPuntuacion() + m.getPuntuacion());
      
    }
    else
    {
      jugadores[turno-1].setPuntuacion(jugadores[turno-1].getPuntuacion() + m.getPuntuacion());
    }
  }
  else
  {
    for(i = 0;i < m.getPalabra().size(); i++)
    {
      puntua = m.getPalabraString()[i] - 'A';					// Pasar la letra l a un numero
      
      if(PUNTUACIONLETRAS[puntua] == 0)
      {
	m.setPuntuacion(m.getPuntuacion() + 0);
    
      }
      else if(PUNTUACIONLETRAS[puntua] == 1)
      {
	if(tablero.getCasilla(m.getOrigen().getFila() + i,m.getOrigen().getColumna()) == DOBLELETRA && letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 2);
	  
	}
	else if(tablero.getCasilla(m.getOrigen().getFila() + i,m.getOrigen().getColumna()) == TRIPLELETRA && letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 3);
	  
	}
	else
	{
	  m.setPuntuacion(m.getPuntuacion() + 1);
	}
      }
      else if(PUNTUACIONLETRAS[puntua] == 2)
      {
	if(tablero.getCasilla(m.getOrigen().getFila() + i,m.getOrigen().getColumna()) == DOBLELETRA && letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 4);
	  
	}
	else if(tablero.getCasilla(m.getOrigen().getFila() + i,m.getOrigen().getColumna()) == TRIPLELETRA && letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 6);
	  
	}
	else
	{
	  m.setPuntuacion(m.getPuntuacion() + 2);
	}
      }
      else if(PUNTUACIONLETRAS[puntua] == 3)
      {
	if(tablero.getCasilla(m.getOrigen().getFila() + i,m.getOrigen().getColumna()) == DOBLELETRA && letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 6);
	  
	}
	else if(tablero.getCasilla(m.getOrigen().getFila() + i,m.getOrigen().getColumna()) == TRIPLELETRA && letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 9);
	  
	}
	else
	{
	  m.setPuntuacion(m.getPuntuacion() + 3);
	}
      }
      else if(PUNTUACIONLETRAS[puntua] == 4)
      {
	if(tablero.getCasilla(m.getOrigen().getFila() + i,m.getOrigen().getColumna()) == DOBLELETRA && letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 8);
	  
	}
	else if(tablero.getCasilla(m.getOrigen().getFila() + i,m.getOrigen().getColumna()) == TRIPLELETRA && letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 12);
	  
	}
	else
	{
	  m.setPuntuacion(m.getPuntuacion() + 4);
	}
      }
      else if(PUNTUACIONLETRAS[puntua] == 5)
      {
	if(tablero.getCasilla(m.getOrigen().getFila() + i,m.getOrigen().getColumna()) == DOBLELETRA && letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 10);
	  
	}
	else if(tablero.getCasilla(m.getOrigen().getFila() + i,m.getOrigen().getColumna()) == TRIPLELETRA && letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 15);
	  
	}
	else
	{
	  m.setPuntuacion(m.getPuntuacion() + 5);
	}
      }
      else if(PUNTUACIONLETRAS[puntua] == 8)
      {
	if(tablero.getCasilla(m.getOrigen().getFila() + i,m.getOrigen().getColumna()) == DOBLELETRA && letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 16);
	  
	}
	else if(tablero.getCasilla(m.getOrigen().getFila() + i,m.getOrigen().getColumna()) == TRIPLELETRA && letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 24);
	  
	}
	else
	{
	  m.setPuntuacion(m.getPuntuacion() + 8);
	}
      }
      else 
      {
	if(tablero.getCasilla(m.getOrigen().getFila() + i,m.getOrigen().getColumna()) == DOBLELETRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 20);
	  
	}
	else if(tablero.getCasilla(m.getOrigen().getFila() + i,m.getOrigen().getColumna()) == TRIPLELETRA && letras[m.getOrigen().getFila()][m.getOrigen().getColumna() + i].getSimbolo() == ' ')
	{
	  m.setPuntuacion(m.getPuntuacion() + 30);
	  
	}
	else
	{
	  m.setPuntuacion(m.getPuntuacion() + 10);
	}
      }
      if(tablero.getCasilla(m.getOrigen().getFila() + i,m.getOrigen().getColumna()) == DOBLEPALABRA && letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == ' ')
      {
	doblepa ++;
      }
      if(tablero.getCasilla(m.getOrigen().getFila() + i,m.getOrigen().getColumna()) == TRIPLEPALABRA && letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].getSimbolo() == ' ')
      {
	tripa ++;
      }
      letras[m.getOrigen().getFila() + i][m.getOrigen().getColumna()].setSimbolo(m.getPalabraString()[i]);       // Anyado por ultimo las letras en el tablero
    }
    if(doblepa > 0)
    {
      m.setPuntuacion(m.getPuntuacion() * 2 * doblepa);
      jugadores[turno-1].setPuntuacion(jugadores[turno-1].getPuntuacion() + m.getPuntuacion());  
      
    }
    else if(tripa > 0)
    {
      m.setPuntuacion(m.getPuntuacion() * 3 * tripa);
      jugadores[turno-1].setPuntuacion(jugadores[turno-1].getPuntuacion() + m.getPuntuacion());
    }
    else
    {
      jugadores[turno-1].setPuntuacion(jugadores[turno-1].getPuntuacion() + m.getPuntuacion());
    }
  }  
  movimientos.push_back(m);			  			// Almacenamos toda la informacion para los guardados
}


void Partida::inicializarSemilla()
{
  srand(0);
}

string Partida::imprimirMovimiento(Movimiento m)const
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
  return(guarda);
}

void Partida::limpiarBuffer() 
{ 
    while(cin.get() != '\n'); 
}

vector<Letra> Partida::getBolsa()const
{
  return(bolsa);
}

Letra Partida::getLetra(int fila, int columna)const
{
  return(letras[fila][columna]);
}

vector<Movimiento> Partida::getMovimientos()const
{
	return(movimientos);
}

Jugador Partida::getJugador(int numJugador)const
{
  return(jugadores[numJugador]);
}
