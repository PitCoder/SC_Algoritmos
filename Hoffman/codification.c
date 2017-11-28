//*****************************************************************
//CODIFICATION.C
//*****************************************************************
//*****************************************************************
//DIEGO ARTURO MORALES GONZALEZ
//PEDRO ANTONIO PAREDEZ HERNANDEZ
//ERIC ALEJANDRO LÓPEZ AYALA
//Curso: Análisis de algoritmos
//(C) Agosto 2017
//ESCOM-IPN
//Libreria que implementa las estructuras y funciones para
//generar y recorrer el arbol de codificacion.
//Compilación de la libreria: "gcc -c codifcation.c bits.c frecuencies.c queuecodification.c" 
//*****************************************************************

//*****************************************************************
//Librerias incluidas
//*****************************************************************
#include <stdlib.h>
#include <stdio.h>
#include "bits.h"
#include "frecuencies.h"
#include "queuecodification.h"
#include "codification.h"

//*****************************************************************
//(Variables globales)
//*****************************************************************
TreeNode ** huffmanForest; // En este doble apuntador se almacenará la colección de frecuencias.
int nodes;				   // Longitud del bosque Huffman.

//*****************************************************************
//createTree (Definición)
//*****************************************************************
//Descripción: Estructura que crea el arbol de caracteres con las
//frecuencias obtenidas (Arbol de codificacion).
//Recibe: frecuency *frecuencies, int lenght
//Devuelve: Void
//*****************************************************************
void createTree(frecuency *frecuencies,int length){
	int i;
	nodes = length;
	// Reservamos memoria
	huffmanForest = (TreeNode**)malloc(length*sizeof(TreeNode*));
	// Como las frecuencias ya estaban ordenadas previamente, basta con asignarlas en ese orden dentro del nuevo arreglo
	for(i=0;i<length;i++) {
		TreeNode *leaf = (TreeNode*)malloc(sizeof(TreeNode));
		leaf -> frec 	  = &(frecuencies[i]); 			// Guardamos la información del caracter y sus apariciones
		leaf -> weight    = frecuencies[i].ocurrences; 	// Para el paso uno el peso es igual a la frecuencia del caracter
		leaf -> node0     = NULL; 						// Son hojas
		leaf -> node1     = NULL; 						// Son hojas
		leaf -> visited   = 0; 							// Lo marcamos como no visitado
		huffmanForest[i]  = leaf;
	}
	// Llamado a la función encargada de realizar las combinaciones
	generateUniqueTree();
	//ordenaVectorFrecuenciasPorCaracter(frecuencias, length);
	for(i = 0; i < length; i++) {
		// Usaremos una cola para guardar la sevuencia de 1 y 0
		QueueCodification *queue = (QueueCodification*)malloc(sizeof(QueueCodification));
		newQueue(queue);
		// Obtenemos el camino tantas veces como caracteres tenemos
		// En boasqueHuffman[0] está el árbol de codificación.
		getRPath(huffmanForest[0], queue);
		assignCodification(frecuencies, length, queue);
		// Liberamos la memoria de la cola
		free(queue);
	}
}

//*****************************************************************
//generateUniqueTree (Definition)
//*****************************************************************
//Descripción: Función que realiza la combinación de los árboles 
//hasta llegar a un único nodo.
//Recibe: Void
//Devuelve: Void
//*****************************************************************
void generateUniqueTree(){
	int i = nodes;
	int j;
	while(huffmanForest[1] != NULL){ // Mientras no tengamos un solo árbol
		// Generamos un nuevo árbol:
		TreeNode *newLeaf = (TreeNode*)malloc(sizeof(TreeNode));
		// Como es un árbol resultado de la combinación de otros dos, ya no deberá tener un caracter asociado
		newLeaf -> frec      = NULL;
		newLeaf -> weight    = huffmanForest[0] -> weight + huffmanForest[1] -> weight; 	// La suma de los pesos de sus dos hijos
		newLeaf -> node0     = huffmanForest[0]; 											// Hijo de menor frecuencia
		newLeaf -> node1     = huffmanForest[1]; 											// Hijo de mayor frecuencia
		newLeaf -> visited   = 0; 															// Lo marcamos como no visitado
		// Dentro de este for iremos recorriendo todos, un lugar hacia atrás cada vez
		for(j=2;j<i;j++){
			huffmanForest[j-1] = huffmanForest[j];
		}
		// Borramos el último elemento de la lista
		huffmanForest[j-1] = NULL;
		// Y asignamos el nuevo al inicio
		huffmanForest[0] = newLeaf;
		// Llamamos a la ordenación de los árboles para reacomodarlos según su peso
		sortTrees();
	}
}

