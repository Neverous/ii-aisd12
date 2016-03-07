/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#define MOD 500000003

int tests,
    size,
    coloured;
char top[1024],
     mid[1024],
     bot[1024];
int ladder[2][3072],
    almost[2][3072];

inline int solve(void);

int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        scanf("%d %d %s %s %s", &size, &coloured, top, mid, bot);
        mid[0] -= '0';
        for(int t = 0; top[t]; ++ t)
        {
            top[t] -= '0';
            bot[t] -= '0';
            mid[t + 1] -= '0';
        }

        printf("%d\n", solve());
    }

    return 0;
}

inline int solve(void)
{
    for(int c = 0; c <= coloured; ++ c)
        ladder[0][c] = almost[0][c] = 0;

    ladder[0][0] = mid[0] == 0;
    ladder[0][1] = !ladder[0][0];

    almost[0][0] = 1;

    for(int s = 1, s1 = 0, s2 = 1, t = top[s - 1], m = mid[s], b = bot[s - 1]; s <= size; s2 = !(s1 = s2), t = top[s], b = bot[s], m = mid[++ s])
    {
        for(int c = 0; c <= coloured; ++ c)
            ladder[s2][c] = almost[s2][c] = 0;

        for(int c = 0; c <= coloured; ++ c)
        {
            if(ladder[s1][c] >= MOD)
                ladder[s1][c] %= MOD;

            if(almost[s1][c] >= MOD)
                almost[s1][c] %= MOD;

            // FULL
            // -|
            ladder[s2][c + m + t] += ladder[s1][c];

            // _|
            ladder[s2][c + m + b] += ladder[s1][c];

            // =
            ladder[s2][c + t + b] += ladder[s1][c];

            // =|
            ladder[s2][c + t + b + m] += almost[s1][c];

            // ALMOST
            // =
            almost[s2][c + t + b] += almost[s1][c];

            // -
            almost[s2][c + t] += ladder[s1][c];

            // _
            almost[s2][c + b] += ladder[s1][c];
        }
    }

    if(ladder[size & 1][coloured] >= MOD)
        ladder[size & 1][coloured] %= MOD;

    return ladder[size & 1][coloured];
}
