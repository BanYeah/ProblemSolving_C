#include <stdio.h>
#include <stdlib.h>

int main()
{
  int N, M;
  scanf("%d %d", &N, &M);

  int *arr = (int *)malloc(sizeof(int) * N);
  int *sum_arr = (int *)malloc(sizeof(int) * N);
  for (int i = 0; i < N; i++)
  {
    scanf("%d", &arr[i]);

    if (i == 0)
      sum_arr[0] = arr[0];
    else
      sum_arr[i] = arr[i] + sum_arr[i - 1];
  }

  int i, j;
  for (int k = 0; k < M; k++)
  {
    scanf("%d %d", &i, &j);

    if (i == 1)
      printf("%d\n", sum_arr[j - 1]);
    else
      printf("%d\n", sum_arr[j - 1] - sum_arr[i - 2]);
  }

  free(arr);
  return 0;
}