#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int zero;
    int one;
} Node;

int main()
{
    int T;
    scanf("%d", &T);

    Node arr[41];

    // n이 0일 때
    arr[0].zero = 1;
    arr[0].one = 0;

    // n이 1일 때
    arr[1].zero = 0;
    arr[1].one = 1;

    for (int i = 2; i < 41; i++)
    {
        arr[i].zero = arr[i - 1].zero + arr[i - 2].zero;
        arr[i].one = arr[i - 1].one + arr[i - 2].one;
    }

    for (int i = 0; i < T; i++)
    {
        int N;
        scanf("%d", &N);

        printf("%d %d\n", arr[N].zero, arr[N].one);
    }

    return 0;
}