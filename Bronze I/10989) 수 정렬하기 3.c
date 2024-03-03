#include <stdio.h>
#include <stdlib.h>

int main()
{
  int N;
  scanf("%d", &N);

  int *num_arr = (int *)malloc(sizeof(int) * 10001);
  for (int i = 0; i <= 10001; i++)
    num_arr[i] = 0;

  for (int i = 0; i < N; i++)
  {
    int input;
    scanf("%d", &input);
    num_arr[input]++;
  }

  for (int i = 0; i <= 10001; i++)
  {
    while (num_arr[i] > 0)
    {
      printf("%d\n", i);
      num_arr[i]--;
    }
  }

  free(num_arr);
  return 0;
}