/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>

int books,
    barriers,
    book[131072],
    s, e;

bool check(const int &limit);
int solve(void);

int main(void)
{
    scanf("%d %d", &books, &barriers);
    for(int b = 0; b < books; ++ b)
    {
        scanf("%d", &book[b]);
        if(s < book[b])
            s = book[b];

        e += book[b];
    }

    printf("%d\n", solve());
    return 0;
}

int solve(void)
{
    while(s < e)
    {
        int mid = (s + e) / 2;
        if(check(mid))
            e = mid;

        else
            s = mid + 1;
    }

    return s;
}

bool check(const int &limit)
{
    int c = 0;
    for(int b = 0, sum = 0; b < books && c <= barriers && sum <= limit; ++ b)
    {
        if(sum + book[b] > limit)
        {
            ++ c;
            sum = 0;
        }

        sum += book[b];
    }

    return c <= barriers;
}
