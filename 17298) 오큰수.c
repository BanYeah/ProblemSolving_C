#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
  int item;
  int idx;
} Node;

void Swap(Node *a, Node *b)
{
  Node temp = *a;
  *a = *b;
  *b = temp;
}

void HeapInsertion(Node *h, int *h_len, int item, int idx)
{
  *h_len += 1;
  int len = *h_len;

  // heap의 마지막 요소에 값을 추가
  h[len].item = item, h[len].idx = idx;

  // 부모 요소와 비교하면서 정렬
  while (len / 2 > 0)
  {
    if (h[len].item < h[len / 2].item)
      Swap(&h[len], &h[len / 2]);
    else
      break;

    len /= 2;
  }
}

int HeapPeek(Node *h)
{
  return h[1].item;
}

int HeapDeletion(Node *h, int *h_len)
{

  int result = h[1].idx;

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
      if (h[idx].item > h[idx * 2].item)
        Swap(&h[idx], &h[idx * 2]);
      else
        break;

      idx *= 2;
    }
    else // 자식이 둘인 경우
    {
      // 두 자식 중 우선 순위가 높은 자식 탐색
      int small_child_idx;
      if (h[idx * 2].item <= h[idx * 2 + 1].item)
        small_child_idx = idx * 2;
      else
        small_child_idx = idx * 2 + 1;

      // 절댓값 비교
      if (h[idx].item > h[small_child_idx].item)
        Swap(&h[idx], &h[small_child_idx]);
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

  int *arr = (int *)malloc(sizeof(int) * N);
  for (int i = 0; i < N; i++)
    scanf("%d", &arr[i]);

  int *output_arr = (int *)malloc(sizeof(int) * N);
  Node *h = (Node *)malloc(sizeof(Node) * (N + 1));
  int h_len = 0;

  for (int i = 0; i < N; i++)
  {
    while (h_len > 0 && arr[i] > HeapPeek(h))
      output_arr[HeapDeletion(h, &h_len)] = arr[i];

    HeapInsertion(h, &h_len, arr[i], i);
  }

  while (h_len > 0)
    output_arr[HeapDeletion(h, &h_len)] = -1;

  for (int i = 0; i < N; i++)
    printf("%d ", output_arr[i]);
  printf("\n");

  free(arr);
  free(output_arr);
  free(h);
  return 0;
}