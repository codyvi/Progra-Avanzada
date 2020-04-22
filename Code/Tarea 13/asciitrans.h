//
//  asciitrans.h
//  practica13
//
//  Created by Pepe Hdez hdez on 22/04/20.
//  Copyright © 2020 itesm. All rights reserved.
//

#include "stdio.h"
#include "stdlib.h"

#define DllExport __declspec(dllexport)


DllExport int asciiBinaryToInt(char *cBin);
DllExport int asciiHEXToInt(char *cHex);
DllExport double asciiToDouble(char *cNum);
