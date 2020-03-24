#Autor: David Alonso Cantú Martínez
#Matrícula: A00822455
#Fecha: 20/03/2020
#Cambia palabras de un archivo de texto por medio de sed

#!/bin/bash

cat $"Dracula.txt" | sed "s/Dracula/David/g" | \
                    sed "s/Jonathan Harker/Nook/g" | \
                    sed "s/Newcastle/Cumbre/g" | \
                    sed "s/Yesterday/Tomorrow/g" > $"NewBook.txt"