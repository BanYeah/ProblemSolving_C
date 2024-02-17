#include <stdio.h>
#include <stdlib.h>

void Swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int main()
{
  int N;
  scanf("%d", &N);

  int *arr = (int *)malloc(sizeof(int) * N);
  for (int i = 0; i < N; i++)
    scanf("%d", &arr[i]);

  // Insertion Sort
  for (int i = 1; i < N; i++)
  {
    for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--)
      Swap(&arr[j], &arr[j + 1]);
  }

  int time = 0, sum = 0;
  for (int i = 0; i < N; i++)
  {
    time += sum + arr[i];
    sum += arr[i];
  }
  printf("%d\n", time);

  free(arr);
  return 0;
}