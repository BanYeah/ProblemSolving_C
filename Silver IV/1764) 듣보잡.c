#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _string
{
    char str[21];
} String;

void Swap(String *a, String *b)
{
    String temp;
    strcpy(temp.str, a->str);
    strcpy(a->str, b->str);
    strcpy(b->str, temp.str);
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    // 듣도 못한 사람의 이름 정렬을 위한 Heap 선언
    String *heap = (String *)malloc(sizeof(String) * (N + 1));

    // Heap Insertion
    for (int i = 0; i < N; i++)
    {
        int idx = i + 1;
        scanf("%s", heap[idx].str);

        // 부모와 비교하면서 위치 변경
        while (idx / 2 >= 1)
        {
            if (strcmp(heap[idx / 2].str, heap[idx].str) > 0)
            {
                Swap(&heap[idx / 2], &heap[idx]);
                idx /= 2;
            }
            else
                break;
        }
    }

    // Heap Deletion
    String *not_heard = (String *)malloc(sizeof(String) * N);
    for (int i = 0; i < N; i++)
    {
        // Root 노드를 제거
        strcpy(not_heard[i].str, heap[1].str);

        // 마지막 노드를 Root로 이동
        Swap(&heap[1], &heap[N - i]);

        // 자식과 비교하면서 위치 변경
        int idx = 1, max = N - i - 1;
        while (idx * 2 <= max)
        {
            // 자식이 하나인 경우 or 왼쪽 자식이 더 작은 경우
            if (idx * 2 == max || strcmp(heap[idx * 2].str, heap[idx * 2 + 1].str) < 0)
            {
                if (strcmp(heap[idx].str, heap[idx * 2].str) > 0)
                {
                    Swap(&heap[idx], &heap[idx * 2]);
                    idx *= 2;
                }
                else
                    break;
            }
            else
            {
                if (strcmp(heap[idx].str, heap[idx * 2 + 1].str) > 0)
                {
                    Swap(&heap[idx], &heap[idx * 2 + 1]);
                    idx = idx * 2 + 1;
                }
                else
                    break;
            }
        }
    }
    // 메모리 해제
    free(heap);

    // 듣도 보도 못한 사람의 이름 정렬
    int num = 0;
    String *not_heard_seen = (String *)malloc(sizeof(String) * (N < M ? N + 1 : M + 1));

    // 보도 못한 사람 입력 받기
    for (int i = 0; i < M; i++)
    {
        char str[21];
        scanf("%s", str);

        // binary search
        int target = N / 2;
        int start = 0, end = N;

        while (start != end - 1 && strcmp(str, not_heard[target].str) != 0)
        {
            if (strcmp(str, not_heard[target].str) < 0)
                end = target;
            else
                start = target;
            target = (start + end) / 2;
        }

        if (strcmp(str, not_heard[target].str) == 0)
        {
            // Heap Insertion
            num++;
            strcpy(not_heard_seen[num].str, not_heard[target].str);

            // 부모와 비교하면서 위치 변경
            int idx = num;
            while (idx / 2 >= 1)
            {
                if (strcmp(not_heard_seen[idx / 2].str, not_heard_seen[idx].str) > 0)
                {
                    Swap(&not_heard_seen[idx / 2], &not_heard_seen[idx]);
                    idx /= 2;
                }
                else
                    break;
            }
        }
    }

    printf("%d\n", num);

    // Heap Deletion
    for (int i = 0; i < num; i++)
    {
        // Root 노드를 제거
        printf("%s\n", not_heard_seen[1].str);

        // 마지막 노드를 Root로 이동
        Swap(&not_heard_seen[1], &not_heard_seen[num - i]);

        // 자식과 비교하면서 위치 변경
        int idx = 1, max = num - i - 1;
        while (idx * 2 <= max)
        {
            // 자식이 하나인 경우 or 왼쪽 자식이 더 작은 경우
            if (idx * 2 == max || strcmp(not_heard_seen[idx * 2].str, not_heard_seen[idx * 2 + 1].str) < 0)
            {
                if (strcmp(not_heard_seen[idx].str, not_heard_seen[idx * 2].str) > 0)
                {
                    Swap(&not_heard_seen[idx], &not_heard_seen[idx * 2]);
                    idx *= 2;
                }
                else
                    break;
            }
            else
            {
                if (strcmp(not_heard_seen[idx].str, not_heard_seen[idx * 2 + 1].str) > 0)
                {
                    Swap(&not_heard_seen[idx], &not_heard_seen[idx * 2 + 1]);
                    idx = idx * 2 + 1;
                }
                else
                    break;
            }
        }
    }

    // 메모리 해제
    free(not_heard_seen);
    free(not_heard);

    return 0;
}