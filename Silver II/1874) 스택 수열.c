#include <stdio.h>
#include <stdlib.h>

typedef struct _number
{
  int item;
  struct _number *next;
} Number;

typedef struct _stack
{
  Number *top;
  int len;
} Stack;

void Push(Stack *s, int item)
{
  // 동적 할당
  Number *new_number = (Number *)malloc(sizeof(Number));
  new_number->item = item, new_number->next = NULL;

  // 스택에 삽입
  if (s->len == 0)
    s->top = new_number;
  else
  {
    new_number->next = s->top;
    s->top = new_number;
  }
  s->len++;

  return;
}
int Peek(Stack *s)
{
  return s->top->item;
}
int Pop(Stack *s)
{
  // 스택에서 제거
  Number *top_number = s->top;
  if (s->len == 1)
    s->top = NULL;
  else
    s->top = s->top->next;
  s->len--;

  // 동적 할당 해제
  int item = top_number->item;
  free(top_number);

  return item;
}

int main()
{
  Stack s;
  s.top = NULL, s.len = 0;

  int N;
  scanf("%d", &N);

  int *arr = (int *)malloc(sizeof(int) * N);
  for (int i = 0; i < N; i++)
    scanf("%d", &arr[i]);

  // 스택 수열인지 확인
  int flag = 1, last_push = 0;
  for (int i = 0; i < N; i++)
  {
    if (arr[i] > last_push)
    {
      for (int j = last_push + 1; j <= arr[i]; j++)
        Push(&s, j);

      last_push = arr[i];
      Pop(&s);
    }
    else
    {
      if (s.len > 0 && arr[i] == Peek(&s))
        Pop(&s);
      else
      {
        flag = 0;
        while (s.len != 0)
        {
          Pop(&s);
        }
        break;
      }
    }
  }
  if (!flag)
  {
    printf("NO\n");
    free(arr);

    return 0;
  }

  // 스택 연산자 출력
  last_push = 0;
  for (int i = 0; i < N; i++)
  {
    if (arr[i] > last_push)
    {
      for (int j = last_push + 1; j <= arr[i]; j++)
      {
        Push(&s, j);
        printf("+\n");
      }

      last_push = arr[i];
      Pop(&s);
      printf("-\n");
    }
    else
    {
      Pop(&s);
      printf("-\n");
    }
  }

  free(arr);

  return 0;
}