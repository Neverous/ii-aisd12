/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <vector>
#include <queue>
#include <map>

int cities,
    roads,
    fuel[1024],
    start, end, length,
    questions,
    tank;

std::vector<std::pair<int, int> > graph[1024];

inline int $(const int &v, const int &t) { return 128 * v + t; }
inline int _v(const int &h) { return h / 128; }
inline int _t(const int &h) { return h % 128; }

bool solve(void);

int main(void)
{
    scanf("%d %d", &cities, &roads);
    for(int c = 0; c < cities; ++ c)
        scanf("%d", &fuel[c]);

    for(int r = 0; r < roads; ++ r)
    {
        scanf("%d %d %d", &start, &end, &length);
        graph[start].push_back(std::make_pair(end, length));
        graph[end].push_back(std::make_pair(start, length));
    }


    scanf("%d", &questions);
    for(int q = 0; q < questions; ++ q)
    {
        scanf("%d %d %d", &tank, &start, &end);
        if(!solve())
            puts("impossible");
    }

    return 0;
}

inline
bool solve(void)
{
    int cheapest[131072] = {};
    for(int c = 0; c < 131072; ++ c)
        cheapest[c] = 1 << 30;

    std::priority_queue<std::pair<int, int> > que;

    cheapest[$(start, 0)] = 0;
    que.push(std::make_pair(0, $(start, 0)));
    while(!que.empty())
    {
        std::pair<int, int> act = que.top();
        que.pop();

        if(cheapest[act.second] < -act.first)
            continue;

        if(_v(act.second) == end)
        {
            printf("%d\n", -act.first);
            return true;
        }

        int v = _v(act.second),
            t = _t(act.second);

        // printf("> %d, %d => %d\n", v, t, cheapest[act.second]);

        // go to next city
        for(unsigned int n = 0; n < graph[v].size(); ++ n)
        {
            int &_next = graph[v][n].first,
                &_length = graph[v][n].second;

            if(_length > t) continue;
            if(cheapest[$(_next, t - _length)] > cheapest[act.second])
            {
                cheapest[$(_next, t - _length)] = cheapest[act.second];
                que.push(std::make_pair(-cheapest[$(_next, t - _length)], $(_next, t - _length)));
            }
        }

        // or stay and tank once
        if(t < tank && cheapest[$(v, t + 1)] > cheapest[act.second] + fuel[v])
        {
            cheapest[$(v, t + 1)] = cheapest[act.second] + fuel[v];
            que.push(std::make_pair(-cheapest[$(v, t + 1)], $(v, t + 1)));
        }
    }

    return false;
}
