//*****************************************************************
//QUEUECODIFICATION.H 
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

//Si definimos la libreria en caso de que no lo este.
#ifndef __QUEUECODIFICATION_H__
#define	__QUEUECODIFICATION_H__

//*****************************************************************
//Estructuras
//*****************************************************************

//*****************************************************************
//queueNode (Declaración) renombrado como QueueNode
//*****************************************************************
//Descripción: Estructura que almacenara un nodo de la estructura
//cola, el cual contendra el valor del caracter y un apuntador al
//siguiente nodo.
//*****************************************************************
typedef struct queueNode{
	char value;
	struct queueNode *next;
}QueueNode;

//*****************************************************************
//queueCodification (Declaración) renombrado como QueueCodification
//*****************************************************************
//Descripción: Estructura que almacenara un nodo de la estructura
//cola, el cual contendra el valor del caracter y un apuntador al
//siguiente nodo.
//*****************************************************************
typedef struct queueCodification{
	QueueNode *begin;
	QueueNode *end;
	int count;
}QueueCodification;

//*****************************************************************
//newQueue (Declaración)
//*****************************************************************
//Descripción: Función que crea una nueva cola para atender las 
//codificaciones en espera.
//Recibe: QueueCodification *queue
//Devuelve: Void
//*****************************************************************
void newQueue(QueueCodification *queue);

//*****************************************************************
//createCodification (Declaración)
//*****************************************************************
//Descripción: Función que codifica los archivos en espera con un 
//valor dado.
//Recibe: QueueCodification *queue, char value
//Devuelve: Void
//*****************************************************************
void createCodification(QueueCodification *queue,char value);

//*****************************************************************
//setbeginCodification (Declaración)
//*****************************************************************
//Descripción: Función que empieza a codificar los archivos en espera
//Recibe: QueueCodification *queue, char value
//Devuelve: Void
//*****************************************************************
void setbeginCodification(QueueCodification *queue,char value);

//*****************************************************************
//listenQueue (Declaración)
//*****************************************************************
//Descripción: Función que codifica un archivo que se encuentra 
//en espera
//Recibe: QueueCodification *queue 
//Devuelve: char
//*****************************************************************
char listenQueue(QueueCodification *queue);

//*****************************************************************
//listenAll (Declaración)
//*****************************************************************
//Descripción: Función que codifica todos los archivos que se 
//encuentran en espera
//Recibe: QueueCodification *queue 
//Devuelve: Void
//*****************************************************************
void listenAll(QueueCodification *queue);

#endif