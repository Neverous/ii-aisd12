/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

int a, b;

int main(void)
{
    scanf("%d %d", &a, &b);
    if(a > b)
        std::swap(a, b);

    while(a <= b)
        printf("%d\n", a ++);

    return 0;
}
