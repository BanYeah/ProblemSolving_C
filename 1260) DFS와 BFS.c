#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int vertex;
    struct _node *next;
} Node;

int main()
{
    int N, M, V;
    scanf("%d %d %d", &N, &M, &V);

    // 인접 매트릭스 생성 및 초기화
    char **adjacency_matrix = (char **)malloc(sizeof(char *) * (N + 1));
    for (int i = 1; i < N + 1; i++)
    {
        adjacency_matrix[i] = (char *)malloc(sizeof(char) * (N + 1));
        for (int j = 1; j < N + 1; j++)
            adjacency_matrix[i][j] = 0;
    }

    // 간선 입력 받기
    for (int i = 0; i < M; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        adjacency_matrix[u][v] = 1;
        adjacency_matrix[v][u] = 1;
    }

    char *visited = (char *)malloc(sizeof(char) * (N + 1));
    for (int i = 1; i < N + 1; i++)
        visited[i] = 0;

    // DFS 수행
    Node *stack = NULL;

    int visit_vertex = V;
    visited[V] = 1;
    printf("%d ", V);

    for (int i = N; i > 0; i--)
    {
        // 간선이 존재하면서 방문한 적이 없는 경우
        if (adjacency_matrix[V][i] == 1 && visited[i] == 0)
        {
            // stack에 노드 추가
            Node *temp = (Node *)malloc(sizeof(Node));
            temp->vertex = i, temp->next = stack;
            stack = temp;
        }
    }

    while (stack != NULL)
    {
        visit_vertex = stack->vertex;

        // stack에서 노드 제거
        Node *temp = stack;
        stack = stack->next;

        free(temp);

        // 방문한 적이 있는 경우
        if (visited[visit_vertex] == 1)
            continue;

        visited[visit_vertex] = 1;
        printf("%d ", visit_vertex);

        for (int i = N; i > 0; i--)
        {
            // 간선이 존재하면서 방문한 적이 없는 경우
            if (adjacency_matrix[visit_vertex][i] == 1 && visited[i] == 0)
            {
                // stack에 노드 추가
                Node *temp = (Node *)malloc(sizeof(Node));
                temp->vertex = i, temp->next = stack;
                stack = temp;
            }
        }
    }
    printf("\n");

    // BFS 수행
    // visit 배열 초기화
    for (int i = 1; i < N + 1; i++)
        visited[i] = 0;

    Node *queue_front = NULL, *queue_rear = NULL;

    visit_vertex = V;
    visited[V] = 1;
    printf("%d ", V);

    for (int i = 1; i < N + 1; i++)
    {
        // 간선이 존재하면서 방문한 적이 없는 경우
        if (adjacency_matrix[V][i] == 1 && visited[i] == 0)
        {
            // queue에 노드 추가
            Node *temp = (Node *)malloc(sizeof(Node));
            temp->vertex = i, temp->next = NULL;

            if (queue_front == NULL && queue_rear == NULL)
                queue_front = temp, queue_rear = temp;
            else
            {
                queue_rear->next = temp;
                queue_rear = temp;
            }
        }
    }

    while (queue_front != NULL)
    {
        visit_vertex = queue_front->vertex;

        // queue에서 노드 제거
        Node *temp = queue_front;
        if (queue_front->next == NULL)
            queue_front = NULL, queue_rear = NULL;
        else
            queue_front = queue_front->next;

        free(temp);

        // 방문한 적이 있는 경우
        if (visited[visit_vertex] == 1)
            continue;

        visited[visit_vertex] = 1;
        printf("%d ", visit_vertex);

        for (int i = 1; i < N + 1; i++)
        {
            // 간선이 존재하면서 방문한 적이 없는 경우
            if (adjacency_matrix[visit_vertex][i] == 1 && visited[i] == 0)
            {
                // queue에 노드 추가
                Node *temp = (Node *)malloc(sizeof(Node));
                temp->vertex = i, temp->next = NULL;

                if (queue_front == NULL && queue_rear == NULL)
                    queue_front = temp, queue_rear = temp;
                else
                {
                    queue_rear->next = temp;
                    queue_rear = temp;
                }
            }
        }
    }
    printf("\n");

    // 메모리 해제
    free(visited);

    for (int i = 1; i < N + 1; i++)
        free(adjacency_matrix[i]);

    free(adjacency_matrix);

    return 0;
}