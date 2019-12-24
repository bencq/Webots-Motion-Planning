#include<bits/stdc++.h>

#define frep(i, a, b) for(int i = a; i <= b; ++i)

using namespace std;


/** useful constants **/
const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

/** parameters **/
const int ROW = 30;
const int COL = 30;

int fRec[ROW][COL];
char matrix[ROW][COL];
bool inOpen[ROW][COL];
bool vis[ROW][COL];
pair<int, int> fa[ROW][COL];


const int SRC_R = ROW - 1, SRC_C = 0;
const int DEST_R = 0, DEST_C = COL - 1;


/** f = g + h **/

bool outRange(int r, int c)
{
    return r < 0 || r >= ROW || c < 0 || c >= COL;
}

int computeH(int r, int c)
{
    return abs(r - DEST_R) + abs(c - DEST_C);
}

struct Node
{
    int r;
    int c;
    int g;

    Node(int r, int c, int g): r(r), c(c), g(g){}

    friend operator< (const Node& n1, const Node& n2)
    {
        return computeH(n1.r, n1.c) + n1.g < computeH(n2.r, n2.c) + n2.g;
    }
};

priority_queue<Node> openList;


int main()
{
    freopen("map.txt", "r", stdin);
    fstream fs;
    fs.open("res.txt", ios::out);
    frep(i, 0, ROW - 1)
    {
        frep(j, 0, COL - 1)
        {
            cin >> matrix[i][j];
        }
    }
    memset(fa, -1, sizeof(fa));
    memset(fRec, -1, sizeof(fRec));
    openList.push({SRC_R, SRC_C, 0});
    inOpen[SRC_R][SRC_C] = true;
    while(!openList.empty())
    {
        if(vis[DEST_R][DEST_C])
        {
            break;
        }
        Node node = openList.top(); openList.pop();
        const int r = node.r;
        const int c = node.c;
        const int g = node.g;
        cout << "r:" << r << " c:" << c << " g:" << g << endl;;

        vis[r][c] = true;
        inOpen[r][c] = false;


        frep(k, 0, 4 - 1)
        {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if(outRange(nr, nc) || vis[nr][nc] || matrix[nr][nc] == 1)
            {
                //if visited or unreachable, skip it
                continue;
            }
            if(!inOpen[nr][nc] || (fRec[nr][nc] != -1 && (g + 1) + computeH(nr, nc) < fRec[nr][nc]))
            {
                openList.push({nr, nc, g+1});
                fRec[nr][nc] = (g + 1) + computeH(nr, nc);
                inOpen[nr][nc] = true;
                fa[nr][nc] = {r, c};

            }

        }

    }

    {
        int cur_r = DEST_R, cur_c = DEST_C;
        while(!(cur_r == SRC_R && cur_c == SRC_C))
        {
            matrix[cur_r][cur_c] = 'x';
            int now_r = fa[cur_r][cur_c].first;
            int now_c = fa[cur_r][cur_c].second;
            cur_r = now_r;
            cur_c = now_c;
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

}
