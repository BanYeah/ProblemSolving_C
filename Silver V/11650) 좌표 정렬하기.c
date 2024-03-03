#include <stdio.h>
#include <stdlib.h>

typedef struct _coordinate
{
  int x;
  int y;
} Coordinate;

void MergeSort(Coordinate *arr, int N, int size);
void Partition(Coordinate *arr, int N, int size);
void Merge(Coordinate *arr, int left_idx, int right_idx, int end_idx);

void MergeSort(Coordinate *arr, int N, int size)
{
  if (size > 1)
    Partition(arr, N, 1);
}
void Partition(Coordinate *arr, int N, int size)
{
  if (size < N)
  {
    for (int i = 0; i < N; i += size * 2)
    {
      if (i + size < N)
      {
        int end_idx = i + size * 2 < N ? i + size * 2 : N;
        Merge(arr, i, i + size, end_idx);
      }
    }
    Partition(arr, N, size * 2);
  }
}
void Merge(Coordinate *arr, int left_idx, int right_idx, int end_idx)
{
  int start_idx = left_idx, mid_idx = right_idx;

  int copy_size = end_idx - left_idx, copy_idx = 0;
  Coordinate *copy_arr = (Coordinate *)malloc(sizeof(Coordinate) * copy_size);

  // 순차적으로 정렬
  while (left_idx < mid_idx && right_idx < end_idx)
  {
    if (arr[left_idx].x < arr[right_idx].x || (arr[left_idx].x == arr[right_idx].x && arr[left_idx].y < arr[right_idx].y))
    {
      copy_arr[copy_idx] = arr[left_idx];
      left_idx++;
    }
    else
    {
      copy_arr[copy_idx] = arr[right_idx];
      right_idx++;
    }

    copy_idx++;
  }
  while (left_idx < mid_idx)
  {
    copy_arr[copy_idx] = arr[left_idx];
    left_idx++;
    copy_idx++;
  }
  while (right_idx < end_idx)
  {
    copy_arr[copy_idx] = arr[right_idx];
    right_idx++;
    copy_idx++;
  }

  for (int i = 0; i < copy_size; i++)
    arr[start_idx + i] = copy_arr[i];

  free(copy_arr);
}

int main()
{
  int N;
  scanf("%d", &N);

  // 동적 할당
  Coordinate *arr = (Coordinate *)malloc(sizeof(Coordinate) * N);
  for (int i = 0; i < N; i++)
    scanf("%d %d", &arr[i].x, &arr[i].y);

  // Merge Sort
  MergeSort(arr, N, N);

  for (int i = 0; i < N; i++)
    printf("%d %d\n", arr[i].x, arr[i].y);

  // 동적 할당 해제
  free(arr);
  return 0;
}