#!/bin/bash

#Grep para buscar los hashtags del archivo html, los junta y devuelve en pantalla
grep -o "hashtag\/[A-Za-z0-9_]\+" met.html | sort -n | uniq -ic 