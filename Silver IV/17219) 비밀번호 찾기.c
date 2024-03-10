#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node
{
    char site[21];
    char pw[21];
} Node;

void Cpy(Node *a, Node *b)
{
    strcpy(a->site, b->site);
    strcpy(a->pw, b->pw);
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    Node *arr = (Node *)malloc(sizeof(Node) * N);
    for (int i = 0; i < N; i++)
        scanf("%s %s", arr[i].site, arr[i].pw);

    // merge sort
    for (int size = 1; size < N; size *= 2)
    {
        for (int start = 0; start < N && start + size < N; start += size * 2)
        {
            int l = start, r = start + size, idx = 0;
            int end = start + (size * 2) < N ? start + (size * 2) : N;

            Node *sorted_arr = (Node *)malloc(sizeof(Node) * size * 2);
            while (l < start + size && r < end)
            {
                if (strcmp(arr[l].site, arr[r].site) < 0)
                {
                    Cpy(&sorted_arr[idx], &arr[l]);
                    l++, idx++;
                }
                else
                {
                    Cpy(&sorted_arr[idx], &arr[r]);
                    r++, idx++;
                }
            }

            while (l < start + size)
            {
                Cpy(&sorted_arr[idx], &arr[l]);
                l++, idx++;
            }
            while (r < end)
            {
                Cpy(&sorted_arr[idx], &arr[r]);
                r++, idx++;
            }

            for (int i = 0; i < idx; i++)
                Cpy(&arr[start + i], &sorted_arr[i]);

            free(sorted_arr);
        }
    }

    // printf("정렬 결과:\n");
    // for (int i = 0; i < N; i++)
    //     printf("%s\n", arr[i]);

    // 비밀번호 찾기
    for (int i = 0; i < M; i++)
    {
        char site[21];
        scanf("%s", site);

        // binary search
        int start = 0, end = N, target = N / 2;
        while (strcmp(site, arr[target].site) != 0)
        {
            if (strcmp(site, arr[target].site) < 0)
                end = target;
            else
                start = target;

            target = (start + end) / 2;
        }

        printf("%s\n", arr[target].pw);
    }

    free(arr);

    return 0;
}