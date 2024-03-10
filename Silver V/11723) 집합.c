#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int M;
    scanf("%d", &M);

    int set[21] = {0};

    for (int i = 0; i < M; i++)
    {
        char cmd[7];
        int x;
        scanf("%s", cmd);

        if (strcmp("all", cmd) == 0)
        {
            for (int j = 1; j <= 20; j++)
                set[j] = 1;
        }
        else if (strcmp("empty", cmd) == 0)
        {
            for (int j = 1; j <= 20; j++)
                set[j] = 0;
        }
        else
        {
            scanf("%d", &x);
            if (strcmp("add", cmd) == 0)
                set[x] = 1;
            else if (strcmp("remove", cmd) == 0)
                set[x] = 0;
            else if (strcmp("check", cmd) == 0)
            {
                if (set[x] == 1)
                    printf("1\n");
                else
                    printf("0\n");
            }
            else
                set[x] = set[x] == 0 ? 1 : 0;
        }
    }

    return 0;
}