/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>

int tests,
    a, b,
    MOD;

inline int fastPower(const int &a, const int &b, const int &m);

int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        scanf("%d %d %d", &a, &b, &MOD);
        printf("%d\n", fastPower(a % MOD, b, MOD));
    }

    return 0;
}

inline int fastPower(const int &a, const int &b, const int &m)
{
    if(!b)
        return 1;

    long long int half = fastPower(a, b / 2, m);
    half *= half;
    if(half > m)
        half %= m;

    half *= (b & 1 ? a : 1LL);
    if(half > m)
        half %= m;

    return half;
}
