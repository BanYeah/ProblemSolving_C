#include <stdio.h>

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int main()
{
  int N = 0; // 수의 개수
  scanf("%d", &N);

  int arr[1000] = {0}; // 수를 저장할 공간

  for (int i = 0; i < N; i++) // 수를 입력 받기
    scanf("%d", &arr[i]);

  // selection sort
  for (int i = 1; i < N; i++)
  {
    for (int j = i - 1; j >= 0; j--)
    {
      if (arr[j] > arr[j + 1])
        swap(&arr[j], &arr[j + 1]);
      else
        break;
    }
  }

  for (int i = 0; i < N; i++) // 수 출력하기
    printf("%d\n", arr[i]);

  return 0;
}