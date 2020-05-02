#include <stdbool.h>
#include "Convert.h"

int asciiBinaryToInt(char *s) {
    int converted = 0;

    while(*s != '\0') {
        if(*s != '0' && *s != '1'){
            return converted;
        }
        converted *= 2;

        if(*s == '1') {
            converted++;
        }
        s++;
    }
    return converted;
}

int asciiHEXToInt(char *s) {
    int converted = 0, valueToAdd;
    
    while(*s != '\0') {
        switch (*s) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            valueToAdd = *s - '0';
            break;
        case 'A':
            valueToAdd = 10;
            break;
        case 'B':
            valueToAdd = 11;
            break;
        case 'C':
            valueToAdd = 12;
            break;
        case 'D':
            valueToAdd = 13;
            break;
        case 'E':
            valueToAdd = 14;
            break;
        case 'F':
            valueToAdd = 15;
            break;
        default: 
            return converted;
        }

        converted *= 16;
        converted += valueToAdd;
        s++;
    }
    return converted;
}

double asciiToDouble(char *s) {
    double converted = 0, currentDecimal = 1;
    bool negative = false;

    // Skip sign and check if negative
    if(*s == '+' || *s == '-') {
        if(*s == '-') {
            negative = true;
        }
        s++;
    }

    while(*s != '.' && *s != '\0') {
        if(*s >= '0' && *s <= '9') {
            converted *= 10;
            converted += *s - '0';
        }
        else {
            break;
        }

        s++;
    }
    
    if(*s == '.') {
        s++;
    }

    while(*s != '\0') {
        if(*s >= '0' && *s <= '9') {
            currentDecimal *= 0.1;
            converted += (*s - '0') * currentDecimal;
        }
        else {
            break;
        }

        s++;
    }

    if(negative) {
        converted *= -1;
    }
    return converted;
}