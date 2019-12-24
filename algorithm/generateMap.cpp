#include<bits/stdc++.h>

#define frep(i, a, b) for(int i = a; i <= b; ++i)

using namespace std;

/** parameters **/
const int ROW = 30;
const int COL = 30;


/** map **/
int matrix[ROW][COL];

int main()
{
    freopen("map.txt", "w", stdout);
    srand(time(NULL));
    //rand() % RAND_MAX;
    frep(i, 0, ROW - 1)
    {
        frep(j, 0, COL - 1)
        {
            int rndNum = rand() % 10;
            if(rndNum == 0)
            {
                matrix[i][j] = 1;
            }
        }
    }
    matrix[ROW - 1][0] = 0;

    frep(i, 0, ROW - 1)
    {
        frep(j, 0, COL - 1)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
