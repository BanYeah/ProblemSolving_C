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

  int arr[10];
  int len = 0;
  for (; N > 0 && len < 10; len++)
  {
    arr[len] = N % 10;
    N /= 10;
  }

  // Selection Sort: Max 값을 찾아서 앞으로 이동
  for (int i = 0; i < len - 1; i++)
  {
    int max_idx = i;
    for (int j = i + 1; j < len; j++)
    {
      if (arr[j] > arr[max_idx])
        max_idx = j;
    }
    Swap(&arr[i], &arr[max_idx]);
  }

  for (int i = 0; i < len; i++)
  {
    printf("%d", arr[i]);
  }
  printf("\n");

  return 0;
}