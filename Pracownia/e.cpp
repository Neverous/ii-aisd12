/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <vector>
#include <algorithm>

typedef std::pair<int, int> Pair;

class iTree
{
    private:
        int data[262144 * 2],
            max[262144 * 2];

        void update(const int &st);

    public:
        iTree(void): data(), max() {};

        void insert(const int &start, const int &end, const int &val, const int &iStart = 1, const int &iEnd = 262144, const int &pos = 1);
        int getMax(void) {return max[1];}
};

int clouds,
    x1, y1, x2, y2, water,
    res;
Pair edge[262144],
     span[131072],
     renumber[262144];
iTree tree;

int $(const int &a, const int &b);
Pair _(const int &h);

void Renumber(void);

int main(void)
{
    scanf("%d", &clouds);
    for(int c = 0; c < clouds; ++ c)
    {
        scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &water);
        edge[2 * c] = Pair(x1, $(c, water));
        edge[2 * c + 1] = Pair(x2, $(c, -water));
        span[c] = Pair(y1, y2);
        renumber[2 * c] = Pair(y1, c);
        renumber[2 * c + 1] = Pair(y2, c);
    }

    Renumber();
    sort(edge, edge + 2 * clouds);
    for(int c = 0; c < 2 * clouds; ++ c)
    {
        Pair tmp = _(edge[c].second);
        tree.insert(span[tmp.first].first, span[tmp.first].second, tmp.second);
        res = std::max(res, tree.getMax());
    }

    printf("%d\n", res);
    return 0;
}

int $(const int &a, const int &b)
{
    if(b < 0)
        return (a << 14) - b;

    return -(a << 14) - b;
}

Pair _(const int &h)
{
    Pair r;
    if(h < 0)
    {
        r.first = (-h) >> 14;
        r.second = ((-h) & ((1 << 14) - 1));
        return r;
    }

    r.first = h >> 14;
    r.second = -(h & ((1 << 14) - 1));
    return r;
}

void Renumber(void)
{
    std::sort(renumber, renumber + 2 * clouds);
    for(int r = 0, p = 1; r < 2 * clouds; ++ r)
    {
        if(r && renumber[r].first != renumber[r - 1].first)
            ++ p;

        Pair &pt = span[renumber[r].second];
        if(renumber[r].first == pt.first)
            pt.first = -p;

        else
            pt.second = -p;
    }

    for(int c = 0; c < clouds; ++ c)
    {
        span[c].first *= -1;
        span[c].second *= -1;
    }
}

void iTree::insert(const int &start, const int &end, const int &val, const int &iStart, const int &iEnd, const int &pos)
{
    if(iStart == start && iEnd == end)
    {
        max[pos] = data[pos] += val;
        if(pos < 262144)
            max[pos] += std::max(max[pos * 2], max[pos * 2 + 1]);

        update(pos / 2);
        return;
    }

    int iMid = (iStart + iEnd) / 2;
    if(end <= iMid)
        insert(start, end, val, iStart, iMid, pos * 2);

    else if(start > iMid)
        insert(start, end, val, iMid + 1, iEnd, pos * 2 + 1);

    else
    {
        insert(start, iMid, val, iStart, iMid, pos * 2);
        insert(iMid + 1, end, val, iMid + 1, iEnd, pos * 2 + 1);
    }
}

void iTree::update(const int &st)
{
    for(int p = st; p > 0; p /= 2)
        max[p] = data[p] + std::max(max[p * 2], max[p * 2 + 1]);
}
