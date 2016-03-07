/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

int tests,
    lenF,
    lenS,
    lcs[2][1024];
char first[1024],
     second[1024];

int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        scanf("%d %s %d %s", &lenF, first, &lenS, second);
        for(int f = 0; f <= 1; ++ f)
            for(int s = 0; s <= lenS; ++ s)
                lcs[f][s] = 0;

        for(int f = 1; f <= lenF; ++ f)
            for(int s = 1; s <= lenS; ++ s)
                if(first[f - 1] == second[s - 1])
                    lcs[f & 1][s] = lcs[!(f & 1)][s - 1] + 1;

                else
                    lcs[f & 1][s] = std::max(lcs[!(f & 1)][s], lcs[f & 1][s - 1]);

        printf("%d\n", lcs[lenF & 1][lenS]);
    }

    return 0;
}
