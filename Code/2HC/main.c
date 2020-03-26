#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define AGENT_ID 15
#define STOP_CHAR '$'

int isAlpha(int);
int isDigit(int);


char *askId();

int isId(char*);

char* extremelyLargeString(char);

char* getNumberFromWord(char*);


void swap(char* a, char* b);

void randomize(char *word);

char *rtrim(char *, const char *);
char *ltrim(char *, const char *);
char *trim(char *, const char *);

int main(int argc, char const *argv[]) {

  char *AgentId = askId();

  char *longStringNumbers;
  

  while (!isId(AgentId)) 
  {
    printf("Formtao de ID incorrecto, intentalo otra vez\n");
    AgentId = askId();
  }

  printf("Dame los 9 digitos separados por coma y espacio para terminar dame '$'\n");
  longStringNumbers = extremelyLargeString(STOP_CHAR);
  
  char *word;
  char *numberStr;
  char *numbers = malloc(10 * sizeof(char));
  char *finalString = malloc(sizeof(char) * (14));
  strncpy(numbers, "", sizeof(numbers));


  int difference;

  word = strtok(longStringNumbers, ",");
  while(word != NULL) 
  {
    numberStr = getNumberFromWord(word);

    if(strlen(numbers) + strlen(numberStr) <= 9) {
      strcat(numbers, numberStr);
    }
    else {
      difference = 9 - strlen(numbers);
      strncat(numbers, numberStr, difference);
    }

    word = strtok(NULL, ",");
  }
  numbers[10] = '\0';

  printf("Los numeros dados son : %s \n", numbers);


  randomize(numbers);

  strncpy(finalString, AgentId, 4);
  strcat(finalString, numbers); 
  finalString[14] = '\0';


  printf("Muchas gracias, el nuevo ID es: %s \n", finalString);

  if(numbers != NULL) {
    free(numbers);
  }
  if(finalString != NULL) {
    free(finalString);
  }
  if(longStringNumbers != NULL) {
    free(longStringNumbers);
  }
  if(AgentId != NULL) {
    free(AgentId);
  }

  return 0;
}

char* getNumberFromWord(char* untrimmedWord) {


  char * word = trim(untrimmedWord, NULL);

  char *response = (char *)malloc(1);


  if(strcmp(word, "cero") == 0) {
    return "0\0";
  }
  if(strcmp(word, "cien") == 0) {
    return "100\0";
  }

  int numEspecificos = 20;
  char especificos[20][13] = {
    "diez"       ,"once"       ,"doce"       ,"trece"     ,"catorce"      ,"quince"     ,"dieciseis"  ,"diecisiete" ,"dieciocho" ,"diecinueve"   ,"veinte"     ,"veintiuno"  ,"veintidos"  ,"veintitres","veinticuatro" ,"veinticinco","veintiseis" ,"veintisiete","veintiocho","veintinueve"
    };

  for(int i = 0; i < 20; i++) {
    if(strcmp(word, especificos[i]) == 0) {
      char first = ((i / 10) + 1) + '0';
      char second = (i % 10) + '0';

      response = realloc(response, 3 * sizeof(char));
      response[0] = first;
      response[1] = second;
      response[2] = '\0';
    
      return response;
    }
  }

  int numDigitos = 9;
  char digitos[9][7] = {
    "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve"
  };
  for(int i = 0; i < numDigitos; i++) {
    if(strcmp(word, digitos[i]) == 0) {
      char digit = (i % 10) + '0' + 1;

      response = realloc(response, 2 * sizeof(char));
      response[0] = digit;
      response[1] = '\0';

      return response;
    }
  }

  int numDecimales = 6;
  char decimales[7][11] = {
    "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa"
  };
  for(int i = 0; i < numDecimales; i++) {
    if(strcmp(word, decimales[i]) == 0) {
      char digit = (i % 10) + '0' + 3;

      response = realloc(response, 3 * sizeof(char));
      response[0] = digit;
      response[1] = '0';
      response[2] = '\0';

      return response;
    }
  }

  char *superString = malloc(1);
  char *digito;
  char *decimal;
  char *concat = " y ";

  for(int i = 0; i < numDecimales; i++) 
  {
    decimal = decimales[i];
    for(int j = 0; j < numDigitos; j++) 
    {
      digito = digitos[j];

      int size = strlen(decimal) + strlen(digito) + strlen(concat);
      superString = realloc(superString, size * sizeof(char) + 1);

      strcpy(superString, decimal);
      strcat(superString, concat);
      strcat(superString, digito);
      superString[size] = '\0';

      if(strcmp(word, superString) == 0) 
      {
        char first = (i % 10) + '3';
        char second = (j % 10) + '0';

        response = realloc(response, 3 * sizeof(char));
        response[0] = first;
        response[1] = second + 1;
        response[2] = '\0';

        free(superString);
        return response;
      }
    }

  }

  return "-";
}

void randomize(char *word) 
{
  srand(time(NULL));

  int length = strlen(word);

  for(int i = length - 1; i > 0; i--) 
  {
    int j = rand() % (i + 1);
    swap(&word[i], &word[j]);
  }
}

void swap(char *a, char *b) 
{
  char temp = *a;
  *a = *b;
  *b = temp;
}

char* extremelyLargeString(char stopChar) 
{

  unsigned int maxCharsPerSection = 24;

  unsigned int currentChars = maxCharsPerSection;

  char *ptr = (char *)malloc(maxCharsPerSection * sizeof(char));
  char c;
  unsigned int i = 0;

  while ( (c = getchar()) != stopChar && c != EOF) 
  {
    ptr[i++] = tolower((char)c);

    if(i == currentChars) 
    {
      currentChars += maxCharsPerSection;
      ptr = realloc(ptr, currentChars);
    }
  }
  

  if(currentChars == maxCharsPerSection) 
  {
    ptr = realloc(ptr, currentChars + 1);
  }
  ptr[i] = '\0';

  return ptr;

}

char *askId() 
{
  char* id = (char *)malloc(AGENT_ID * sizeof(char));
  printf("\n");
  printf("Dame tu id\n");
  fgets(id, AGENT_ID, stdin);

  return id;
}

int isId(char *id) 
{
  int i;

  if (strlen(id) != AGENT_ID - 1) 
  {
    return 0;
  }

  for (i = 0; i < 4; i++) 
  {
    if (!isAlpha(id[i])) 
    {
      return 0;
    }
  }
  for (; i < AGENT_ID - 2; i++) 
  {
    if (!isDigit(id[i])) 
    {
      return 0;
    }
  }

  return 1;
}

int isAlpha(int letter) 
{
  return (letter >= 65 && letter <= 90) || (letter >= 97 && letter <= 122);
}

int isDigit(int letter) 
{
  return letter >= 48 && letter <= 57;
}

char *rtrim(char *word, const char *seps) 
{
  int i;
  if (seps == NULL) {
    seps = "\t\n\v\f\r ";
  }
  i = strlen(word) - 1;
  while (i >= 0 && strchr(seps, word[i]) != NULL) 
  {
    word[i] = '\0';
    i--;
  }
  return word;
}

char *ltrim(char *str, const char *seps) 
{
  size_t totrim;
  if (seps == NULL) 
  {
    seps = "\t\n\v\f\r ";
  }
  totrim = strspn(str, seps);
  if (totrim > 0) {
    size_t len = strlen(str);
    if (totrim == len) 
    {
      str[0] = '\0';
    }
    else 
    {
      memmove(str, str + totrim, len + 1 - totrim);
    }
  }
  return str;
}

char *trim(char *str, const char *seps) 
{
  return ltrim(rtrim(str, seps), seps);
}