#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int vertex;
    struct _node *next;
} Node;

int main()
{
    int V, E;
    scanf("%d", &V); // 정점의 수
    scanf("%d", &E); // 간선의 수

    Node **linkedList = (Node **)malloc(sizeof(Node *) * (V + 1));
    for (int i = 0; i <= V; i++)
        linkedList[i] = NULL;

    // graph 생성
    for (int i = 0; i < E; i++)
    {
        int v, u;
        scanf("%d %d", &v, &u);

        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->vertex = u;
        newNode->next = linkedList[v];
        linkedList[v] = newNode;

        newNode = (Node *)malloc(sizeof(Node));
        newNode->vertex = v;
        newNode->next = linkedList[u];
        linkedList[u] = newNode;
    }

    // connected 여부 확인
    int *visited = (int *)malloc(sizeof(int) * (V + 1));
    for (int i = 0; i <= V; i++)
        visited[i] = 0;
    visited[1] = 1;

    // DFS용 stack 생성
    Node *stack = NULL;
    Node *cur = linkedList[1];
    while (cur != NULL)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->vertex = cur->vertex;
        newNode->next = stack;
        stack = newNode;

        cur = cur->next;
    }

    while (stack != NULL)
    {
        int num = stack->vertex;
        cur = stack;
        stack = stack->next;
        free(cur);

        if (visited[num] != 1)
        {
            visited[num] = 1;

            cur = linkedList[num];
            while (cur != NULL)
            {
                if (visited[cur->vertex] == 1)
                {
                    cur = cur->next;
                    continue;
                }

                Node *newNode = (Node *)malloc(sizeof(Node));
                newNode->vertex = cur->vertex;
                newNode->next = stack;
                stack = newNode;

                cur = cur->next;
            }
        }
    }

    // 결과 출력
    int sum = 0;
    for (int i = 2; i <= V; i++)
    {
        if (visited[i] == 1)
            sum++;
    }

    printf("%d\n", sum);

    // 메모리 해제
    for (int i = 1; i <= V; i++)
    {
        while (linkedList[i] != NULL)
        {
            Node *temp = linkedList[i];
            linkedList[i] = linkedList[i]->next;
            free(temp);
        }
    }
    free(linkedList);

    return 0;
}