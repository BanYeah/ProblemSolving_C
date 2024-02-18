#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N;
    scanf("%d", &N);

    if (N == 1)
    {
        printf("%d\n", 666);
        return 0;
    }

    int collapse_num = 1;
    int i = 667;
    while (collapse_num != N)
    {
        // i에서 세 번 연속으로 6이 등장하는지 여부 확인
        int continuous = 0, copy_i = i;
        while (copy_i > 0 && continuous < 3)
        {
            if (copy_i % 10 == 6)
                continuous++;
            else
                continuous = 0;

            copy_i /= 10;
        }
        if (continuous >= 3)
            collapse_num++;

        i++;
    }

    printf("%d\n", i - 1);

    return 0;
}