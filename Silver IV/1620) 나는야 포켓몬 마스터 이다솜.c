#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node
{
    int num;
    char str[21];
} Node;

void Swap(Node *a, Node *b)
{
    Node temp;
    temp.num = a->num;
    strcpy(temp.str, a->str);

    a->num = b->num;
    strcpy(a->str, b->str);

    b->num = temp.num;
    strcpy(b->str, temp.str);
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    // 포켓몬 이름 정렬을 위한 Heap 선언
    Node *heap = (Node *)malloc(sizeof(Node) * (N + 1));

    char **arr = (char **)malloc(sizeof(char *) * N);
    for (int i = 0; i < N; i++)
    {
        arr[i] = (char *)malloc(sizeof(char) * 21);
        scanf("%s", arr[i]);

        // Heap Insertion
        int idx = i + 1;
        heap[idx].num = i + 1;
        strcpy(heap[idx].str, arr[i]);

        // 부모와 비교하면서 위치 변경
        while (idx / 2 >= 1)
        {
            // heap[idx / 2].str이 heap[idx].str보다 큰 경우 -> min heap
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
    Node *sorted_arr = (Node *)malloc(sizeof(Node) * N);
    for (int i = 0; i < N; i++)
    {
        // Root 노드를 제거
        sorted_arr[i].num = heap[1].num;
        strcpy(sorted_arr[i].str, heap[1].str);

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

    // M개의 문제
    for (int i = 0; i < M; i++)
    {
        char str[21];
        scanf("%s", str);

        // atoi()는 인자가 정수로 변환되지 않는 경우, 0 반환
        int num = atoi(str);
        if (num)
            printf("%s\n", arr[num - 1]); // num을 인덱스로 접근해서 출력
        else
        {
            // binary search로 주어진 문자열 찾기
            int idx = N / 2, start = 0, end = N;

            while (strcmp(str, sorted_arr[idx].str) != 0)
            {
                if (strcmp(str, sorted_arr[idx].str) < 0)
                    end = idx;
                else
                    start = idx;

                idx = (start + end) / 2;
            }

            printf("%d\n", sorted_arr[idx].num);
        }
    }

    // 메모리 해제
    free(heap);
    free(sorted_arr);

    for (int i = 0; i < N; i++)
        free(arr[i]);
    free(arr);

    return 0;
}