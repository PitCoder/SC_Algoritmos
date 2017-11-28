//*****************************************************************
//CODIFICATION.H
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

//Si definimos la libreria en caso de que no lo este.
#ifndef __CODIFICACION_H__
#define	__CODIFICACION_H__

//*****************************************************************
//Estructuras
//*****************************************************************

//*****************************************************************
//treeNode (Declaración) renombrado como TreeNode
//*****************************************************************
//Descripción: Estructura que almacenara un nodo de la estructura
//cola, el cual contendra el valor del caracter y un apuntador al
//siguiente nodo.
//*****************************************************************
typedef struct treeNode{
	frecuency *frec;
	int weight;
	struct treeNode *node0;
	struct treeNode *node1;
	unsigned visited : 1;
}TreeNode;

//*****************************************************************
//createTree (Declaración)
//*****************************************************************
//Descripción: Estructura que crea el arbol de caracteres con las
//frecuencias obtenidas (Arbol de codificacion).
//Recibe: frecuency *frecuencies, int lenght
//Devuelve: Void
//*****************************************************************
void createTree(frecuency *frecuencies,int length);

//*****************************************************************
//generateUniqueTree (Declaración)
//*****************************************************************
//Descripción: Funcion que realiza la combinación de los árboles 
//hasta llegar a un único nodo.
//Recibe: Void
//Devuelve: Void
//*****************************************************************
void generateUniqueTree();

//*****************************************************************
//sortTrees (Declaración)
//*****************************************************************
//Descripción: Funcion encargada de la reordenación de los árboles 
//dentro del arreglo.
//Recibe: Void
//Devuelve: Void
//*****************************************************************
void sortTrees();

//*****************************************************************
//getRPath (Declaración)
//*****************************************************************
//Descripción: Funcion que arma la codificación para cada caracter de forma recursiva, 
//almacena el resultado en una cola para posteriormente recuperarlo.
//Recibe: TreeNode *tree, QueueCodification *queue
//Devuelve: Void
//*****************************************************************
void getRPath(TreeNode *tree, QueueCodification *queue);

//*****************************************************************
//sortFVbyCharacter (Declaración)
//*****************************************************************
//Descripción: Funcion para reordenar el vector de frecuencias de acuerdo a los caracteres que contiene
//usando el algoritmo de ordenación por inserción.
//Recibe: frecuency *frecuencies, int lenght
//Devuelve: Void
//*****************************************************************
void sortFVbyCharacter(frecuency *frecuencies, int length);

//*****************************************************************
//saveBits (Declaración)
//*****************************************************************
//Descripción: Funcion para modificar los bits de un arreglo de caracteres de acuerdo a los 
//parámetros recibidos.
//Recibe: char *output, int outputLenght, long pointer, char frecuency *frecuencies, int lenght
//Devuelve: int
//*****************************************************************
int saveBits(char *output,int outputLength,long pointer,char c, frecuency *frecuencies, int length);

//*****************************************************************
//assignCodification (Declaración)
//*****************************************************************
//Descripción: Función encargada de asignar la secuencia de código correspondiente a cada caracter.
//Recibe: frecuency *frecuencies, int lenght, QueueCodification *queue
//Devuelve: Void
//*****************************************************************
void assignCodification(frecuency *frecuencies, int lenght, QueueCodification *queue);

//*****************************************************************
//searchFrecuency (Declaración)
//*****************************************************************
//Descripción: Función para buscar un caracter dentro del arreglo de caracteres,
//utiliza búsqueda lineal
//Recibe: frecuency * frecuencies, int begin, int end, char c
//Devuelve: Void
//*****************************************************************
int searchFrecuency(frecuency * frecuencies, int begin, int end, char c);

//*****************************************************************
//decodeBits (Declaración)
//*****************************************************************
//Descripción: Funcion encargada de convertir de un arreglo de caracteres codificado a uno sin codificar empleando
//el árbol de codificación previamente generado
//Recibe: char *codified, long codifiedLenght, char *output
//Devuelve: Void
//*****************************************************************
void decodeBits(char *codified, long codifiedLenght, char *output);

#endif	/* __CODIFICACION_H__ */