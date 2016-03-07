/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <vector>
#include <algorithm>

int verts,
    edges,
    last,
    repr[1048576];
std::pair<int, std::pair<int, int> > edge[1048576];
#define _s second.first
#define _e second.second
#define _cost first

bool unionUnion(const int &a, const int &b);
int &unionFind(const int &a);

int main(void)
{
    scanf("%d %d", &verts, &edges);
    for(int v = 0; v <= verts; ++ v)
        repr[v] = v;

    for(int e = 0; e < edges; ++ e)
    {
        scanf("%d %d %d", &edge[e]._s, &edge[e]._e, &edge[e]._cost);
        edge[e]._cost *= -1;
    }

    std::sort(edge, edge + edges);
    for(int e = 0; e < edges; ++ e)
        if(unionUnion(edge[e]._s, edge[e]._e))
            last = -edge[e]._cost;

    printf("%d\n", last);
    return 0;
}

bool unionUnion(const int &a, const int &b)
{
    int &fa = unionFind(a),
        &fb = unionFind(b);

    if(fa == fb)
        return false;

    if(fa < fb)
        repr[fb] = fa;

    else
        repr[fa] = fb;

    return true;
}

int &unionFind(const int &a)
{
    if(repr[a] == a)
        return repr[a];

    return repr[a] = unionFind(repr[a]);
}
