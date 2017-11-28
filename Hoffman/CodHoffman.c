//*****************************************************************
//CODHOFFMAN.C
//*****************************************************************
//*****************************************************************
//DIEGO ARTURO MORALES GONZALEZ
//PEDRO ANTONIO PAREDEZ HERNANDEZ
//ERIC ALEJANDRO LÓPEZ AYALA
//Curso: Análisis de algoritmos
//(C) Agosto 2017
//ESCOM-IPN
//Ejemplo de implementacion del algoritmo de codificación voraz de Hoffman en C 
//y recepción de parametros en C bajo UNIX.
//
//Compilación de la libreria: "gcc -c CodHoffman.c tiempo.c bits.c frecuencies.c codification.c queuecodification.c" 
//Generación del código objeto "gcc CodHoffman.c tiempo.c bits.c frecuencies.c codification.c queuecodification.c -o CodHoffman"
//*****************************************************************

//*****************************************************************
//Librerias incluidas
//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
#include "bits.h"
#include "frecuencies.h"
#include "queuecodification.h"
#include "codification.h"

//*****************************************************************
//Definición de constantes
//*****************************************************************
//Constante buffer de tamaño 1024 bits
#define BUFFER 1024

//*****************************************************************
//(Variables globales)
//*****************************************************************
//Apuntadores a archivos 
FILE *input;
FILE *frecuenciesFile;
FILE *decoded;
//Variable para medir tiempos
double 	utime0, stime0, wtime0,
		utime1, stime1, wtime1;

//Usada para almacenar temporalmente los valores del archivo
char buffer[BUFFER];	

//*****************************************************************
//savefrecTable (Declaracion)
//*****************************************************************
//Descripción: Función para imprimir la tabla de frecuencias a un 
//archivo especificado
//Recibe: frecuency *frecuencies, int lenght, int padding,
//int originalByte, const char path[]
//Devuelve: Void
//*****************************************************************
void savefrecTable(frecuency *frecuencies,int length,int padding,int originalByte,const char path[]);

