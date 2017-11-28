#!/bin/bash
echo "---Comenzando compresion Monalisa.bmp---"
./CodHoffman entradas/Monalisa.bmp comprimidos/Monalisa tablas/MonaTab.txt > resultados/RepMonalisa.txt
echo "---Comenzando descompresion Monalisa.bmp---"
./CodHoffman -d tablas/MonaTab.txt comprimidos/Monalisa descomprimidos/Monalisa.bmp >> resultados/RepMonalisa.txt
echo "---Comenzando compresion Intervalos.doc---"
./CodHoffman entradas/Intervalos.doc comprimidos/Intervalos tablas/InterTab.txt > resultados/RepInter.txt
echo "---Comenzando descompresion Intervalos.doc---"
./CodHoffman -d tablas/InterTab.txt comprimidos/Intervalos descomprimidos/Intervalos.doc >> resultados/RepInter.txt
echo "---Comenzando compresion numeros10millones.txt---"
./CodHoffman entradas/numeros10millones.txt comprimidos/numeros10millones tablas/NumTab.txt >  resultados/RepNum.txt
echo "---Comenzando descompresion numeros10millones.txt---"
./CodHoffman -d tablas/NumTab.txt comprimidos/numeros10millones descomprimidos/numeros10millones.txt >> resultados/RepNum.txt
echo "---Comenzando compresion Prueba.pdf---"
./CodHoffman entradas/Prueba.pdf comprimidos/Prueba tablas/PruebaTab.txt > resultados/RepPrueba.txt
echo "---Comenzando descompresion Prueba.pdf---"
./CodHoffman -d tablas/PruebaTab.txt comprimidos/Prueba descomprimidos/Prueba.pdf >> resultados/RepPrueba.txt
echo "---Comenzando compresion FileRegister.zip---"
./CodHoffman entradas/FileRegister.zip comprimidos/FileRegister tablas/RegisterTab.txt > resultados/RepRegister.txt
echo "---Comenzando descompresion FileRegister.zip---"
./CodHoffman -d tablas/RegisterTab.txt comprimidos/FileRegister descomprimidos/FileRegister.zip >> resultados/RepRegister.txt
echo "---Comenzando compresion Practica03.pdf---"
./CodHoffman entradas/Practica03.pdf comprimidos/Practica3 tablas/Practica3Tab.txt > resultados/RepPractica3.txt
