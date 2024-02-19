#include <stdio.h>
#include <stdlib.h>

void Cpy(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

int main()
{
    int N;
    scanf("%d", &N);

    if (N == 0)
    {
        printf("%d\n", 0);
        return 0;
    }

    int trunc;
    // 반올림 값 구하기 (사사오입 주의!!)
    double temp = (double)N / 100 * 15;
    if ((int)(temp * 10) % 10 >= 5)
        trunc = (int)temp + 1;
    else
        trunc = (int)temp;

    char *arr = (char *)malloc(sizeof(char) * N);
    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);

    // merge sort
    int size = 1;
    while (size < N)
    {
        for (int i = 0; i + size < N; i += size * 2)
        {
            int l = i, r = i + size, idx = 0;
            char *sorted_arr = (char *)malloc(sizeof(char) * (size * 2));

            int max_r = i + size * 2 < N ? i + size * 2 : N;
            while (l < i + size && r < max_r)
            {
                if (arr[l] < arr[r])
                {
                    Cpy(&sorted_arr[idx], &arr[l]);
                    l++;
                }
                else
                {
                    Cpy(&sorted_arr[idx], &arr[r]);
                    r++;
                }
                idx++;
            }

            while (l < i + size)
            {
                Cpy(&sorted_arr[idx], &arr[l]);
                l++, idx++;
            }

            while (r < max_r)
            {
                Cpy(&sorted_arr[idx], &arr[r]);
                r++, idx++;
            }

            idx = i;
            for (; idx < max_r; idx++)
                Cpy(&arr[idx], &sorted_arr[idx - i]);

            free(sorted_arr);
        }

        size *= 2;
    }

    int sum = 0;
    for (int i = trunc; i < N - trunc; i++)
        sum += arr[i];

    // 반올림 값 구하기 (사사오입 주의!!)
    temp = (double)sum / (N - 2 * trunc);
    if ((int)(temp * 10) % 10 >= 5)
        sum = (int)temp + 1;
    else
        sum = (int)temp;

    printf("%d\n", sum);

    free(arr);
    return 0;
}