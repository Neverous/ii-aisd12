/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <queue>
#include <vector>
#define INFINITY 1073741824

int verts,
    edges,
    from, to, cost,
    shortest[8192];
std::vector<std::pair<int, int> > graph[8192];
std::priority_queue<std::pair<int, int> > que;
std::pair<int, int> act;

int main(void)
{
    scanf("%d %d", &verts, &edges);
    for(int v = 0; v < verts; ++ v)
        shortest[v] = INFINITY;

    for(int e = 0; e < edges; ++ e)
    {
        scanf("%d %d %d", &from, &to, &cost);
        -- from;
        -- to;

        graph[from].push_back(std::make_pair(to, cost));
        graph[to].push_back(std::make_pair(from, cost));
    }

    que.push(std::make_pair(0, 0));
    shortest[0] = 0;
    while(!que.empty())
    {
        act = que.top();
        que.pop();

        if(act.first != -shortest[act.second])
            continue;

        for(unsigned int n = 0; n < graph[act.second].size(); ++ n)
            if(shortest[graph[act.second][n].first] > shortest[act.second] + graph[act.second][n].second)
            {
                shortest[graph[act.second][n].first] = shortest[act.second] + graph[act.second][n].second;
                que.push(std::make_pair(-shortest[graph[act.second][n].first], graph[act.second][n].first));
            }
    }

    for(int v = 1; v < verts; ++ v)
        printf("%d ", shortest[v]);

    puts("");
    return 0;
}
