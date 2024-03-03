#include <stdio.h>
#include <stdlib.h>

typedef struct _person
{
  int age;
  char name[101];
} Person;

int main()
{
  int N;
  scanf("%d", &N);

  // 동적 할당 배열 생성
  Person *arr = (Person *)malloc(sizeof(Person) * N);

  // 나이와 이름을 입력 받기
  for (int i = 0; i < N; i++)
    scanf("%d %s", &arr[i].age, &arr[i].name);

  // Merge sort 실행
  for (int size = 1; size < N; size *= 2) // 각 부분의 크기
  {
    for (int idx = 0; idx < N; idx += size * 2)
    {
      int left_idx = idx;
      int right_idx = idx + size;

      // 부분적으로 정렬된 배열 저장할 공간
      Person *copy = (Person *)malloc(sizeof(Person) * size * 2);
      int copy_idx = 0;

      // 순차적으로 정렬
      while (left_idx < idx + size && left_idx < N && right_idx < idx + size * 2 && right_idx < N)
      {
        if (arr[left_idx].age <= arr[right_idx].age)
        {
          copy[copy_idx] = arr[left_idx];
          left_idx++;
        }
        else
        {
          copy[copy_idx] = arr[right_idx];
          right_idx++;
        }
        copy_idx++;
      }
      while (left_idx < idx + size && left_idx < N)
      {
        copy[copy_idx] = arr[left_idx];
        left_idx++;
        copy_idx++;
      }
      while (right_idx < idx + size * 2 && right_idx < N)
      {
        copy[copy_idx] = arr[right_idx];
        right_idx++;
        copy_idx++;
      }

      // 기존 배열에 복사해 넣기
      for (int i = idx; i < idx + size * 2 && i < N; i++)
        arr[i] = copy[i - idx];

      // 동적 할당 해제
      free(copy);
    }
  }

  // 정렬된 데이터 출력
  for (int i = 0; i < N; i++)
    printf("%d %s\n", arr[i].age, arr[i].name);

  // 동적 할당 해제
  free(arr);
  return 0;
}