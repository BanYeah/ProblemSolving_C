#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
  int value;
  int abs;
} Node;

void Swap(Node *a, Node *b)
{
  Node temp = *a;
  *a = *b;
  *b = temp;
}

void HeapInsertion(Node *h, int *h_len, int item)
{
  *h_len += 1;
  int len = *h_len;

  // heap의 마지막 요소에 값을 추가
  h[len].value = item;
  h[len].abs = item > 0 ? item : -item;

  // 부모 요소와 비교하면서 정렬
  while (len / 2 > 0)
  {
    // 절댓값 비교
    if (h[len].abs < h[len / 2].abs)
      Swap(&h[len], &h[len / 2]);
    else if (h[len].abs == h[len / 2].abs)
    {
      // 값 비교
      if (h[len].value < h[len / 2].value)
        Swap(&h[len], &h[len / 2]);
      else
        break;
    }
    else
      break;

    len /= 2;
  }
}

int HeapDeletion(Node *h, int *h_len)
{

  int result = h[1].value;

  // heap의 마지막 요소를 루트로 이동
  h[1] = h[*h_len];
  *h_len -= 1;
  int len = *h_len;

  // 자식 요소와 비교하면서 정렬
  int idx = 1;
  while (idx * 2 <= len) // 조건 확인
  {
    // 자식이 하나인 경우
    if (idx * 2 == len)
    {
      // 절댓값 비교
      if (h[idx].abs > h[idx * 2].abs)
        Swap(&h[idx], &h[idx * 2]);
      else if (h[idx].abs == h[idx * 2].abs)
      {
        if (h[idx].value > h[idx * 2].value)
          Swap(&h[idx], &h[idx * 2]);
        else
          break;
      }
      else
        break;

      idx *= 2;
    }
    else // 자식이 둘인 경우
    {
      // 두 자식 중 우선 순위가 높은 자식 탐색
      int small_child_idx;

      // 절댓값 비교
      if (h[idx * 2].abs < h[idx * 2 + 1].abs)
        small_child_idx = idx * 2;
      else if (h[idx * 2].abs == h[idx * 2 + 1].abs)
      {
        // 값 비교
        if (h[idx * 2].value <= h[idx * 2 + 1].value)
          small_child_idx = idx * 2;
        else
          small_child_idx = idx * 2 + 1;
      }
      else
        small_child_idx = idx * 2 + 1;

      // 절댓값 비교
      if (h[idx].abs > h[small_child_idx].abs)
        Swap(&h[idx], &h[small_child_idx]);
      else if (h[idx].abs == h[small_child_idx].abs)
      {
        if (h[idx].value > h[small_child_idx].value)
          Swap(&h[idx], &h[small_child_idx]);
        else
          break;
      }
      else
        break;

      idx = small_child_idx;
    }
  }
  return result;
}

int main()
{
  int N;
  scanf("%d", &N);

  Node *h = (Node *)malloc(sizeof(Node) * (N + 1));
  int h_len = 0;

  for (int i = 0; i < N; i++)
  {
    int input;
    scanf("%d", &input);

    if (input == 0)
    {
      if (h_len == 0)
        printf("0\n");
      else
        printf("%d\n", HeapDeletion(h, &h_len));
    }
    else
      HeapInsertion(h, &h_len, input);
  }

  free(h);
  return 0;
}