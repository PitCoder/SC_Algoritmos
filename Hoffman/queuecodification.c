//*****************************************************************
//QUEUECODIFICATION.C 
//*****************************************************************
//*****************************************************************
//DIEGO ARTURO MORALES GONZALEZ
//PEDRO ANTONIO PAREDEZ HERNANDEZ
//ERIC ALEJANDRO LÓPEZ AYALA
//Curso: Análisis de algoritmos
//(C) Agosto 2017
//ESCOM-IPN
//Libreria que implementa los metodos de una cola en la
//cual se apoya el metodo de codificacion.
////Compilación de la libreria: "gcc -c queuecodification.c"
//*****************************************************************

//*****************************************************************
//Librerias incluidas
//*****************************************************************
#include <stdlib.h>
#include "queuecodification.h"

//*****************************************************************
//newQueue (Definition)
//*****************************************************************
//Descripción: Función que crea una nueva cola para atender las 
//codificaciones en espera.
//Recibe: QueueCodification *queue
//Devuelve: Void
//*****************************************************************
void newQueue(QueueCodification *queue){
	queue->count = 0;
	queue->begin = NULL;
	queue->end 	 = NULL;
}

//*****************************************************************
//createCodification (Definicion)
//*****************************************************************
//Descripción: Función que codifica los archivos en espera con un 
//valor dado.
//Recibe: QueueCodification *queue, char value
//Devuelve: Void
//*****************************************************************
void createCodification(QueueCodification *queue,char value){
	QueueNode *newNode = malloc(sizeof(QueueNode));	
	newNode->value = value;
	newNode->next  = NULL;
	if(queue->end == NULL) {
	   queue->end   = newNode;
	   queue->begin = newNode;		
	}
	else{
		queue->end->next = newNode;
		queue->end = newNode;
	}
	queue->count++;
}

//*****************************************************************
//setbeginCodification (Declaración)
//*****************************************************************
//Descripción: Función que empieza a codificar los archivos en espera
//Recibe: QueueCodification *queue, char value
//Devuelve: Void
//*****************************************************************
void setbeginCodification(QueueCodification *queue,char value){
	QueueNode *newNode = malloc(sizeof(QueueNode));	
	newNode->value = value;
	newNode->next  = queue->begin;
	queue->begin   = newNode;
	queue->count++;
}

//*****************************************************************
//listenQueue (Declaración)
//*****************************************************************
//Descripción: Función que codifica un archivo que se encuentra 
//en espera
//Recibe: QueueCodification *queue 
//Devuelve: char
//*****************************************************************
char listenQueue(QueueCodification *queue){
	QueueNode *aux = queue->begin;
	char val = queue->begin->value;
	queue->begin = queue->begin->next;
	queue->count--;
	free(aux);
	return val;
}

//*****************************************************************
//listenAll (Declaración)
//*****************************************************************
//Descripción: Función que codifica todos los archivos que se 
//encuentran en espera
//Recibe: QueueCodification *queue 
//Devuelve: Void
//*****************************************************************
void listenAll(QueueCodification *queue){
	while(queue->begin != NULL){
		listenQueue(queue);
	}
	queue->count = 0;
}