//*****************************************************************
//sortTrees (Declaración)
//*****************************************************************
//Descripción: Función encargada de la reordenación de los árboles 
//dentro del arreglo.
//Recibe: Void
//Devuelve: Void
//*****************************************************************
void sortTrees(){
	TreeNode *temp;
	int k = nodes/2;
	int i,j,v;
	//Shell sort para ordenar el vector de frecuencias de menor a mayor
	while(k>=1){
		for(i=k;i<nodes && huffmanForest[i] != NULL;i++){
			temp = huffmanForest[i];
			v = temp->weight;
			j = i-k;
				while(j>=0 && huffmanForest[j+1] != NULL && huffmanForest[j]->weight > v){
					huffmanForest[j+k] = huffmanForest[j];
					j-=k;
				}
			huffmanForest[j+k] = temp;
		}
		k/=2;	
	}
}

//*****************************************************************
//getRPath (Definicion)
//*****************************************************************
//Descripción: Función que arma la codificación para cada caracter de forma recursiva, 
//almacena el resultado en una cola para posteriormente recuperarlo
//Recibe: TreeNode *tree, QueueCodification *queue
//Devuelve: Void
//*****************************************************************
void getRPath(TreeNode *tree, QueueCodification *queue) {
	// Comprobamos si el árbol no ha sido visitado
	if(tree != NULL && tree->visited == 0){
		// Si tiene hijo 0 y no ha sido visitado, nos movemos hacia el
		if(tree->node0 && tree->node0->visited == 0){
			// Insertamos un 0 en la cola
			createCodification(queue,'0');
			//printf("0");
			getRPath(tree->node0, queue);
		}		
		// Si tiene hijo 1 y no ha sido visitado, nos movemos hacia el
		else if(tree->node1 && tree->node1->visited == 0){
			createCodification(queue,'1');
			//printf("1");
			getRPath(tree->node1, queue);
		}	
		// Si no tiene hijos o ya fueron visitados
		else{
			// Lo marcamos como visitado
			tree->visited = 1;
			if(tree->frec != NULL){
				// Insertamos el caracter en la cola, pero al inicio
				setbeginCodification(queue,tree->frec->character);
			}
			// Insertamos el fin de línea como referencia
			createCodification(queue,'\0');
		}
		// Comprobamos que sea un nodo tallo
		if(tree->frec == NULL)
			// Si sus hijos ya fueron visitados
			if(tree->node0->visited == 1 && tree->node1->visited == 1)
				// Marcamos el padre como visitado
				tree->visited = 1;
	}
}

//*****************************************************************
//sortFVbyCharacter (Declaración)
//*****************************************************************
//Descripción: Función para reordenar el vector de frecuencias de acuerdo a los caracteres que contiene
//usando el algoritmo de ordenación por inserción.
//Recibe: frecuency *frecuencies, int lenght
//Devuelve: Void
//*****************************************************************
void sortFVbyCharacter(frecuency *frecuencies, int length){
	// Inicializamos una variable
	// auxiliar para recorrer el arreglo
	for(int ix = 1;ix<length;++ix){// Recorremos el arreglo
		// Asignamos el valor actual a
		// una variable temporal
		frecuency temp = frecuencies[ix];
		// Nos ubicamos en la posición anterior a 
		// la actual para ir revisando los valores
		int j = ix-1;
		while((frecuencies[j].character > temp.character) && (j >= 0)){
			// Nos vamos moviendo hacia atrás
			// hasta que encontremos la nueva
			// ubicación de nuestro valor
			frecuencies[j+1] = frecuencies[j];
			j--;
		}
		// Lo asignamos
		frecuencies[j+1] = temp;
	}
}

