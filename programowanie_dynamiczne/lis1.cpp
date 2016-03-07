/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <vector>
#include <algorithm>
#define SIZE 1048576

class Lis
{
    private:
        int end;
        int data[SIZE],
            prev[SIZE];

        class CompareWithIndex
        {
            private:
                const Lis *lis;

            public:
                CompareWithIndex(const Lis *_lis) :lis(_lis) {};
                bool operator()(const int &a, const int &b) const;
        };

    public:
        int number[SIZE];

        Lis(void)
            :end(0),
             data(),
             prev(),
             number()
        {};

        void push(const int &_number);
        int size(void) const;
        void printSmallest(void) const;
};

int size;
Lis lis;

int main(void)
{
    scanf("%d", &size);
    for(int s = 0; s < size; ++ s)
    {
        scanf("%d", &lis.number[s]);
        lis.push(s);
    }

    printf("%d\n", lis.size());
    lis.printSmallest();
    return 0;
}

inline
bool Lis::CompareWithIndex::operator()(const int &a, const int &b) const
{
    return lis->number[a] < lis->number[b];
}

inline
void Lis::push(const int &_number)
{
    int pos = std::lower_bound(data, data + end, _number, Lis::CompareWithIndex(this)) - data;
    data[pos] = _number;
    if(pos > 0)
        prev[_number] = data[pos - 1];

    else
        prev[_number] = -1;

    if(pos == end) ++ end;
}

inline
int Lis::size(void) const
{
    return end;
}

inline
void Lis::printSmallest(void) const
{
    std::vector<int> res(size());
    res[size() - 1] = data[size() - 1];
    for(int r = size() - 2; r >= 0; -- r)
        res[r] = prev[res[r + 1]];

    for(int r = 0; r < size(); ++ r)
        printf("%d ", number[res[r]]);

    puts("");
}
