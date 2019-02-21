/*
ID: aaryan.1
TASK: maze1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

typedef struct room room;
struct room {
    int dist;
    bool up, down, left, right;

    room() {
        dist = INF;
        up = down = left = right = false;
    }
};

int M, N;
vector<vector<room> > house;
vector<vector<bool> > visited;
int maxDist;

void fill(int x, int y);
int min(int x, int y);

int main() {
    ifstream fin("maze1.in");
    ofstream fout("maze1.out");

    fin >> M >> N;
    string junk;
    getline(fin, junk); // so its on the correct lines

    house = vector<vector<room> >(N, vector<room>(M));

    // creates the rooms
    for (int i = 0; i <= N; i++) {
        string row = "";
        getline(fin, row);

        //cout << row << endl;
        for (int j = 0; j < M; j++) {
            //cout << i << ' ' << j << endl;
            if (row[2*j + 1] == '-') {
                if (i < N) {
                    house[i][j].up = true;
                }

                if (i > 0) {
                    house[i - 1][j].down = true;
                }
            }
        }

        if (i < N) {
            getline(fin, row);
            for (int j = 0; j <= M; j++) {
                if (row[2*j] == '|') {
                    if (j < M) {
                        house[i][j].left = true;
                    }

                    if (j > 0) {
                        house[i][j - 1].right = true;
                    }
                }
            }
        }
    }

    visited = vector<vector<bool> >(N, vector<bool>(M, false));

    // checks top row
    for (int j = 0; j < M; j++) {
        if (!house[0][j].up) {
            //visited = vector<vector<bool> >(N, vector<bool>(M, false));
            house[0][j].dist = 1;
            fill(0, j);
        }
    }

    // checks bottom row
    for (int j = 0; j < M; j++) {
        if (!house[N - 1][j].down) {
            //visited = vector<vector<bool> >(N, vector<bool>(M, false));
            house[N - 1][j].dist = 1;
            fill(N - 1, j);
        }
    }

    // checks left col
    for (int i = 0; i < N; i++) {
        if (!house[i][0].left) {
            //visited = vector<vector<bool> >(N, vector<bool>(M, false));
            house[i][0].dist = 1;
            fill(i, 0);
        }
    }

    // checks right col
    for (int i = 0; i < N; i++) {
        if (!house[i][M - 1].right) {
            //visited = vector<vector<bool> >(N, vector<bool>(M, false));
            house[i][M - 1].dist = 1;
            fill(i, M - 1);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (house[i][j].dist > maxDist) {
                maxDist = house[i][j].dist;
            }
        }
    }

    fout << maxDist << '\n';

    /*
    for (auto x : house) {
        for (auto y : x) {
            cout << y.dist << ' ';
        }
        cout << endl;
    }
    */

    return 0;
}

void fill(int x, int y) {
    //cout << x << ' ' << y << endl;

    //cout << x << ' ' << y << endl;
    auto cur = &house[x][y];

    if (!cur->up && x > 0 && house[x - 1][y].dist > cur->dist + 1) {
        //cout << "HI\n";
        house[x - 1][y].dist = cur->dist + 1;
        fill(x - 1, y);
    } 

    if (!cur->down && x < N - 1 && house[x + 1][y].dist > cur->dist + 1) {
        //cout << "BYE\n";
        house[x + 1][y].dist = min(cur->dist + 1, house[x + 1][y].dist);
        fill(x + 1, y);
    } 

    if (!cur->left && y > 0 && house[x][y - 1].dist > cur->dist + 1) {
        //cout << "france won\n";
        house[x][y - 1].dist = min(cur->dist + 1, house[x][y - 1].dist);
        fill(x, y - 1);
    } 

    if (!cur->right && y < M - 1 && house[x][y + 1].dist > cur->dist + 1) {
        //cout << "croatia won\n";
        house[x][y + 1].dist = min(cur->dist + 1, house[x][y + 1].dist);
        fill(x, y + 1);
    } 
}

int min(int x, int y) { 
    return x < y ? x : y;
}