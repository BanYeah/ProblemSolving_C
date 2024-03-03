#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
  int vertex;
  struct _node *next;
} Node;

int main()
{
  int N, M;
  scanf("%d %d", &N, &M);

  //  N개의 정점 생성
  Node **vertices = (Node **)malloc(sizeof(Node *) * (N + 1));
  for (int i = 0; i < N + 1; i++)
    vertices[i] = NULL;

  // M개의 간선 생성
  for (int i = 0; i < M; i++)
  {
    int u, v;
    scanf("%d %d", &u, &v);

    // 정점 u에 간선 추가
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->vertex = v, temp->next = vertices[u];
    vertices[u] = temp;

    // 정점 v에 간선 추가
    temp = (Node *)malloc(sizeof(Node));
    temp->vertex = u, temp->next = vertices[v];
    vertices[v] = temp;
  }

  // 여기까지는 문제 없음!!

  // 연결 요소의 개수
  int connected_components = 0;

  // 정점 방문 여부 확인용 배열 생성
  int total_visited = 0;
  int *visited = (int *)malloc(sizeof(int) * (N + 1));
  for (int i = 0; i < N + 1; i++)
    visited[i] = 0;

  // DFS로 연결 요소의 개수 확인
  while (total_visited != N)
  {
    // DFS 구현을 위한 스택 생성
    Node *stack = NULL;
    connected_components++;

    // 연결 요소의 시작 노드 탐색
    int visit_node;
    for (int i = 1; i < N + 1; i++)
    {
      if (visited[i] == 0)
      {
        visit_node = i, visited[i] = 1;
        total_visited++;
        break;
      }
    }

    while (1)
    {
      // 현재 탐색 중인 노드
      Node *cur = vertices[visit_node];
      while (cur != NULL)
      {
        // vertices[visit_node]에 있는 node들을 모두 stack에 추가
        Node *temp = (Node *)malloc(sizeof(Node));
        temp->vertex = cur->vertex;
        temp->next = stack;

        stack = temp;
        cur = cur->next;
      }

      // 새로 탐색할 노드 탐색
      int is_change_visit = 0;
      while (stack != NULL)
      {
        if (visited[stack->vertex] == 0)
        {
          visit_node = stack->vertex;
          visited[visit_node] = 1;
          total_visited++;

          is_change_visit = 1;
        }

        Node *temp = stack;
        stack = stack->next;

        free(temp);

        if (is_change_visit)
          break;
      }

      if (is_change_visit == 0)
        break;
    }
  }

  // 결과 출력
  printf("%d\n", connected_components);

  // 메모리 해제
  free(visited);

  for (int i = 1; i < N + 1; i++)
  {
    while (vertices[i] != NULL)
    {
      Node *temp = vertices[i];
      vertices[i] = vertices[i]->next;

      free(temp);
    }
  }

  free(vertices);
}