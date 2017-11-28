//*****************************************************************
//BITS.H 
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

//Si definimos la libreria en caso de que no lo este.
#ifndef __BITS_H__
#define	__BITS_H__

//*****************************************************************
//set1 (Declaración)
//*****************************************************************
//Descripción: Función encargada de poner el bit elegido en 1
//Recibe: char *array, int pos
//Devuelve: Void
//*****************************************************************
void set1(char *array,int pos);

//*****************************************************************
//set0 (Declaración)
//*****************************************************************
//Descripción: Función encargada de poner el bit elegido en 0
//Recibe: char *array, int pos
//Devuelve: Void
//*****************************************************************
void set0(char *array,int pos);

//*****************************************************************
//bitValue (Declaración)
//*****************************************************************
//Descripción: Función encargada de obtener el valor del bit en el 
//arreglo
//Recibe: char *array, int pos
//Devuelve: Void
//*****************************************************************
int bitValue(char *array, int pos);

#endif
