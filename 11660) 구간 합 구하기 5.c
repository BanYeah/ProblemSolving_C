#include <stdio.h>
#include <stdlib.h>

int main()
{
  int N, M;
  scanf("%d %d", &N, &M);

  int **arr = (int **)malloc(sizeof(int *) * N);
  int **sum_arr = (int **)malloc(sizeof(int *) * N);

  for (int i = 0; i < N; i++)
  {
    arr[i] = (int *)malloc(sizeof(int) * N);
    sum_arr[i] = (int *)malloc(sizeof(int) * N);
  }

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      scanf("%d", &arr[i][j]);

      if (i == 0 && j == 0)
        sum_arr[0][0] = arr[0][0];
      else if (i == 0)
        sum_arr[0][j] = sum_arr[0][j - 1] + arr[0][j];
      else if (j == 0)
        sum_arr[i][0] = sum_arr[i - 1][0] + arr[i][0];
      else
        sum_arr[i][j] = sum_arr[i][j - 1] + sum_arr[i - 1][j] - sum_arr[i - 1][j - 1] + arr[i][j];
    }
  }

  int x1, y1, x2, y2;
  for (int i = 0; i < M; i++)
  {
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    if (x1 == 1 && y1 == 1)
      printf("%d\n", sum_arr[x2 - 1][y2 - 1]);
    else if (x1 == 1)
      printf("%d\n", sum_arr[x2 - 1][y2 - 1] - sum_arr[x2 - 1][y1 - 2]);
    else if (y1 == 1)
      printf("%d\n", sum_arr[x2 - 1][y2 - 1] - sum_arr[x1 - 2][y2 - 1]);
    else
      printf("%d\n", sum_arr[x2 - 1][y2 - 1] - sum_arr[x2 - 1][y1 - 2] - sum_arr[x1 - 2][y2 - 1] + sum_arr[x1 - 2][y1 - 2]);
  }

  for (int i = 0; i < N; i++)
  {
    free(arr[i]);
    free(sum_arr[i]);
  }
  free(arr);
  free(sum_arr);

  return 0;
}