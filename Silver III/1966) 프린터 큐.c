#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int main()
{
    int T;
    scanf("%d", &T);

    // 각 테스트 케이스를 반복
    for (int t = 0; t < T; t++)
    {
        int N, M;
        scanf("%d %d", &N, &M);

        // 각 문서의 중요도 입력 받기
        int document[MAX_SIZE];
        for (int i = 0; i < N; i++)
            scanf("%d", &document[i]);

        // 중요도 9부터 1까지 문서 순회
        int start = 0, cur = 0, prev = 0;
        int count = 0;
        for (int p = 9; p >= 1; p--)
        {
            do
            {
                // 중요도가 가장 높으면서 M번째 문서인 경우
                if (document[cur] == p && cur == M) {
                    printf("%d\n", ++count);
                    p = 0;
                    break;
                }
                else if (document[cur] == p)
                {
                    document[cur] = -1;
                    count++;

                    prev = cur;
                }

                if (cur == N - 1)
                    cur = 0;
                else
                    cur++;
            } while (start != cur);

            start = prev;
            cur = prev;
        }
    }

    return 0;
}