#include <stdio.h>
#include <stdlib.h>

typedef struct _coord
{
    int x;
    int y;
} Coord;

void CoordCpy(Coord *dest, Coord *src)
{
    dest->x = src->x;
    dest->y = src->y;
}

int main()
{
    int N;
    scanf("%d", &N);

    Coord *arr = (Coord *)malloc(sizeof(Coord) * N);
    for (int i = 0; i < N; i++)
        scanf("%d %d", &arr[i].x, &arr[i].y);

    // merge sort 구현
    int size = 1;
    while (size < N)
    {
        for (int i = 0; i + size < N; i += size * 2)
        {
            int l = i, r = i + size, idx = 0;
            Coord *sorted_arr = (Coord *)malloc(sizeof(Coord) * (size * 2));

            int max_r = i + size * 2 < N ? i + size * 2 : N;
            while (l < i + size && r < max_r)
            {
                if (arr[l].y < arr[r].y)
                {
                    CoordCpy(&sorted_arr[idx], &arr[l]);
                    l++;
                }
                else if (arr[l].y > arr[r].y)
                {
                    CoordCpy(&sorted_arr[idx], &arr[r]);
                    r++;
                }
                else
                {
                    if (arr[l].x < arr[r].x)
                    {
                        CoordCpy(&sorted_arr[idx], &arr[l]);
                        l++;
                    }
                    else
                    {
                        CoordCpy(&sorted_arr[idx], &arr[r]);
                        r++;
                    }
                }
                idx++;
            }

            while (l < i + size)
            {
                CoordCpy(&sorted_arr[idx], &arr[l]);
                l++, idx++;
            }

            while (r < max_r)
            {
                CoordCpy(&sorted_arr[idx], &arr[r]);
                r++, idx++;
            }

            idx = i;
            for (; idx < max_r; idx++)
                CoordCpy(&arr[idx], &sorted_arr[idx - i]);

            free(sorted_arr);
        }

        size *= 2;
    }

    for (int i = 0; i < N; i++)
        printf("%d %d\n", arr[i].x, arr[i].y);

    // 메모리 해제
    free(arr);
    return 0;
}