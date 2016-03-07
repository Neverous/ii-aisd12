/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <climits>
#include <vector>
#define INFINITY 536870912

int verts,
    edges,
    start,
    from, to, cost,
    shortest[512];
bool improved = true;
std::pair<int, int> edge[262144];

inline int $(const int &f, const int &t);
inline int _F(const int &h);
inline int _T(const int &h);

int main(void)
{
    scanf("%d %d %d", &verts, &edges, &start);
    for(int v = 0; v < verts; ++ v)
        shortest[v] = INFINITY;

    shortest[start] = 0;
    for(int e = 0; e < edges; ++ e)
    {
        scanf("%d %d %d", &from, &to, &cost);
        edge[e] = std::make_pair($(from, to), cost);
    }

    for(int v = 0; improved && v < verts; ++ v)
    {
        improved = false;
        for(int e = 0; e < edges; ++ e)
        {
            from = _F(edge[e].first);
            to = _T(edge[e].first);

            if(shortest[from] != INFINITY && shortest[to] > shortest[from] + edge[e].second)
            {
                improved = true;
                shortest[to] = shortest[from] + edge[e].second;
            }
        }
    }

    if(improved)
        puts("NIE");

    else
    {
        for(int v = 0; v < start; ++ v)
            if(shortest[v] != INFINITY)
                printf("%d %d\n", v, shortest[v]);

        for(int v = start + 1; v < verts; ++ v)
            if(shortest[v] != INFINITY)
                printf("%d %d\n", v, shortest[v]);
    }

    return 0;
}

inline int $(const int &f, const int &t)
{
    return (f << 9) + t;
}

inline int _F(const int &h)
{
    return h >> 9;
}

inline int _T(const int &h)
{
    return h & ((1 << 9) - 1);
}
