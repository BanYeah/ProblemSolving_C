#include <stdio.h>

int main()
{
  int N;
  scanf("%d", &N);

  int score[1000], sum = 0, M = -1;
  for (int i = 0; i < N; i++)
  {
    scanf("%d", &score[i]);
    sum += score[i];

    if (score[i] > M)
      M = score[i];
  }

  printf("%lf", (double)sum / M * 100 / N);

  return 0;
}