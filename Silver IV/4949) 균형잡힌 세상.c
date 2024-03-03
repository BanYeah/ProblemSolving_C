#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct _node
{
    char c;
    struct _node *next;
} Node;

int main()
{
    // 각 문자열이 균형잡힌 문자열인지 확인
    while (1)
    {
        char str[MAX_LENGTH + 1];

        // 입력의 종료 여부 확인
        str[0] = getchar();
        if (str[0] == '.')
            break;

        // 문자열 입력 받기
        int idx = 1;
        while (1)
        {
            str[idx++] = getchar();
            if (str[idx - 1] == '.')
                break;
        }
        // \n 입력 받기
        str[idx] = getchar();

        // 균형이 잡힌 문자열인지 확인 (stack 이용)
        Node *stack = NULL;
        int flag = 0;
        for (int i = 0; i < idx; i++)
        {
            if (str[i] == '(' || str[i] == '[')
            {
                Node *new_node = (Node *)malloc(sizeof(Node));
                new_node->c = str[i];
                new_node->next = stack;

                stack = new_node;
            }
            else if (str[i] == ')' || str[i] == ']')
            {
                if (stack != NULL && stack->c == (str[i] == ')' ? '(' : '['))
                {
                    Node *temp = stack;
                    stack = stack->next;

                    free(temp);
                }
                else
                {
                    flag = 1;
                    break;
                }
            }
        }
        if (stack != NULL)
        {
            flag = 1;

            while (stack != NULL)
            {
                Node *temp = stack;
                stack = stack->next;

                free(temp);
            }
        }

        if (flag)
            printf("no\n");
        else
            printf("yes\n");
    }

    return 0;
}