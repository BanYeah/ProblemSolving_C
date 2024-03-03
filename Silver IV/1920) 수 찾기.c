#include <stdio.h>
#include <stdlib.h>

void MergeSort(int *arr, int N, int size);
void Partition(int *arr, int N, int size);
void Merge(int *arr, int left_idx, int right_idx, int end_idx);

void MergeSort(int *arr, int N, int size)
{
  if (size > 1)
    Partition(arr, N, 1);
}
void Partition(int *arr, int N, int size)
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
void Merge(int *arr, int left_idx, int right_idx, int end_idx)
{
  int start_idx = left_idx, mid_idx = right_idx;

  int copy_size = end_idx - left_idx, copy_idx = 0;
  int *copy_arr = (int *)malloc(sizeof(int) * copy_size);

  // 순차적으로 정렬
  while (left_idx < mid_idx && right_idx < end_idx)
  {
    if (arr[left_idx] <= arr[right_idx])
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

int BinarySearch(int *arr, int N, int target, int start_idx, int end_idx)
{
  if (start_idx > end_idx)
    return -1;

  int mid_idx = (start_idx + end_idx) / 2;
  if (arr[mid_idx] < target)
    return BinarySearch(arr, N, target, mid_idx + 1, end_idx);
  else if (arr[mid_idx] > target)
    return BinarySearch(arr, N, target, start_idx, mid_idx - 1);

  return mid_idx;
}

int main()
{
  int N;
  scanf("%d", &N);

  // 동적 할당
  int *arr = (int *)malloc(sizeof(int) * N);
  for (int i = 0; i < N; i++)
    scanf("%d", &arr[i]);

  // MergeSort
  MergeSort(arr, N, N);

  int M;
  scanf("%d", &M);

  // 동적 할당
  int *targer_arr = (int *)malloc(sizeof(int) * M);
  for (int i = 0; i < M; i++)
    scanf("%d", &targer_arr[i]);

  for (int i = 0; i < M; i++)
  {
    int target = targer_arr[i];
    // binary search 실행
    int find_idx = BinarySearch(arr, N, target, 0, N - 1);
    if (find_idx == -1)
      printf("0\n");
    else
      printf("1\n");
  }

  // 동적 할당 해제
  free(targer_arr);
  free(arr);
}