#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _word
{
  char str[51];
  int len;
} Word;

void MergeSort(Word *arr, int N, int size);
void Partition(Word *arr, int N, int size);
void Merge(Word *arr, int left_idx, int right_idx, int end_idx);

// partition
void MergeSort(Word *arr, int N, int size)
{
  if (size > 1)
    Partition(arr, N, 1);
}

void Partition(Word *arr, int N, int size)
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

void Merge(Word *arr, int left_idx, int right_idx, int end_idx)
{
  int start_idx = left_idx, mid_idx = right_idx;

  int copy_size = end_idx - left_idx, copy_idx = 0;
  Word *copy_arr = (Word *)malloc(sizeof(Word) * copy_size);

  // 순차적으로 정렬
  while (left_idx < mid_idx && right_idx < end_idx)
  {
    if (arr[left_idx].len != arr[right_idx].len)
    {
      if (arr[left_idx].len <= arr[right_idx].len)
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
    else if (strcmp(arr[left_idx].str, arr[right_idx].str) < 0)
    {
      copy_arr[copy_idx] = arr[left_idx];
      left_idx++;
      copy_idx++;
    }
    else
    {
      copy_arr[copy_idx] = arr[right_idx];
      right_idx++;
      copy_idx++;
    }
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
  Word *arr = (Word *)malloc(sizeof(Word) * N);
  for (int i = 0; i < N; i++)
  {
    scanf("%s", &arr[i].str);
    arr[i].len = strlen(arr[i].str);
  }

  // Merge Sort
  MergeSort(arr, N, N);

  // 정렬 결과 출력
  char prev_word[51];
  for (int i = 0; i < N; i++)
  {
    // 중복된 단어는 출력 X
    if (i != 0 && strcmp(prev_word, arr[i].str) == 0)
      continue;
    printf("%s\n", arr[i].str);
    strcpy(prev_word, arr[i].str);
  }

  // 동적 할당 해제
  free(arr);

  return 0;
}
