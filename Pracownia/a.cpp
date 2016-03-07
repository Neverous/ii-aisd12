/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <vector>

#define DEBUG       false
#define FREE        2000*2000
#define BLOCKED     0
#define QUE_SIZE    131072

short int steps[4][2] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1},
};

short int                       width,
                                height;
int                             map[2000][2000],
                                qtop,
                                qbottom;
char                            buffer[2001];
std::pair<short int, short int> start,
                                end,
                                que[QUE_SIZE],
                                act,
                                next;

inline void qpush(const std::pair<short int, short int> &a);
inline std::pair<short int, short int> qpop(void);
inline int qsize(void);
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

inline void qpush(const std::pair<short int, short int> &a)
{
    que[qbottom ++] = a;
    if(qbottom == QUE_SIZE)
        qbottom = 0;
}

inline std::pair<short int, short int> qpop(void)
{
    std::pair<short int, short int> res = que[qtop ++];
    if(qtop == QUE_SIZE)
        qtop = 0;

    return res;
}

inline int qsize(void)
{
    if(qtop <= qbottom)
        return qbottom - qtop;

    return QUE_SIZE - qtop + qbottom;
}

inline bool findTreasure(void)
{
    qpush(start);
    while(qsize())
    {
        act = qpop();
        if(DEBUG) printf("{%hd, %hd}\n", act.first, act.second);
        for(int s = 0; s < 4; ++ s)
        {
            next.first = act.first + steps[s][0];
            next.second = act.second + steps[s][1];
            if(0 <= next.first && next.first < height &&
               0 <= next.second && next.second < width &&
               map[next.first][next.second] == FREE)
            {
                map[next.first][next.second] = map[act.first][act.second] + 1;
                if(next == end)
                    return true;

                if(DEBUG) printf("[%hd, %hd] -> %d\n", next.first, next.second, map[next.first][next.second]);
                qpush(next);
            }
        }
    }

    return false;
}
