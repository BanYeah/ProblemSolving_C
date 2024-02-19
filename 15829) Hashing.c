#include <stdio.h>
#include <stdlib.h>

#define r 31
#define M 1234567891 // 12억

int main()
{
    int L;
    scanf("%d", &L);

    char *str = (char *)malloc(sizeof(char) * (L + 1));
    scanf("%s", str);

    // Hashing
    unsigned long long result = str[0] - 'a' + 1; // a0

    // 각 자리 숫자를 순회 (a1 ~ aL-1)
    for (int i = 1; i < L; i++)
    {
        unsigned long long mod_result = str[i] - 'a' + 1; // ai

        for (int j = 0; j < i; j++)
            mod_result = ((mod_result % M) * r) % M;

        result = ((result % M) + (mod_result % M)) % M;
    }

    printf("%llu\n", result);

    free(str);
    return 0;
}