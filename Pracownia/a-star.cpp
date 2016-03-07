#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG       false
#define FREE        2000*2000
#define BLOCKED     0

short int steps[4][2] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1},
};

short int                       width,
                                height;
int                             map[2000][2000];
char                            buffer[2001];
std::pair<short int, short int> start,
                                end,
                                act,
                                next;

inline short int dist(const std::pair<short int, short int> &a, const std::pair<short int, short int> &b);
inline bool findTreasure(void);

int main(void)
{
    scanf("%hd %hd", &width, &height);
    for(short int h = 0; h < height; ++ h)
    {
        scanf("%s", buffer);
        for(short int w = 0; w < width; ++ w)
        {
            map[h][w] = FREE;
            switch(buffer[w])
            {
                case 'P':
                    start = std::make_pair(h, w);
                    map[h][w] = BLOCKED;
                    break;

                case 'S':
                    end = std::make_pair(h, w);
                    break;

                case 'x':
                    map[h][w] = BLOCKED;
                    break;
            }
        }
    }

    if(findTreasure())
        printf("%d\n", map[end.first][end.second]);

    else
        puts("NIE");

    return 0;
}

inline bool findTreasure(void)
{
    std::priority_queue<std::pair<int, std::pair<short int, short int> > > que;
    que.push(std::make_pair(-dist(start, end), start));
    while(!que.empty())
    {
        act = que.top().second;
        que.pop();
        if(DEBUG) printf("{%hd, %hd}\n", act.first, act.second);
        for(int s = 0; s < 4; ++ s)
        {
            next.first = act.first + steps[s][0];
            next.second = act.second + steps[s][1];
            if(0 <= next.first && next.first < height &&
               0 <= next.second && next.second < width &&
               map[next.first][next.second] > map[act.first][act.second] + 1)
            {
                map[next.first][next.second] = map[act.first][act.second] + 1;
                if(next == end)
                    return true;

                if(DEBUG) printf("[%hd, %hd] -> %d\n", next.first, next.second, map[next.first][next.second]);
                que.push(std::make_pair(-map[next.first][next.second] - dist(next, end), next));
            }
        }
    }

    return false;
}

inline short int dist(const std::pair<short int, short int> &a, const std::pair<short int, short int> &b)
{
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}
