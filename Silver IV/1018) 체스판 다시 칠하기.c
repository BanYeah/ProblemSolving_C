#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    int min = 64;
    char dummy1[] = {'W', 'B', 'W', 'B', 'W', 'B', 'W', 'B'};
    char dummy2[] = {'B', 'W', 'B', 'W', 'B', 'W', 'B', 'W'};

    char **chess_board = (char **)malloc(sizeof(char *) * N);
    for (int i = 0; i < N; i++)
        chess_board[i] = (char *)malloc(sizeof(char) * M);

    // 체스판 입력 받기
    for (int i = 0; i < N; i++)
    {
        // 문자열을 입력 받기
        char *str = (char *)malloc(sizeof(char) * (M + 1));
        scanf("%s", str);

        for (int j = 0; j < M; j++)
            chess_board[i][j] = str[j];

        free(str);
    }

    // 다시 칠해야하는 정사각형의 최소 개수 구하기
    // 이때, 최솟값이 0이 나온 경우 바로 프로그램 종료
    for (int i = 7; i < N; i++)
    {
        for (int j = 7; j < M; j++)
        {
            // 8*8 정사각형의 다시 칠해야하는 개수 확인
            int flag = 0;
            int wrong = 0;
            for (int ii = i - 7; ii <= i; ii++)
            {
                for (int jj = j - 7, idx = 0; jj <= j; jj++, idx++)
                {
                    if (flag)
                    {
                        if (dummy2[idx] != chess_board[ii][jj])
                            wrong++;
                    }
                    else
                    {
                        if (dummy1[idx] != chess_board[ii][jj])
                            wrong++;
                    }
                }
                flag = flag ? 0 : 1;
            }

            wrong = wrong <= 32 ? wrong : 64 - wrong;
            if (wrong == 0)
            {
                printf("%d\n", 0);

                // 메모리 해제
                for (int i = 0; i < N; i++)
                    free(chess_board[i]);

                free(chess_board);

                return 0;
            }
            else if (wrong < min)
                min = wrong;
        }
    }

    // 결과 출력
    printf("%d\n", min);

    // 메모리 해제
    for (int i = 0; i < N; i++)
        free(chess_board[i]);

    free(chess_board);

    return 0;
}