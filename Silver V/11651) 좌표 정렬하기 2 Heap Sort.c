#include <stdio.h>
#include <stdlib.h>

typedef struct _coord
{
    int x;
    int y;
} Coord;

void SwapCoord(Coord *a, Coord *b)
{
    Coord temp;
    temp.x = a->x, temp.y = a->y;

    a->x = b->x, a->y = b->y;
    b->x = temp.x, b->y = temp.y;
}

int main()
{
    int N;
    scanf("%d", &N);

    Coord *heap = (Coord *)malloc(sizeof(Coord) * (N + 1));

    // heap에 좌표 값 넣기
    for (int i = 1; i < N + 1; i++)
    {
        scanf("%d %d", &heap[i].x, &heap[i].y);

        // 이제 heap을 조건에 맞게 정렬하기
        int copy_i = i;
        while (copy_i > 1)
        {
            if (heap[copy_i].y < heap[copy_i / 2].y)
                SwapCoord(&heap[copy_i], &heap[copy_i / 2]);
            else if (heap[copy_i].y == heap[copy_i / 2].y)
            {
                if (heap[copy_i].x < heap[copy_i / 2].x)
                    SwapCoord(&heap[copy_i], &heap[copy_i / 2]);
                else
                    break;
            }
            else
                break;

            copy_i /= 2;
        }

        // printf("%d가 맨 뒤 노드일 때, ", i);
        // for (int j = 1; j <= i; j++)
        //     printf("(%d, %d) ", heap[j].x, heap[j].y);

        // printf("\n");
    }

    // heap에서 좌표 값 제거
    for (int i = N; i > 1; i--)
    {
        printf("%d %d\n", heap[1].x, heap[1].y);

        // 맨 뒤의 좌표를 루트로 이동
        SwapCoord(&heap[1], &heap[i]);

        // 다시 heap을 조건에 맞게 정렬
        int idx = 1;
        while (idx * 2 <= i - 1)
        {
            // 자식 노드가 하나인 경우
            if (idx * 2 == i - 1)
            {
                if (heap[idx * 2].y < heap[idx].y)
                    SwapCoord(&heap[idx * 2], &heap[idx]);
                else if (heap[idx * 2].y == heap[idx].y)
                {
                    if (heap[idx * 2].x < heap[idx].x)
                        SwapCoord(&heap[idx * 2], &heap[idx]);
                    else
                        break;
                }
                else
                    break;

                idx *= 2;
            }
            else // 자식 노드가 두 개인 경우
            {
                int child_idx;
                if (heap[idx * 2].y < heap[idx * 2 + 1].y)
                    child_idx = idx * 2;
                else if (heap[idx * 2].y > heap[idx * 2 + 1].y)
                    child_idx = idx * 2 + 1;
                else
                {
                    if (heap[idx * 2].x < heap[idx * 2 + 1].x)
                        child_idx = idx * 2;
                    else
                        child_idx = idx * 2 + 1;
                }

                if (heap[child_idx].y < heap[idx].y)
                    SwapCoord(&heap[child_idx], &heap[idx]);
                else if (heap[child_idx].y == heap[idx].y)
                {
                    if (heap[child_idx].x < heap[idx].x)
                        SwapCoord(&heap[child_idx], &heap[idx]);
                    else
                        break;
                }
                else
                    break;

                idx = child_idx;
            }
        }
    }

    printf("%d %d\n", heap[1].x, heap[1].y);

    // 메모리 해제
    free(heap);
    return 0;
}