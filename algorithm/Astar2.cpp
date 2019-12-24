#include<bits/stdc++.h>
#include"heap.cpp"
#define frep(i, a, b) for(int i = a; i <= b; ++i)

using namespace std;


/** useful constants **/
const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

/** parameters **/
const int ROW = 30;
const int COL = 30;

const int SRC_R = ROW - 1, SRC_C = 0;
const int DEST_R = 0, DEST_C = COL - 1;

#define debug true

struct Node
{
    int r;
    int c;
    int g;
    int f;

    Node(int r, int c, int g, int f): r(r), c(c), g(g), f(f){}
    Node(){};
    bool friend operator< (const Node& n1, const Node& n2)
    {
        return n1.f < n2.f;
    }
    bool friend operator<= (const Node& n1, const Node& n2)
    {
        return n1.f <= n2.f;
    }
};

/** variables **/
int fRec[ROW][COL];
char matrix[ROW][COL];
bool inOpen[ROW][COL];
bool vis[ROW][COL];
pair<int, int> fa[ROW][COL];
Node arr[ROW * COL + 5];




MinHeap<Node> openList(arr, 0, ROW * COL + 5);


/** f = g + h **/

int findInd(int r, int c)
{
    int ret = -1;
    int sz = openList.getSize();
    frep(i, 0, sz - 1)
    {
        if(arr[i].r == r && arr[i].c == c)
        {
            ret = i;
            break;
        }
    }
    return ret;
}


bool outRange(int r, int c)
{
    return r < 0 || r >= ROW || c < 0 || c >= COL;
}

int computeH(int r, int c)
{
    return abs(r - DEST_R) + abs(c - DEST_C);
}


void init()
{

}


int main()
{
    freopen("map.txt", "r", stdin);
    fstream resStream;
    resStream.open("res.txt", ios::out);

    frep(i, 0, ROW - 1)
    {
        frep(j, 0, COL - 1)
        {
            cin >> matrix[i][j];
        }
    }
    memset(fa, -1, sizeof(fa));
    memset(fRec, -1, sizeof(fRec));
    Node SRC(SRC_R, SRC_C, 0, 0 + computeH(SRC_R, SRC_C));
    openList.insert(SRC);
    inOpen[SRC_R][SRC_C] = true;
    while(openList.getSize() > 0)
    {
        if(vis[DEST_R][DEST_C])
        {
            break;
        }

        Node node;
        bool suc = openList.removeMin(node);

        const int r = node.r;
        const int c = node.c;
        const int g = node.g;
        const int f = node.f;
        //cout << "r:" << r << " c:" << c << " g:" << g << endl;

        vis[r][c] = true;
        inOpen[r][c] = false;

        frep(k, 0, 4 - 1)
        {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if(outRange(nr, nc))
            {
                continue;
            }
            if(matrix[nr][nc] == 1)
            {
                continue;
            }
            if(vis[nr][nc])
            {
                //if visited or unreachable, skip it
                continue;
            }
            if(!inOpen[nr][nc])
            {
                Node newNode(nr, nc, g+1, g+1 + computeH(nr, nc));
                openList.insert(newNode);
                inOpen[nr][nc] = true;
                fa[nr][nc] = {r, c};
            }
            else
            {
                int ind = findInd(nr, nc);
                int newF = g+1 + computeH(nr, nc);
                if(newF < arr[ind].f)
                {
                    int sz = openList.getSize();
                    swap(arr[ind], arr[sz-1]);
                    --openList.size;
                    openList.buildHeap();
                }
            }
        }
    }

    {
        vector<pair<int, int> > vec;
        int cur_r = DEST_R, cur_c = DEST_C;
        while(!(cur_r == SRC_R && cur_c == SRC_C))
        {
            vec.push_back({cur_r, cur_c});
            int now_r = fa[cur_r][cur_c].first;
            int now_c = fa[cur_r][cur_c].second;
            cur_r = now_r;
            cur_c = now_c;
        }
        vec.push_back({SRC_R, SRC_C});
        for(auto iter = vec.rbegin(); iter != vec.rend(); ++iter)
        {
            const pair<int, int> p = *iter;
            resStream << p.first << " " << p.second << endl;
        }
    }


    if(debug)
    {
        {
            fstream fs;
            fs.open("xRes.txt", ios::out);
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
