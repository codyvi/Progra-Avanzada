#include "stdio.h"

void fibonacci(int n) 
{
  int i = 0;
	int j = 1;
  if(n == 1)
  {
    printf("%d", i);
    printf(" ");
  }

  else if (n > 1)
  {
    printf("%d %d", i,j);
    printf(" ");
    for (int k = 2; k < n; k++)
      {	
        int t;
        t = i + j;
        i = j;
        j = t;
        printf("%d", j);
        printf(" ");
      }
  }

}

int main()
{
  int Num = 0;
  printf("Dame la cantidad de numeros de la secuencia: ");
  scanf("%d", &Num);
  printf("La secuencia fibonnaci de ");
  printf("%d", Num);
  if(Num == 1)
  {
    printf(" numero es: ");
  }
  else
  {
    printf(" numeros es: ");
  }
  fibonacci(Num);
  printf("\n");
  return 0;
}
