#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    // 동적 할당
    int *arr = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);

    // Merge Sort
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

    for (int i = 0; i < N; i++)
        printf("%d\n", arr[i]);

    // 동적 할당 해제
    free(arr);
    return 0;
}