#include <stdio.h>
#include <stdlib.h>

typedef struct _card
{
  int item;
  struct _card *next;
} Number;

typedef struct _queue
{
  Number *front;
  Number *rear;
  int len;
} Queue;

void Push(Queue *q, int item)
{
  // 동적 할당
  Number *new_card = (Number *)malloc(sizeof(Number));
  new_card->item = item, new_card->next = NULL;

  // 큐에 삽입
  if (q->len == 0)
    q->front = new_card, q->rear = new_card;
  else
  {
    q->rear->next = new_card;
    q->rear = new_card;
  }
  q->len++;

  return;
}
int Pop(Queue *q)
{
  // 큐에서 제거
  Number *front_card = q->front;
  if (q->len == 1)
    q->front = NULL, q->rear = NULL;
  else
    q->front = q->front->next;
  q->len--;

  // 동적 할당 해제
  int item = front_card->item;
  free(front_card);

  return item;
}

int main()
{
  Queue q;
  q.front = NULL, q.rear = NULL, q.len = 0;

  int N;
  scanf("%d", &N);
  for (int i = 1; i <= N; i++)
    Push(&q, i);

  while (q.len != 1)
  {
    // front에 있는 카드 버리기
    Pop(&q);

    // 그 다음 front에 있는 카드 뽑아서 rear로 넣기
    Push(&q, Pop(&q));
  }

  printf("%d\n", Pop(&q));

  return 0;
}
