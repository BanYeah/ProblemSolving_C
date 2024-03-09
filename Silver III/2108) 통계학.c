#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N;
    scanf("%d", &N);

    int sum = 0; // -> 산술평균

    int *arr = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }

    // 산술 평균 출력
    double average = (double)sum / N;
    printf("%.0f\n", (-0.5 < average && average < 0) ? 0 : average);

    // merge sort
    // -> 중앙값은 N/2 인덱스에 위치한 값
    // -> 최빈값은 순회하면서 탐색!
    // -> 범위는 최대값 - 최소값
    for (int size = 1; size < N; size *= 2)
    {
        for (int start = 0; start + size < N; start += size * 2)
        {
            int l = start, r = start + size, idx = 0;
            int max_r = (start + size * 2 <= N ? start + size * 2 : N);

            int *sorted_arr = (int *)malloc(sizeof(int) * size * 2);

            while (l < start + size && r < max_r)
            {
                if (arr[l] < arr[r])
                {
                    sorted_arr[idx] = arr[l];
                    l++, idx++;
                }
                else
                {
                    sorted_arr[idx] = arr[r];
                    r++, idx++;
                }
            }

            while (l < start + size)
            {
                sorted_arr[idx] = arr[l];
                l++, idx++;
            }

            while (r < max_r)
            {
                sorted_arr[idx] = arr[r];
                r++, idx++;
            }

            for (int i = 0; i < idx; i++)
                arr[start + i] = sorted_arr[i];

            free(sorted_arr);
        }
    }

    // 중앙값 출력
    printf("%d\n", arr[N / 2]);

    // 최빈값 출력
    int num = arr[0], num_count = 1, order = 1;
    for (int i = 0; i < N; i++)
    {
        int cur_count = 1;
        while (i < N - 1 && arr[i] == arr[i + 1])
        {
            cur_count++;
            i++;
        }

        if (num_count < cur_count)
        {
            num = arr[i], num_count = cur_count;
            order = 1;
        }
        else if (i != 0 && order == 1 && num_count == cur_count)
        {
            num = arr[i];
            order = 2;
        }
    }
    printf("%d\n", num);

    // 범위 출력
    printf("%d\n", arr[N - 1] - arr[0]);

    free(arr);
    return 0;
}