/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>
#define MAX_NUMBER 1000000
int brute[MAX_NUMBER][2],
    size, numbers;
long long int prev;

int main(void)
{
    scanf("%d %d", &size, &numbers);
    for(int i = 0; size > 0; ++ i, -- size)
        brute[i][0] = brute[i][1] = size;

    while(numbers > 0)
    {
        long long int value = (long long int) brute[0][0] * brute[0][1];
        -- brute[0][1];
        for(int i = 0; (long long int) brute[i][0] * brute[i][1] < (long long int) brute[i + 1][0] * brute[i + 1][1]; ++ i)
            std::swap(brute[i], brute[i + 1]);

        if(value != prev)
        {
            printf("%lld\n", value);
            -- numbers;
        }

        prev = value;
    }

    return 0;
}
