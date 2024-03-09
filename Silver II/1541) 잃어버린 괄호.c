#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char exp[51];
    scanf("%s", exp);

    int result = 0, flag = 0, num = 0;
    char op = 0;
    for (int i = 0; i < strlen(exp); i++)
    {
        if ('0' <= exp[i] && exp[i] <= '9')
        {
            num *= 10;
            num += exp[i] - '0';
            continue;
        }

        if (op == 0)
            result = num;
        else if (op == '+')
        {
            if (flag)
                result -= num;
            else
                result += num;
        }
        else
        {
            flag = 1;
            result -= num;
        }
        op = exp[i];
        num = 0;
    }

    // 마지막 숫자 처리
    if (op == 0)
        result = num;
    else if (op == '+')
    {
        if (flag)
            result -= num;
        else
            result += num;
    }
    else
    {
        flag = 1;
        result -= num;
    }

    printf("%d\n", result);

    return 0;
}