#include <stdio.h>

int main()
{
  int N;
  scanf("%d", &N);

  int result = 0, divisor = 1;
  int flag = 1;

  while (flag)
  {
    int sum = 0;
    int left_pointer, right_pointer;

    if (divisor % 2 != 0) // divisor가 홀수인 경우
    {
      sum += N / divisor;

      left_pointer = N / divisor - 1;
      right_pointer = N / divisor + 1;
    }
    else // divisor가 짝수인 경우
    {
      sum += N / divisor;
      if (N % divisor + 1 > N)
        break;

      sum += N / divisor + 1;

      left_pointer = N / divisor - 1;
      right_pointer = N / divisor + 2;
    }

    for (int i = 0; i < (divisor - 1) / 2; i++)
    {
      if (left_pointer <= 0 || right_pointer > N)
      {
        flag = 0;
        break;
      }

      sum += left_pointer + right_pointer;
      left_pointer--;
      right_pointer++;
    }
    if (!flag)
      break;

    if (sum == N)
      result++;

    divisor++;
  }

  printf("%d\n", result);

  return 0;
}