#include<bits/stdc++.h>
#define frep(i, a, b) for(int i = a; i <= b; ++i)

using namespace std;


/** parameters **/
const double HEIGHT = 3.0;
const double WIDTH = 3.0;
const int sqrHeightCnt = 30;
const int sqrWidthCnt = 30;


/** constants **/
const double sqrH = HEIGHT / sqrHeightCnt;
const double sqrW = WIDTH / sqrWidthCnt;

// leftBottom as base
const double xBase = -HEIGHT / 2 + sqrH / 2;
const double zBase = -WIDTH / 2 + sqrW / 2;


int main()
{
    FILE* file = fopen("res.txt", "r");
    FILE* fout = fopen("route.txt", "w");
    int r, c;

    while(fscanf(file, "%d %d", &r, &c) > 0)
    {
        double x = xBase + (sqrHeightCnt - 1 - r) * sqrH;
        double z = zBase + c * sqrW;
        fprintf(fout, "%.6f %.6f\n", x, z);
    }
}