//*****************************************************************
//saveBits (Definicion)
//*****************************************************************
//Descripción: Funcion para modificar los bits de un arreglo de caracteres de acuerdo a los 
//parámetros recibidos.
//Recibe: char *output, int outputLenght, long pointer, char c, frecuency *frecuencies, int lenght
//Devuelve: int
//*****************************************************************
int saveBits(char *output,int outputLength,long pointer,char c, frecuency *frecuencies, int length){
	int writtenBits;
	int frecuencyIndex = searchFrecuency(frecuencies,0,length,c);
	frecuency f = frecuencies[frecuencyIndex];
	for(writtenBits=0;f.code[writtenBits]!='\0';writtenBits++){
		if(f.code[writtenBits]=='1'){
			set1(output,pointer + writtenBits);
		}
		else if(f.code[writtenBits]=='0'){
			set0(output,pointer + writtenBits);
		}
	}
	return writtenBits;
}

//*****************************************************************
//assignCodification (Definicion)
//*****************************************************************
//Descripción: Función encargada de asignar la secuencia de código correspondiente a cada caracter.
//Recibe: frecuency *frecuencies, int lenght, QueueCodification *queue
//Devuelve: Void
//*****************************************************************
void assignCodification(frecuency *frecuencies, int lenght, QueueCodification *queue){
	char character = listenQueue(queue);
	int codeLenght = queue -> count;
	int frecuencyIndex = searchFrecuency(frecuencies,0,lenght,character);
	int i;
	frecuencies[frecuencyIndex].code = (char*)calloc(codeLenght-1,sizeof(char));
	for(i=0;i<codeLenght;i++){
		frecuencies[frecuencyIndex].code[i] = listenQueue(queue);
	}
}

//*****************************************************************
//searchFrecuency (Definicion)
//*****************************************************************
//Descripción: Función para buscar un caracter dentro del arreglo de caracteres,
//utiliza búsqueda lineal
//Recibe: frecuency * frecuencies, int begin, int end, char c
//Devuelve: Void
//*****************************************************************
int searchFrecuency(frecuency * frecuencies, int begin, int end, char c){
	int i = -1;
	// TODO:	Implementar un mejor algoritmo de búsqueda
	for(begin=0;begin<end;begin++){
		if(frecuencies[begin].character == c){
			i = begin;
			break;
		}
	}
	return i;
}

//*****************************************************************
//decodeBits (Defincion)
//*****************************************************************
//Descripción: Funcion encargada de convertir de un arreglo de caracteres codificado a uno sin codificar empleando
//el árbol de codificación previamente generado
//Recibe: char *codified, long codifiedLenght, char *output
//Devuelve: Void
//*****************************************************************
void decodeBits(char *codified, long codifiedLenght, char *output){
	long x = 0;
	int v;
	int outputChar = 0;
	// Nos posicionamos en el la raíz de nuestro árbol
	TreeNode *aux = huffmanForest[0];
	// Navegamos entre los nodos de acuerdo al valor de los bits leídos
	// hasta terminar de recorrerlos todos
	for(x=0;x<codifiedLenght;){
		while(aux->frec == NULL){
			// Obtenemos el valor del bit y de acuerdo a este
			// nos movemos hacia la hoja 0 o 1 de nuetro árbol
			v = bitValue(codified,x++);
			if(v == 0)
				aux = aux -> node0;
			else if (v == 1)
				aux = aux -> node1;
		}
		// Asignamos el caracter asociado al arreglo de salida
		output[outputChar++] = aux -> frec -> character;
		// Nos colocamos nuevamente en la raíz del árbol
		aux = huffmanForest[0];
	}
}