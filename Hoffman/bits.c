//*****************************************************************
//BITS.C
//*****************************************************************
//*****************************************************************
//DIEGO ARTURO MORALES GONZALEZ
//PEDRO ANTONIO PAREDEZ HERNANDEZ
//ERIC ALEJANDRO LÓPEZ AYALA
//Curso: Análisis de algoritmos
//(C) Agosto 2017
//ESCOM-IPN
//Libreria que implementa los cambios de bits en los codigos
//de los arreglos.
//Compilación de la libreria: "gcc -c bits.c"
//*****************************************************************

//*****************************************************************
//Librerias incluidas
//*****************************************************************
#include "bits.h"

//*****************************************************************
//set1 (Definicion)
//*****************************************************************
//Descripción: Función encargada de poner el bit elegido en 1
//Recibe: char *array, int pos
//Devuelve: Void
//*****************************************************************
void set1(char *array,int pos){
	// Obtenemos el índice dentro del arreglo
	int ix = pos / BYTE;
	// Obtenemos la posición del bit dentro del arreglo
	int i = pos - (BYTE * ix);
	i =  BYTE - i - 1;
	SET_1(array[ix],i);
}

//*****************************************************************
//set0 (Definicion)
//*****************************************************************
//Descripción: Función encargada de poner el bit elegido en 0
//Recibe: char *array, int pos
//Devuelve: Void
//*****************************************************************
void set0(char *array,int pos){
	// Obtenemos el índice dentro del arreglo
	int ix = pos / BYTE;
	// Obtenemos la posición del bit dentro del arreglo
	int i = pos - (BYTE * ix);
	i =  BYTE - i - 1;
	SET_0(array[ix],i);
}

//*****************************************************************
//bitValue (Definicion)
//*****************************************************************
//Descripción: Función encargada de obtener el valor del bit en el 
//arreglo
//Recibe: char *array, int pos
//Devuelve: Void
//*****************************************************************
int bitValue(char *array,int pos){
	// Obtenemos el índice dentro del arreglo
	int ix = pos / BYTE;
	// Obtenemos la posición del bit dentro del arreglo
	int i = pos - (BYTE * ix);
	i =  BYTE - i - 1;
	return TAKEBIT(array[ix],i);
}
