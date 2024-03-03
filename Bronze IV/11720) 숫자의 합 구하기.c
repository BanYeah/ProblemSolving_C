#include <stdio.h>

int main()
{
  int N;
  scanf("%d", &N);

  char input[100];
  scanf("%s", input);

  int sum = 0;
  for (int i = 0; i < N; i++)
    sum += input[i] - '0';

  printf("%d", sum);
}