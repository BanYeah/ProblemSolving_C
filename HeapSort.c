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

  // 동적 할당
  int *arr = (int *)malloc(sizeof(int) * (N + 1));
  int *sorted_arr = (int *)malloc(sizeof(int) * (N + 1));

  // Heap Sort Insertion
  for (int len = 1; len <= N; len++)
  {
    scanf("%d", &arr[len]); // 맨 뒤로 Insert

    int idx = len;
    while (idx > 1) // 부모와 비교
    {
      if (arr[idx] < arr[idx / 2])
      {
        Swap(&arr[idx], &arr[idx / 2]);
        idx /= 2;
      }
      else
        break;
    }
  }

  // Heap Sort Deletion
  for (int i = 1; i <= N; i++)
  {
    int len = N - i + 1, idx = 1;

    sorted_arr[i] = arr[1];
    arr[1] = arr[len]; // 마지막 요소를 root로

    while (idx * 2 + 1 <= len)
    {
      if (idx * 2 == len || arr[idx * 2] <= arr[idx * 2 + 1])
      {
        if (arr[idx] < arr[idx * 2])
          break;

        Swap(&arr[idx], &arr[idx * 2]);
        idx *= 2;
      }
      else
      {
        if (arr[idx] < arr[idx * 2 + 1])
          break;

        Swap(&arr[idx], &arr[idx * 2 + 1]);
        idx = idx * 2 + 1;
      }
    }
  }

  for (int i = 1; i <= N; i++)
    printf("%d\n", sorted_arr[i]);

  // 동적 할당 해제
  free(arr);
  free(sorted_arr);

  return 0;
}