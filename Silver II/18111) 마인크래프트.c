#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, M, B;
    scanf("%d %d %d", &N, &M, &B);

    int sum = 0;

    // 집터의 블럭 높이 입력 받기
    int *block = (int *)malloc(sizeof(int) * N * M);
    for (int i = 0; i < N * M; i++)
    {
        scanf("%d", &block[i]);
        sum += block[i];
    }

    // 블록의 평균 높이 구하기
    int height = sum / (N * M);

    // 평균 높이로 블록의 높이를 통일하기(땅 고르기)
    int time = 0;
    for (int i = 0; i < N * M; i++)
    {
        if (block[i] < height)
        {
            B -= height - block[i];    // 인벤토리에서 블럭 꺼내기
            time += height - block[i]; // 블럭 설치하기
        }
        else if (block[i] > height)
        {
            time += (block[i] - height) * 2; // 블럭 제거하기
            B += block[i] - height;          // 인벤토리에 블럭 넣기
        }
    }

    int saved_time = time;

    // 통일할 블럭의 높이를 1씩 증가시키면서 최소 시간인지 여부 확인
    int flag = 1;
    while (flag)
    {
        height++;

        // 땅 고르기
        for (int i = 0; i < N * M; i++)
        {
            // 인벤토리가 빈 경우
            if (B == 0)
            {
                flag = 0;
                break;
            }
            B--; // 인벤토리에서 블럭 제거

            if (block[i] < height)
                time++; // 블럭 설치하기
            else if (block[i] >= height)
                time -= 2; // 블럭을 제거하지 않았다고 가정
        }

        if (flag == 0 || height > 256)
            break;
        else if (time >= 0 && saved_time >= time)
            saved_time = time;
        else
            break;
    }

    printf("%d %d\n", saved_time, height - 1);

    // 메모리 해제
    free(block);

    return 0;
}