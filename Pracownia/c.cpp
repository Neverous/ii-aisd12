/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#define COINS 101
#define WEIGHT 100001

int weight,
    coins,
    value[COINS],
    mass[COINS],
    count[COINS];
long long int res[WEIGHT];

inline
long long int _hash(const char &coin, const long long int &money)
{
    return (money << 7) + coin;
}

inline
char _coin(const long long int &hash)
{
    return hash & ((1 << 7) - 1);
}

inline
long long int _money(const long long int &hash)
{
    return hash >> 7;
}

int main(void)
{
    scanf("%d %d", &weight, &coins);
    for(int c = 0; c < coins; ++ c)
        scanf("%d %d", &value[c], &mass[c]);


    /* COUNT MIN */
    for(int w = 1; w <= weight; ++ w)
        res[w] = _hash(0, (long long int) WEIGHT * WEIGHT);

    for(int c = 0; c < coins; ++ c)
        if(_money(res[mass[c]]) > value[c])
            res[mass[c]] = _hash(c, value[c]);

    for(int w = 0; w <= weight; ++ w)
    {
        long long int money = _money(res[w]);
        if(money) for(int c = 0; c < coins; ++ c)
            if(w + mass[c] <= weight && _money(res[w + mass[c]]) > money + value[c])
                res[w + mass[c]] = _hash(c, money + value[c]);
    }

    if(_money(res[weight]) == (long long int) WEIGHT * WEIGHT)
    {
        puts("NIE");
        return 0;
    }

    puts("TAK");
    for(int w = weight; w > 0; w -= mass[(int) _coin(res[w])])
        ++ count[(int) _coin(res[w])];

    printf("%lld\n", _money(res[weight]));
    for(int c = 0; c < coins; ++ c)
    {
        printf("%d ", count[c]);
        count[c] = 0;
    }
    
    puts("");
    /* COUNT MAX */
    for(int w = 1; w <= weight; ++ w)
        res[w] = 0;

    for(int c = 0; c < coins; ++ c)
        if(_money(res[mass[c]]) < value[c])
            res[mass[c]] = _hash(c, value[c]);

    for(int w = 0; w <= weight; ++ w)
    {
        long long int money = _money(res[w]);
        if(money) for(int c = 0; c < coins; ++ c)
            if(w + mass[c] <= weight && _money(res[w + mass[c]]) < money + value[c])
                res[w + mass[c]] = _hash(c, money + value[c]);
    }

    for(int w = weight; w > 0; w -= mass[(int) _coin(res[w])])
        ++ count[(int) _coin(res[w])];

    printf("%lld\n", _money(res[weight]));
    for(int c = 0; c < coins; ++ c)
        printf("%d ", count[c]);
    
    puts("");
    return 0;
}
