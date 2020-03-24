#!/bin/bash

cat $"Dracula.txt" | sed "s/Dracula/David/g" | \
                    sed "s/Jonathan Harker/Nook/g" | \
                    sed "s/Newcastle/Cumbre/g" | \
                    sed "s/Yesterday/Tomorrow/g" > $"NewBook.txt"