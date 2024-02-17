#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int frd;
    struct _node *next;
} Node;

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    //  N명의 사람 생성
    Node **people = (Node **)malloc(sizeof(Node *) * N);
    for (int i = 0; i < N; i++)
        people[i] = NULL;

    // M개의 친구 관계 생성
    for (int i = 0; i < M; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        // 사람 u에 친구 관계 추가
        Node *temp = (Node *)malloc(sizeof(Node));
        temp->frd = v, temp->next = people[u];
        people[u] = temp;

        // 사람 v에 친구 관계 추가
        temp = (Node *)malloc(sizeof(Node));
        temp->frd = u, temp->next = people[v];
        people[v] = temp;
    }

    // 연속된 4개의 친구 관계 존재 여부
    int is_correct = 0;

    // 0번 사람부터 N-1번 사람까지 순회
    for (int person = 0; person < N; person++)
    {
        // DFS 구현을 위한 스택 생성
        Node *stack = NULL;

        int continuous_friends = 0;
        int visit_people[5] = {person, -1, -1, -1, -1};

        int visit_person = person;

        while (1)
        {
            // 현재 방문한 사람
            Node *cur = people[visit_person];

            // 백트래킹 여부 확인을 위해, -1인 node를 stack에 추가
            Node *temp = (Node *)malloc(sizeof(Node));
            temp->frd = -1, temp->next = stack;
            stack = temp;

            while (cur != NULL)
            {
                // people[visit_person]에 있는 node들을 모두 stack에 추가
                Node *temp = (Node *)malloc(sizeof(Node));
                temp->frd = cur->frd;
                temp->next = stack;

                stack = temp;
                cur = cur->next;
            }

            // 새로 방문할 사람 탐색
            while (stack != NULL)
            {
                int flag = 0;

                int next_person = stack->frd;
                if (next_person == -1)
                {
                    visit_people[continuous_friends] = -1;
                    continuous_friends--;

                    flag = 1;
                }
                else
                {
                    for (int i = 0; i < continuous_friends + 1; i++)
                    {
                        // 이미 방문한 경우
                        if (visit_people[i] == next_person)
                        {
                            flag = 1;
                            break;
                        }
                    }
                }

                // stack에서 제거
                Node *temp = stack;
                stack = stack->next;

                free(temp);

                // stack에서 -1를 만난 경우나 이미 방문한 경우
                if (flag)
                    continue;

                continuous_friends++;
                visit_people[continuous_friends] = next_person;
                visit_person = next_person;
                break;
            }

            if (stack == NULL || continuous_friends == 4)
                break;
        }

        if (continuous_friends == 4)
        {
            is_correct = 1;

            // 메모리 해제
            while (stack != NULL)
            {
                Node *temp = stack;
                stack = stack->next;

                free(temp);
            }

            break;
        }
    }

    // 결과 출력
    if (is_correct)
        printf("1\n");
    else
        printf("0\n");

    // 메모리 해제
    for (int i = 0; i < N; i++)
    {
        while (people[i] != NULL)
        {
            Node *temp = people[i];
            people[i] = people[i]->next;

            free(temp);
        }
    }

    free(people);
}