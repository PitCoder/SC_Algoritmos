//*****************************************************************
//FRECUENCIES.C 
//*****************************************************************
//*****************************************************************
//DIEGO ARTURO MORALES GONZALEZ
//PEDRO ANTONIO PAREDEZ HERNANDEZ
//ERIC ALEJANDRO LÓPEZ AYALA
//Curso: Análisis de algoritmos
//(C) Agosto 2017
//ESCOM-IPN
//Libreria que implementa las estructuras y funciones para
//leer y generar las frecuencias del algoritmo de decodificacion
////Compilación de la libreria: "gcc -c frecuencies.c"
//*****************************************************************

//*****************************************************************
//Librerias incluidas
//*****************************************************************
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "frecuencies.h"

//*****************************************************************
//addFrecuency (Definicion)
//*****************************************************************
//Descripción: Función interna para insertar o actualizar la 
//frecuencia de un elemento.
//Recibe: FrecuencyList frecuencies, char character
//Devuelve: Void
//*****************************************************************
void addFrecuency(FrecuencyList *frecuencies,char character){
    // Buscamos si la frecuencia ya existe
    int x;
    FrecuencyNode *f;
    FrecuencyNode *fbefore;
    for(f=frecuencies->begin,fbefore=frecuencies->begin;f!=NULL;f=f->next){
		if(f->frec.character == character) { 
            // En caso de que exista solo incrementamos sus ocurrencias
            f->frec.ocurrences++;
			int ix = 0;
			if(f->next != NULL 
				&& f->frec.ocurrences > f->next->frec.ocurrences){
				
				FrecuencyNode *aux = f->next;
				if(f == frecuencies->begin) {
					// En caso de que el elemento que se tenga que mover esté en el inicio de la lista 
					frecuencies->begin = f->next;
					f->next = aux->next;
					frecuencies->begin->next = f;
				}
				else {
					// Si el elemento se encuentra en otra posición
					fbefore->next = f->next;
					f->next = fbefore->next->next;
					fbefore->next->next = f;
				}
			}
            // Salimos de la función
            return;
        }
		// Movemos el auxiliar a la siguiente posición
		fbefore = f;
	}
	// Si se llega hasta este punto significa que el nodo no existía anteriormente en la lista
    // Insertamos el nodo en la lista, como es su primera aparición, queda al inicio
    FrecuencyNode *aux = frecuencies->begin;
	f = (FrecuencyNode*) malloc(sizeof(FrecuencyNode));
    f->frec.character = character;
    f->frec.ocurrences = 1;
    f->next = aux;
    frecuencies->begin = f;
    frecuencies->length++;
}

//*****************************************************************
//generateFrecuencies (Definicion)
//*****************************************************************
//Descripción: Función para rellenar una lista de frecuencias 
//con los caracteres deseados.
//Recibe: FrecuencyList frecuencies, char characters[], int lenght
//Devuelve: Void
//*****************************************************************
void generateFrecuencies(FrecuencyList * frecuencies,char characters[],int length){
    // Comprobamos que la lista esté iniciada, si no lo está, la inicializamos
    if (frecuencies->begin == NULL) {
        frecuencies->length = 0;
    }
    int ix;
    // Recorremos el arreglo de caracteres para insertarlos en la lista de frecuencia
    for (ix = 0;ix<length;ix++) {
        addFrecuency(frecuencies,characters[ix]);
    }
}

//*****************************************************************
//frecuenciesVector (Definicion)
//*****************************************************************
//Descripción: Función para crear un vector de frecuencias ordenado 
//Recibe: FrecuencyList frecuencies
//Devuelve: frecuency*
//*****************************************************************
frecuency *frecuenciesVector(FrecuencyList *frecuencies){
	// Reservamos la memoria suficiente para almacenar el arreglo
	frecuency *vector = (frecuency*)malloc(frecuencies->length*sizeof(frecuency));
	int i = 0;
    FrecuencyNode *f;
    for(f = frecuencies->begin;f!=NULL;f=f->next,i++){
		vector[i] = f->frec;
	}
	sortbyOcurrences(vector,frecuencies->length);
	return vector;
}

//*****************************************************************
//sortbyOcurrences (Definicion)
//*****************************************************************
//Descripción: Función encargada de ordenar un arreglo de 
//frecuencias dada una lista de ellas,el arreglo resultante estara 
//ordenado de forma ascendete de acuerdo a sus apariciones
//Recibe: frecuency *vector, int lenght
//Devuelve: Void
//*****************************************************************
void sortbyOcurrences(frecuency *vector,int length){
	frecuency temp;
	int k = length/2;
	int i,j,v;
	//Shell sort para ordenar el vector de frecuencias de menor a mayor
	while(k>=1){
		for(i=k;i<length;i++){
			temp = vector[i];
			v = vector[i].ocurrences;
			j = i-k;
				while(j>=0 && vector[j].ocurrences > v){
					vector[j+k] = vector[j];
					j-=k;
				}
			vector[j+k] = temp;
		}
		k/=2;	
	}
}