//*****************************************************************
//FRECUENCIES.H 
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

//Si definimos la libreria en caso de que no lo este.
#ifndef __FRECUENCIES_H__
#define	__FRECUENCIES_H__

//*****************************************************************
//Estructuras
//*****************************************************************

//*****************************************************************
//frecuency (Declaración)
//*****************************************************************
//Descripción: Estructura que almacenara el caracter y el numero
//de aparaciones que este tiene en el texto, asi mismo contiene
//el codigo que lo representa.
//*****************************************************************
typedef struct{
    char *code;
    char character;
    int ocurrences;
}frecuency;

//*****************************************************************
//frecuencyNode (Declaración), renombrado como FreacuencyNode
//*****************************************************************
//Descripción: Estructura que representa un nodo de frecunecia
//esta estructura sera necesaria para generar el arbol de 
//codificacion/decodificacion.
//*****************************************************************
typedef struct frecuencyNode{
    frecuency frec;
    struct frecuencyNode *next;
}FrecuencyNode;

//*****************************************************************
//frecuencyList (Declaración)
//*****************************************************************
//Descripción: Estructura que representa una lista de nodos
//de frecuencia.
//*****************************************************************
typedef struct frecuencyList{
    FrecuencyNode *begin;
    int length;
}FrecuencyList;

//*****************************************************************
//addFrecuency (Declaración)
//*****************************************************************
//Descripción: Función interna para insertar o actualizar la 
//frecuencia de un elemento.
//Recibe: FrecuencyList frecuencies, char character
//Devuelve: Void
//*****************************************************************
void addFrecuency(FrecuencyList *frecuencies,char caracter);

//*****************************************************************
//generateFrecuencies (Declaración)
//*****************************************************************
//Descripción: Función para rellenar una lista de frecuencias 
//con los caracteres deseados.
//Recibe: FrecuencyList frecuencies, char characters[], int lenght
//Devuelve: Void
//*****************************************************************
void generateFrecuencies(FrecuencyList * frecuencies,char characters[],int length);


//*****************************************************************
//frecuenciesVector (Declaración)
//*****************************************************************
//Descripción: Función para crear un vector de frecuencias ordenado 
//Recibe: FrecuencyList frecuencies
//Devuelve: frecuency*
//*****************************************************************
frecuency *frecuenciesVector(FrecuencyList *frecuencies);

//*****************************************************************
//sortbyOcurrences (Declaración)
//*****************************************************************
//Descripción: Función encargada de ordenar un arreglo de 
//frecuencias dada una lista de ellas,el arreglo resultante estara 
//ordenado de forma ascendete de acuerdo a sus apariciones
//Recibe: frecuency *vector, int lenght
//Devuelve: Void
//*****************************************************************
void sortbyOcurrences(frecuency *vector,int length);

#endif