int main(const int argc,char* argv[]){
	//******************************************************************	
	//Variables del main
	//******************************************************************
	char *output;
	char *codified;
	int  readed;
	int  realbitsWritten = 0;
	long totalReaded = 0;
	long totalBytes = 0;
	frecuency *frecArray;

	//******************************************************************	
	//Recepción y decodificación de argumentos
	//******************************************************************
	if(argc>3){
		if(argv[1][0] == '-' && argv[1][1] == 'd'){		//Comando para la decodificacion del archivo
			//******************************************************************	
			//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
			//******************************************************************	
			uswtime(&utime0, &stime0, &wtime0);

			//Apertura de flujos (Entradas/Salidas)
			//Input
			frecuenciesFile = fopen(argv[2],"r");	//Lee la tabla de frecuencias (archivo de texto) de la ruta especificada
			input 			= fopen(argv[3],"rb");  //Lee el archivo de entrada (Formato binario) de la ruta especificada
			//Output
			decoded			= fopen(argv[4],"wb");	//Write a non-text file (Formato binario) de la ruta especificada

			if(decoded == NULL || frecuenciesFile == NULL || input == NULL) {
				perror("\nError alguna de las rutas especificadas no ha sido encontrada\n");
				exit(1);			
			}

			// Variables auxiliares para la descompresión
			char character;
			char dump;
			int  ocurrences;
			int  padding;
			int  originalSize;
			int  numChar;
			long size;

			//Obtenemos el tamaño de nuestro archivo comprimido
			fseek (input,0,SEEK_END);
			size = ftell(input);
			//Devolvemos el apuntador al inicio del archivo
			rewind(input);
			
			totalReaded = size;
			
			//Leemos información importante sobre el archivo de salida
			fscanf(frecuenciesFile,"N%d",&numChar); 	 // El número de caracteres distintos en el archivo
			fscanf(frecuenciesFile,"%c" ,&dump); 		 // Salto de línea
			fscanf(frecuenciesFile,"P%d",&padding); 	 // El número de bits "basura"
			fscanf(frecuenciesFile,"%c" ,&dump); 		 // Salto de línea
			fscanf(frecuenciesFile,"T%d",&originalSize); // El tamaño original del archivo comprimido
			
			//Reservamos memoria para nuestro archivo de salida
			output    = (char*)malloc(originalSize*sizeof(char));
			//Reservamos memoria para nuestro archivo codificado
			codified  = (char*)malloc(size*sizeof(char));
			//Reservamos memoria para el arreglo de frecuencias
			frecArray = (frecuency*)malloc(numChar*sizeof(frecuency));
			
			//Lectura del archivo de la tabla de frecuencias para generar un arreglo
			for(readed=0;readed<numChar;readed++){
				fscanf(frecuenciesFile,"%c",&dump); //Salto de línea
				//Obtenemos los caracteres y su número de apariciones y a partir de ellos
				//se genera el árbol de decodificación
				fscanf(frecuenciesFile,"%c%d",&character,&ocurrences);
				frecuency f;
				f.character 	  = character;
				f.ocurrences 	  = ocurrences;
				frecArray[readed] = f;
			}
			//Cerramos el flujo para el archivo de frecuencias
			fclose(frecuenciesFile);
		
			//Ordenamos el arreglo por las apariciones
			sortbyOcurrences(frecArray,numChar);
			//Creamos el arbol de decodificacion
			createTree(frecArray,numChar);
		
			// Leemos el archivo codificado
			fread(codified,sizeof(char),size,input);
			//Cerramos el flujo de salida del archivo de entrada
			fclose(input);
			//Decodificamos los bits
			decodeBits(codified,(size*8)-padding,output);
		
			//Escribimos el archivo final ya decodificado
			fwrite(output,sizeof(char),originalSize,decoded);
			//Cerramos el flujo del archivo decodificado
			fclose(decoded);

			//******************************************************************	
			//Evaluar los tiempos de ejecución 
			//******************************************************************
			uswtime(&utime1, &stime1, &wtime1);

			//Cálculo del tiempo de ejecución del programa
			printf("\n");
			printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
			printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
			printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
			printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
			printf("\n");
			
			//Mostrar los tiempos en formato exponencial
			printf("\n");
			printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
			printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
			printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
			printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
			printf("\n");
			//******************************************************************

			//Una vez ya evaluados los tiempos de ejecución, obtenemos comprobamos que los archivos esten completos
			decoded    = fopen(argv[4],"rb");
			fseek (decoded,0,SEEK_END);
			totalBytes = ftell(decoded);
			rewind(decoded);
			fclose(decoded);
			// Imprimimos información 
			printf("\nDescompresion: ,%s, exitosa!!!, %ld, %ld, %s,\n",argv[3],totalReaded,totalBytes,argv[4]);
		}
		else if(argv[1][0] == '-' && argv[1][1] == 'c'){ //Comando para la codificacion del archivo
			//******************************************************************	
			//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
			//******************************************************************	
			uswtime(&utime0, &stime0, &wtime0);

			//Creamos una lista en la cual almacenaremos la frecuencia de cada caracter
			FrecuencyList f;
			//Inicializamos la lista
			f.begin = NULL;
			//Leemos el archivo de entrada
			input 	= fopen(argv[1],"rb");
			//Verificamos que la ruta especificada sea valida
			if (input == NULL) {
				perror("\nNo se puede abrir el fichero de entrada.\n");
				exit(1);
			}
			
			//Se realiza la lectura para generar el arbol
			do{
				//Leemos el archivo hasta que ya no haya que leer
				//fread nos devuelve la cantidad de datos leídos
				readed = fread(buffer,sizeof(char),BUFFER,input);
				totalReaded += readed;
				//Insertamos las frecuencias en nuestra tabla
				generateFrecuencies(&f,buffer,readed);
				//Cuando no se hayan ocupado todos los espacios en la lectura
				//sabemos que ya se terminó de leer el archivo
			}while(readed == BUFFER);
			
			//Reservamos memoria para almacenar el archivo comprimido
			output = (char*)malloc(totalReaded*sizeof(char));
			//Obtenemos el arreglo de frecuencias
			frecArray = frecuenciesVector(&f);
			//Generamos la codificación mediante la llamada a este método
			createTree(frecArray,f.length);
		
			// Regresamos al inicio del archivo
			readed = 0;
			rewind(input);
		
			int writeResult = 0;
			//Se realiza la lectura para generar la codificacion
			do{
				int iaux = 0;
				//Leemos el archivo hasta que ya no haya que leer
				//fread nos devuelve la cantidad de datos leídos
				readed = fread(buffer,sizeof(char),BUFFER,input);
				// Por cada caracter leído vamos a modificar los bits dentro de este ciclo
				for(iaux = 0;iaux < readed;iaux++){
					writeResult = saveBits(output,totalReaded*8,realbitsWritten,buffer[iaux],frecArray,f.length);
					if(writeResult < 0) 
						break;
					realbitsWritten += writeResult;
				}
				// Cuando no se hayan ocupado todos los espacios en la lectura
				// sabemos que ya se terminó de leer el archivo
				// Cuando no se puedan segir escribiendo bits en el arreglo de salida, rompemos el ciclo
			}while(readed == BUFFER && writeResult >= 0);
			
			//Cerramos el flujo para el archivo de entrada
			fclose(input); 
			
			totalBytes = (realbitsWritten/8); //Determinamos cuantos bytes ocupará el nuevo archivo
			int padding = totalBytes % 8;
			if(padding > 0){
				totalBytes++;
			}

			//Abrimos un flujo de salida para guardar el nuevo archivo
			decoded = fopen(argv[2],"w"); 
			//Escribimos el arreglo de chars, el cual fue modificado para contener la información
			fwrite(output,sizeof(char),totalBytes,decoded);
			//Cerramos el flujo del archivo
			fclose(decoded);
		
		
			// Imprimimos la tabla de frecuencias a un archivo para conservarla
			savefrecTable(frecArray,f.length,padding,totalReaded,argv[3]);

			//******************************************************************	
			//Evaluar los tiempos de ejecución 
			//******************************************************************
			uswtime(&utime1, &stime1, &wtime1);
			
			//Cálculo del tiempo de ejecución del programa
			printf("\n");
			printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
			printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
			printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
			printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
			printf("\n");
			
			//Mostrar los tiempos en formato exponencial
			printf("\n");
			printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
			printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
			printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
			printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
			printf("\n");
			//******************************************************************

			// Impresión de información relevante de la compresión [Académico]
			if(writeResult >= 0)
				printf("\ncompresion: , %s, exitosa!!!, ",argv[1]);
				
			else
				printf("\ncompresion: , %s, fallida!!!, ",argv[1]);
			
			printf(" %ld, %ld, %s\n",totalReaded,totalBytes,argv[2]);
		}
		else{
			perror("\nComando no valido: -d para decodificacion y -c para codificacion\n");
			exit(1);
		}
	}
	else{
		printf("\nNumero de argumentos insuficientes - i.e: [user@equipo]$ %s [-d'\'-c] path archivodefrecuencias archivoentrada archivosalida\n",argv[0]);
		exit(1);
	}
	return 0;
}

//*****************************************************************
//savefrecTable (Definicion)
//*****************************************************************
//Descripción: Función para imprimir la tabla de frecuencias a un 
//archivo especificado
//Recibe: frecuency *frecuencies, int lenght, int padding,
//int originalByte, const char path[]
//Devuelve: Void
//*****************************************************************
void savefrecTable(frecuency *frecuencies,int length,int padding,int originalByte,const char path[]){
	frecuenciesFile = fopen(path,"w");
    if(frecuenciesFile == NULL){
        perror("\nNo se puede abrir archivo\n");
		exit(1);
    }
	fprintf(frecuenciesFile,"N%d\n", length);
	fprintf(frecuenciesFile,"P%d\n", padding);
	fprintf(frecuenciesFile,"T%d\n", originalByte);
	// Impresión de las frecuencias al archivo especificado
	int i;
    for (i=0;i<length;i++){
        fprintf(frecuenciesFile,"%c%d\n"
                ,(int)frecuencies[i].character
                , frecuencies[i].ocurrences);
    }
    fclose(frecuenciesFile);
}