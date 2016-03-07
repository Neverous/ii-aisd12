/* 2013
 * Maciej Szeptuch 248078
 * Gr. KLO
 */
#include <cstdio>

int start, end;

int main(void)
{
    scanf("%d %d", &start, &end);
    for(int s = start | 1; s <= end; s += 2)
        printf("%d ", s);

    puts("");
    return 0;
}
