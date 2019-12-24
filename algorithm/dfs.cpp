#include<bits/stdc++.h>
#define frep(i, a, b) for(int i = a; i <= b; ++i)

using namespace std;


/** useful constants **/
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, 1};

/** parameters **/
const int ROW = 30;
const int COL = 30;

const int SRC_R = ROW - 1, SRC_C = 0;
const int DEST_R = 0, DEST_C = COL - 1;

#define debug true



/** variables **/
char matrix[ROW][COL];
bool vis[ROW][COL];

vector<pair<int, int> > res;
bool suc = false;


bool outRange(int r, int c)
{
    return r < 0 || r >= ROW || c < 0 || c >= COL;
}

void dfs(int r, int c)
{
    vis[r][c] = true;
    res.push_back({r, c});
    if(r == DEST_R && c == DEST_C)
    {
        suc = true;
        return;
    }
    frep(i, 0, 4 - 1)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(outRange(nr, nc) || vis[nr][nc] || matrix[nr][nc] == '1')
        {
            continue;
        }
        dfs(nr, nc);
        if(suc)
        {
            return;
        }
        res.pop_back();
    }
}



int main()
{
    freopen("map.txt", "r", stdin);
    fstream resStream;
    resStream.open("dfsRes.txt", ios::out);

    frep(i, 0, ROW - 1)
    {
        frep(j, 0, COL - 1)
        {
            cin >> matrix[i][j];
        }
    }

    dfs(SRC_R, SRC_C);
    if(suc)
    {
        for(auto p : res)
        {
            resStream << p.first << " " << p.second << endl;
        }
    }


    if(debug)
    {
        {
            fstream fs;
            fs.open("dfsXRes.txt", ios::out);
            for(auto p : res)
            {
                matrix[p.first][p.second] = 'x';
            }


            frep(i, 0, ROW - 1)
            {
                frep(j, 0, COL - 1)
                {
                    fs << matrix[i][j] << " ";
                }
                fs << endl;
            }

        }
        {
            fstream fs2;
            fs2.open("debug.txt", ios::out);
            frep(i, 0, ROW - 1)
            {
                frep(j, 0, COL - 1)
                {
                    if(vis[i][j])
                    {
                        fs2 << "o" << " ";
                    }
                    else
                    {
                        fs2 << "x" << " ";
                    }
                }

                fs2 << endl;
            }
        }

    }



}
