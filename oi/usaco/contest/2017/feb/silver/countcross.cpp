#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

#define MAXN 100

using namespace std;

// up down left right <- bits
// 1 means that they cant move there
int moves[MAXN][MAXN];
int grid[MAXN][MAXN];
int N, K, R;

void floodfill(int x, int y, int num) {
    if (grid[x][y] != 0) {
        return;
    }

    grid[x][y] = num;
    if ((moves[x][y] & 0b1000) == 0 && x < N - 1) {
        floodfill(x + 1, y, num);
    }

    if ((moves[x][y] & 0b0100) == 0 && x > 0) {
        floodfill(x - 1, y, num);
    }

    if ((moves[x][y] & 0b0010) == 0 && y > 0) {
        floodfill(x, y - 1, num);
    }

    if ((moves[x][y] & 0b0001) == 0 && y < N - 1) {
        floodfill(x, y + 1, num);
    }
}

int main() {
    ifstream fin("countcross.in");
    ofstream fout("countcross.out");

    fin >> N >> K >> R;
    
    for (int i = 0; i < R; i++) {
        int a, b, c, d; fin >> a >> b >> c >> d;

        a--;
        b--;
        c--;
        d--;

        if (a < c) {
            moves[a][b] = moves[a][b] | 0b1000;
            moves[c][d] = moves[c][d] | 0b0100;
        } else if (a > c) {
            moves[a][b] = moves[a][b] | 0b0100;
            moves[c][d] = moves[c][d] | 0b1000;
        } else {
            if (b < d) {
                moves[a][b] = moves[a][b] | 0b0001;
                moves[c][d] = moves[c][d] | 0b0010;
            } else {
                moves[a][b] = moves[a][b] | 0b0010;
                moves[c][d] = moves[c][d] | 0b0001;
            }
        }
    }

    int count = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0) {
                floodfill(i, j, count);
                count++;
            }
        }
    }

    vector<int> cows(count - 1, 0);
    int ans = 0;
    for (int i = 0; i < K; i++) {
        int x, y; fin >> x >> y;
        x--;
        y--;

        int val = grid[x][y];
        cows[val - 1]++;
    }

    for (int i = 0; i < cows.size() - 1; i++) {
        for (int j = i + 1; j < cows.size(); j++) {
            ans += cows[i] * cows[j];
        }
    }

    fout << ans << '\n';
}
