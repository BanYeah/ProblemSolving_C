#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N;
    scanf("%d", &N);

    int num_10 = 0, num_5 = 0, num_2 = 0;
    for (int i = 1; i <= N; i++)
    {
        int copy_i = i;
        // 10으로 나누어 떨어지는지 확인
        while (copy_i > 0 && copy_i % 10 == 0)
        {
            num_10++;
            copy_i /= 10;
        }

        // 5로 나누어 떨어지는지 확인
        while (copy_i > 0 && copy_i % 5 == 0)
        {
            num_5++;
            copy_i /= 5;
        }

        // 2로 나누어 떨어지는지 확인
        while (copy_i > 0 && copy_i % 2 == 0)
        {
            num_2++;
            copy_i /= 2;
        }
    }

    printf("%d\n", num_10 + (num_2 < num_5 ? num_2 : num_5));
    return 0;
}