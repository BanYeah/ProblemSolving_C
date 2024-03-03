#include <stdio.h>
#include <stdlib.h>

int main()
{
  int N, M, input;

  scanf("%d %d", &N, &M);

  long long int *sum_arr = (long long int *)malloc(sizeof(long long int) * N);
  long long int *remain_arr = (long long int *)malloc(sizeof(long long int) * M);
  for (int i = 0; i < M; i++)
    remain_arr[i] = 0; // 각 배열의 내용을 0으로 초기화

  // 합 배열 생성
  for (int i = 0; i < N; i++)
  {
    scanf("%d", &input);

    if (i == 0)
      sum_arr[0] = input;
    else
      sum_arr[i] = sum_arr[i - 1] + input;
  }

  // 합 배열의 나머지 배열 생성
  for (int i = 0; i < N; i++)
  {
    long long int remainder = sum_arr[i] % M;
    remain_arr[remainder]++;
  }

  long long int result = 0;
  for (int i = 0; i < M; i++)
  {
    long n = remain_arr[i];
    if (i == 0)
      result += n;

    result += n * (n - 1) / 2;
  }
  printf("%lld\n", result);

  free(sum_arr);
  free(remain_arr);
}