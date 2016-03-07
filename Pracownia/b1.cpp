/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#define MAX_NUMBER 4096

int heap[MAX_NUMBER],
    count[MAX_NUMBER],
    size, numbers;
long long int act,
              prev;

inline long long int heap_pop(void);
inline void heap_fix(void);
inline long long int compute(const int &i);

int main(void)
{
    scanf("%d %d", &size, &numbers);
    for(int s = 1; s <= size && s < MAX_NUMBER; ++ s)
    {
        heap[s] = size - s + 1;
        count[MAX_NUMBER - s] = size - s + 1;
    }

    while(numbers > 0)
    {
        act = heap_pop();
        if(prev == act)
            continue;

        prev = act;
        printf("%lld\n", act);
        -- numbers;
    }

    return 0;
}

inline long long int heap_pop(void)
{
    long long int res = compute(1);
    -- count[MAX_NUMBER + heap[1] - size - 1];
    heap_fix();
    return res;
}

inline void heap_fix(void)
{
    int i = 1, j = 1, t = 0;
    while(i < MAX_NUMBER / 2)
    {
        j = i;
        if(compute(j) < compute(2 * i))
            j = 2 * i;

        if(compute(j) < compute(2 * i + 1))
            j = 2 * i + 1;

        if(j == i)
            break;

        t = heap[i];
        heap[i] = heap[j];
        heap[j] = t;
        i = j;
    }
}

inline long long int compute(const int &i)
{
    return (long long int) heap[i] * count[MAX_NUMBER + heap[i] - size - 1];
}
