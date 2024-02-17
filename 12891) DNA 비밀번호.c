#include <stdio.h>
#include <stdlib.h>

int main()
{
  int S, P;
  scanf("%d %d", &S, &P);

  // 동적 할당
  char *str = (char *)malloc(sizeof(char) * (S + 1));
  scanf("%s", str);

  int A, C, G, T;
  scanf("%d %d %d %d", &A, &C, &G, &T);

  // 구간 합 동적 할당
  int **sum_arr = (int **)malloc(sizeof(int *) * S);
  for (int i = 0; i < S; i++)
    sum_arr[i] = (int *)calloc(4, sizeof(int));

  // 구간 합 계산
  for (int i = 0; i < S; i++)
  {
    if (i != 0)
    {
      for (int j = 0; j < 4; j++)
        sum_arr[i][j] = sum_arr[i - 1][j];
    }

    switch (str[i])
    {
    case 'A':
      sum_arr[i][0]++;
      break;
    case 'C':
      sum_arr[i][1]++;
      break;
    case 'G':
      sum_arr[i][2]++;
      break;
    case 'T':
      sum_arr[i][3]++;
      break;
    }
  }

  int result = 0;
  for (int i = 0; i <= S - P; i++)
  {
    int left = i, right = i + P - 1;
    int num_A, num_C, num_G, num_T;

    if (i == 0)
    {
      num_A = sum_arr[right][0];
      num_C = sum_arr[right][1];
      num_G = sum_arr[right][2];
      num_T = sum_arr[right][3];
    }
    else
    {
      num_A = sum_arr[right][0] - sum_arr[left - 1][0];
      num_C = sum_arr[right][1] - sum_arr[left - 1][1];
      num_G = sum_arr[right][2] - sum_arr[left - 1][2];
      num_T = sum_arr[right][3] - sum_arr[left - 1][3];
    }

    if (num_A >= A && num_C >= C && num_G >= G && num_T >= T)
      result++;
  }

  printf("%d\n", result);

  // 동적 할당 해제
  for (int i = 0; i < S; i++)
    free(sum_arr[i]);

  free(sum_arr);
  free(str);
}