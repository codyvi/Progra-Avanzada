#include <stdio.h>
#include <stdbool.h> 

bool isPrime(int n) 
{ 

    if (n <= 1)  
    {
      return false; 
    }
  
    for (int i=2; i<n; i++)
    {
        if (n%i == 0) 
        {
            return false;
        } 
    } 
    return true; 
}

int main() 
{
  int tmp = 0;
  printf("Dame un numero: ");
  scanf("%d", &tmp);

  if(isPrime(tmp))
  {
    printf("Es un numero primo\n");
  }

  else
  {
    printf("No es un numero primo\n");
  }

  return 0;
}