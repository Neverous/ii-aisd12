/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

int lenF,
    lenS,
    lcs[2][1024];
char first[1024],
     second[1024];

int main(void)
{
    scanf("%d %s %d %s", &lenF, first, &lenS, second);
    for(int f = 1; f <= lenF; ++ f)
        for(int s = 1; s <= lenS; ++ s)
            if(first[f - 1] == second[s - 1])
                lcs[f & 1][s] = lcs[!(f & 1)][s - 1] + 1;

            else
                lcs[f & 1][s] = std::max(lcs[!(f & 1)][s], lcs[f & 1][s - 1]);

    printf("%d\n", lenF + lenS - 2 * lcs[lenF & 1][lenS]);
    return 0;
}
