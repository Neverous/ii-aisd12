/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

unsigned int tests,
             nonterminals,
             terminals;
unsigned char nonterminal[64],       // [nieterminal | nieterminal] => nieterminale
              terminal[32],          // [terminal] => nieterminale
              possible[512][512],    // [pozycja, dlugosc] => nieterminale
              preprocess[256][256];
char from[512],
     to1[2],
     to2[2];

inline
unsigned int _(const unsigned char &a, const unsigned char &b)
{
    return (a << 3) + b;
}

inline
unsigned int $(const unsigned char &a)
{
    if('A' <= a && a <= 'Z')
        return a - 'A';

    return a - 'a';
}

inline
unsigned int $(const unsigned char &a, const unsigned char &b)
{
    return _($(a), $(b));
}

inline
bool solve(void);

int main(void)
{
    scanf("%u", &tests);
    for(unsigned int t = 0; t < tests; ++ t)
    {
        memset(nonterminal, 0, 64);
        memset(terminal,    0, 32);
        memset(possible,    0, 512 * 512);
        memset(preprocess,  0, 256 * 256);
        scanf("%u %u", &nonterminals, &terminals);
        for(unsigned int n = 0; n < nonterminals; ++ n)
        {
            scanf("%s %s %s", from, to1, to2);
            nonterminal[$(to1[0], to2[0])] |= 1 << $(from[0]);
        }

        for(unsigned int n = 0; n < terminals; ++ n)
        {
            scanf("%s %s", from, to1);
            terminal[$(to1[0])] |= 1 << $(from[0]);
        }

        scanf("%s", from);
        puts(solve() ? "TAK" : "NIE");
    }

    return 0;
}

inline
bool solve(void)
{
    for(unsigned int first = 0; first < 256; ++ first)
        for(unsigned int second = 0; second < 256; ++ second)
            for(unsigned int f = 0; f < 8; ++ f)
                if(first & (1 << f)) for(unsigned int s = 0; s < 8; ++ s)
                    if(second & (1 << s)) preprocess[first][second] |= nonterminal[_(f, s)];

    unsigned int len = strlen(from);
    for(unsigned int l = 0; l < len; ++ l)
        possible[l][0] = terminal[$(from[l])];

    for(unsigned int l = 1; l < len; ++ l)           // dlugosc - 1
        for(unsigned int p = 0; p < len - l; ++ p)   // pozycja
            for(unsigned int d = 0; d < l; ++ d)     // podzial
                possible[p][l] |= preprocess[(unsigned int) possible[p][d]][(unsigned int) possible[p + d + 1][l - d - 1]];

    return possible[0][len - 1] & 1;
}
