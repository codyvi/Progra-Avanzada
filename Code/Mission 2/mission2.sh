#Autor: David Alonso Cantú Martínez
#Matrícula: A00822455
#Fecha: 24/03/2020
#Cambia palabras de un archivo de texto por medio de sed

#!/bin/bash

cat $"Dracula.txt" | sed "s/Dracula/David/g" | \
                    sed "s/DRACULA/David/g" | \
                    sed "s/Jonathan Harker/Nook/g" | \
                    sed "s/Newcastle/Cumbres/g" | \
                    sed "s/10:18/04:20/g" | \
                    sed "s/Yesterday/Tomorrow/g" > $"NewBook.txt"