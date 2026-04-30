
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void le_vet(int n, int v[n])
{
  printf("Digite os %d elementos de um vetor\n", n);
  for (int i = 0; i < n; i++) {
    printf("digite o elemento %d ", i);
    scanf("%d", &v[i]);
  }
}

void imprime_vet(int n, int v[n])
{
  printf("[ ");
  for (int i = 0; i < n; i++) {
    printf("%d ", v[i]);
  }
  printf("]\n");
}

int main()
{
  int x[10];

  le_vet(5, x);
  printf("vetor digitado: ");
  imprime_vet(10000, x);
  printf("\n");
}
