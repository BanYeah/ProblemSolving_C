#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int sum; // 현재까지 총 점수
    struct _node *next;
} Node;

typedef struct _nodeList
{
    Node *count1; // 연속되게 밟은 계단의 수 1인 경우의 수의 모음
    Node *count2; // 연속되게 밟은 계단의 수 2인 경우의 수의 모음
} NodeList;

int main()
{
    int N;
    scanf("%d", &N);

    // i번 계단의 점수
    int *score = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        scanf("%d", &score[i]);

    // i번 계단을 밟은 경우의 수들을 저장하는 배열 (백트래킹을 위해)
    NodeList *arr = (NodeList *)malloc(sizeof(NodeList) * N);
    for (int i = 0; i < N; i++)
        arr[i].count1 = NULL, arr[i].count2 = NULL;

    // 초기값 세팅
    Node *newNode = (Node *)malloc(sizeof(Node));
    // 0번 계단을 밟은 경우
    newNode->sum = score[0];
    newNode->next = NULL;
    arr[0].count1 = newNode;

    // 0번을 건너뛰고 1번 계단을 밟은 경우
    newNode = (Node *)malloc(sizeof(Node));
    newNode->sum = score[1];
    newNode->next = NULL;
    arr[1].count1 = newNode;

    // 0번 계단을 밟은 상황부터 백트래킹을 진행하면서 N-1번 계단까지
    for (int i = 0; i < N; i++)
    {
        // i번 계단을 밟은 경우의 수들 중
        // count 값이 같은 경우의 수끼리 비교해서 점수 합의 최댓값만 남기기

        if (arr[i].count1 != NULL)
        {
            // printf("%d번 계단을 밟은 경우 중 count가 1인 경우: ", i);

            Node *cur = arr[i].count1;
            Node *next = arr[i].count1->next;
            while (next != NULL)
            {
                if (cur->sum >= next->sum)
                {
                    // printf("%d ", next->sum);
                    cur->next = next->next;
                    free(next);
                }
                else
                {
                    // printf("%d ", cur->sum);
                    arr[i].count1 = next;
                    free(cur);
                }

                // 다시 변수 재설정
                cur = arr[i].count1;
                next = arr[i].count1->next;
            }
            // printf("%d\n", arr[i].count1->sum);

            if (i + 2 < N) // 2 계단 더 오르기
            {
                newNode = (Node *)malloc(sizeof(Node));
                newNode->sum = arr[i].count1->sum + score[i + 2];

                newNode->next = arr[i + 2].count1;
                arr[i + 2].count1 = newNode;
            }
            if (i + 1 < N) // 1 계단 더 오르기
            {
                newNode = arr[i].count1;
                newNode->sum += score[i + 1];

                newNode->next = arr[i + 1].count2;
                arr[i + 1].count2 = newNode;
            }
        }

        if (arr[i].count2 != NULL)
        {
            // printf("%d번 계단을 밟은 경우 중 count가 2인 경우: ", i);

            Node *cur = arr[i].count2;
            Node *next = arr[i].count2->next;
            while (next != NULL)
            {
                if (cur->sum >= next->sum)
                {
                    // printf("%d ", next->sum);
                    cur->next = next->next;
                    free(next);
                }
                else
                {
                    // printf("%d ", cur->sum);
                    arr[i].count2 = next;
                    free(cur);
                }

                // 다시 변수 재설정
                cur = arr[i].count2;
                next = arr[i].count2->next;
            }
            // printf("%d\n", arr[i].count2->sum);

            if (i + 2 < N) // 2 계단 더 오르기
            {
                newNode = arr[i].count2;
                newNode->sum += score[i + 2];

                newNode->next = arr[i + 2].count1;
                arr[i + 2].count1 = newNode;
            }
            else if (i != N - 1)
                free(arr[i].count2);
        }
        // printf("\n");
    }

    // 총 점수의 최댓값 출력
    if (arr[N - 1].count1 != NULL && arr[N - 1].count2 != NULL)
    {
        if (arr[N - 1].count1->sum >= arr[N - 1].count2->sum)
            printf("%d\n", arr[N - 1].count1->sum);
        else
            printf("%d\n", arr[N - 1].count2->sum);

        free(arr[N - 1].count1);
        free(arr[N - 1].count2);
    }
    else if (arr[N - 1].count1 != NULL)
    {
        printf("%d\n", arr[N - 1].count1->sum);
        free(arr[N - 1].count1);
    }
    else
    {
        printf("%d\n", arr[N - 1].count2->sum);
        free(arr[N - 1].count2);
    }

    // 메모리 해제
    free(score);
    free(arr);
    return 0;
}