
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main()
{
  int x[10];

  printf("Digite os 10 elementos de um vetor\n");
  for (int i = 0; i < 10; i++) {
    printf("digite o elemento %d ", i);
    scanf("%d", &x[i]);
  }
  printf("vetor digitado: ");
  for (int i = 0; i < 10; i++) {
    printf("%d ", x[i]);
  }
  printf("\n");
}
