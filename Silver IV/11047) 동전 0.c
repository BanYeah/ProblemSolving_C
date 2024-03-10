#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, K;
    scanf("%d %d", &N, &K);

    int *value = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        scanf("%d", &value[i]);

    int num = 0;

    int target = N / 2;
    if (K / value[N - 1] > 0) // binary search가 필요 X
        target = N - 1;
    else
    {
        // binary search
        int start = 0, end = N;
        while (1)
        {
            if (target == N - 1)
                break;

            if (K / value[target] > 0 && K / value[target + 1] == 0)
                break;
            else if (K / value[target] == 0)
                end = target;
            else
                start = target;

            target = (start + end) / 2;
        }
    }

    while (K != 0)
    {
        num += K / value[target];
        K %= value[target];

        target--;
    }

    printf("%d\n", num);

    return 0;
}