#include <stdio.h>
#include <stdlib.h>

// n은 11보다 작다
int PRECAL[12] = {0};

int CaseNum(int n)
{
    // 이전에 계산한 경우
    if (PRECAL[n] != 0)
        return PRECAL[n];

    int result = 0;

    // 그냥 for문 막 써 버리기...?
    for (int thr = n / 3; thr >= 0; thr--)
    {
        for (int two = (n - 3 * thr) / 2; two >= 0; two--)
        {
            int one = n - 3 * thr - 2 * two;

            int num = thr + two + one; // 피연산자 개수
            int numerator = 1;         // 분자
            int denominator = 1;       // 분모

            // 분자 구하기: num!
            for (int i = num; i >= 2; i--)
                numerator *= i;

            // 분모 구하기: thr! * two! * one!
            for (int i = thr; i >= 2; i--)
                denominator *= i;
            for (int i = two; i >= 2; i--)
                denominator *= i;
            for (int i = one; i >= 2; i--)
                denominator *= i;

            result += numerator / denominator;
        }
    }

    PRECAL[n] = result;

    return result;
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int i = 0; i < T; i++)
    {
        int n;
        scanf("%d", &n);
        printf("%d\n", CaseNum(n));
    }

    return 0;
}