/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>

int rows,
    cols,
    field[1024][1024],
    eat[2][1024],
    res;

int main(void)
{
    scanf("%d %d", &rows, &cols);
    for(int r = 0; r < rows; ++ r)
        for(int c = 0; c < cols; ++ c)
            scanf("%d", &field[c][r]);

    for(int r = 0; r < rows; ++ r)
        eat[0][r] = field[0][r];

    for(int c = 0; c < cols - 1; ++ c)
    {
        int a = c & 1,
            n = !a;

        /* UP -> DOWN */
        for(int r = 1; r < rows; ++ r)
            if(eat[a][r - 1] + field[c][r] < eat[a][r])
                eat[a][r] = eat[a][r - 1] + field[c][r];

        /* DOWN -> UP */
        for(int r = rows - 2; r >= 0; -- r)
            if(eat[a][r + 1] + field[c][r] < eat[a][r])
                eat[a][r] = eat[a][r + 1] + field[c][r];

        /* NEXT ROW */
        for(int r = 0; r < rows; ++ r)
            eat[n][r] = eat[a][r] + field[c + 1][r];

        for(int r = 0; r < rows - 1; ++ r)
            if(eat[a][r] + field[c + 1][r + 1] < eat[n][r + 1])
                eat[n][r + 1] = eat[a][r] + field[c + 1][r + 1];

        for(int r = 1; r < rows; ++ r)
            if(eat[a][r] + field[c + 1][r - 1] < eat[n][r - 1])
                eat[n][r - 1] = eat[a][r] + field[c + 1][r - 1];
    }

    res = eat[!(cols & 1)][0];
    for(int r = 1; r < rows; ++ r)
        if(res > eat[!(cols & 1)][r])
            res = eat[!(cols & 1)][r];

    printf("%d\n", res);
    return 0;
}
