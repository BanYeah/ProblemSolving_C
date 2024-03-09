#include <stdio.h>
#include <stdlib.h>

int main()
{
    int K, N;
    scanf("%d %d", &K, &N);

    unsigned long long sum = 0;
    unsigned long *arr = (unsigned long *)malloc(sizeof(unsigned long) * K);
    for (int i = 0; i < K; i++)
    {
        scanf("%lu", &arr[i]);
        sum += arr[i];
    }

    unsigned long len = sum / N; // 랜선의 길이
    unsigned long gap = len;     // 이분 탐색을 위해...
    unsigned long max = -1;      // N개 이상 만들어 질 수 있는 랜선의 최대 길이
    unsigned long min = -1;      // N개 이상 만들어 질 수 없는 랜선의 최소 길이
    while (1)
    {
        // len의 길이로 만들어진 랜선의 개수 구하기
        int num = 0;
        for (int i = 0; i < K; i++)
            num += arr[i] / len;

        // gap이 1보다 큰 경우, 절반으로 줄임.
        if (gap > 1)
            gap /= 2;

        // 랜선이 N개 이상 만들어진 경우
        if (num >= N)
            max = len, len += gap;
        else
            min = len, len -= gap;

        if (max + 1 == min)
            break;
    }

    printf("%lu\n", max);

    free(arr);

    return 0;
}