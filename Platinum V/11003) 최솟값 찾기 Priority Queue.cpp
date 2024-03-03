// 이 풀이의 시간 복잡도는 O(n logn)이어서
// 몇 가지 최적화를 진행해주어야 시간 초과를 해결할 수 있음
// 코드가 cpp인 이유: 빠른 입출력을 사용하기 위해서
#include <iostream>

using namespace std;

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

Node HeapPeek(Node *h)
{
  return h[1];
}

int HeapDeletion(Node *h, int *h_len)
{

  int result = h[1].item;

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
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, L;
  cin >> N >> L;

  int *arr = new int[N];
  for (int i = 0; i < N; i++) // O(n)
    cin >> arr[i];

  Node *h = new Node[N + 1];
  int h_len = 0;

  // 뒤에서부터 L개 만큼 min_h에 추가
  for (int i = N - 1; i >= N - L; i--) // O(L logn)
    HeapInsertion(h, &h_len, arr[i], i);

  int idx = N - 1;
  Node min_value;
  while (idx >= 0) // O(2n logn)
  {
    // 최솟값 탐색
    min_value = HeapPeek(h);
    while (!(idx - L + 1 <= min_value.idx && min_value.idx <= idx))
    {
      HeapDeletion(h, &h_len);
      min_value = HeapPeek(h);
    }
    arr[idx] = min_value.item;

    if (idx - L >= 0) // 범위에 새로 들어온 값 추가
      HeapInsertion(h, &h_len, arr[idx - L], idx - L);

    idx--;
  }

  for (int i = 0; i < N; i++) // O(n)
    cout << arr[i] << " ";
  cout << endl;

  delete[] arr;
  delete[] h;
  return 0;
}