/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>

int numbers,
    number[1048576],
    questions,
    question;

inline int binsearch(const int &value);

int main(void)
{
    scanf("%d", &numbers);
    for(int n = 0; n < numbers; ++ n)
        scanf("%d", &number[n]);

    scanf("%d", &questions);
    for(int q = 0; q < questions; ++ q)
    {
        scanf("%d", &question);
        printf("%d\n", numbers - binsearch(question));
    }

    return 0;
}

inline int binsearch(const int &value)
{
    int start = 0,
        end = numbers,
        mid = -1;

    while(start < end)
    {
        mid = (start + end) >> 1;
        if(number[mid] < value)
            start = mid + 1;

        else
            end = mid;
    }

    return start;
}
