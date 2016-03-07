/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <cstring>
#include <algorithm>

int tests,
    lenF,
    lenS,
    lcs[1024][1024];
char first[1024],
     second[1024],
     result[1024];

int main(void)
{
    scanf("%s %s", first, second);
    lenF = strlen(first);
    lenS = strlen(second);
    for(int f = 1; f <= lenF; ++ f)
        for(int s = 1; s <= lenS; ++ s)
            if(first[f - 1] == second[s - 1])
                lcs[f][s] = lcs[f - 1][s - 1] + 1;

            else
                lcs[f][s] = std::max(lcs[f - 1][s], lcs[f][s - 1]);

    for(int f = lenF, s = lenS; f > 0 && s > 0;)
    {
        if(first[f - 1] == second[s - 1])
        {
            result[lcs[f][s] - 1] = first[f - 1];
            -- f;
            -- s;
        }

        else if(lcs[f - 1][s] > lcs[f][s - 1])
            -- f;

        else -- s;
    }

    printf("%s\n", result);
    return 0;
}
