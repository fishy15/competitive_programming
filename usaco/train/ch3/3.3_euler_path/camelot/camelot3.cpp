/*
ID: aaryan.1
TASK: camelot
LANG: C++11
*/

// :pray: :fishy:

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int r, c;
pair<int, int> king;
vector<pair<int, int>> knights;
int sz;

int dist[780][26][30][2];
bool vist[780][26][30][2];

vector<pair<int, int>> moves = {
    {1, 2},
    {1, -2},
    {-1, 2},
    {-1, -2},
    {2, 1},
    {2, -1},
    {-2, 1},
    {-2, -1}
};

bool comp(const array<int, 3> &a, const array<int, 3> &b) {
    if (a[2] == b[2]) {
        if (a[1] == b[1]) {
            return a[0] > b[0];
        }
        return a[1] > b[1];
    }
    return a[2] > b[2];
}

void calc_dist(int i) {
    queue<array<int, 3>> q;
    q.push({knights[i].first, knights[i].second, 0});

    while (!q.empty()) {
        array<int, 3> cur = q.front();
        q.pop();

        if (vist[i][cur[0]][cur[1]][0]) {
            continue;
        }

        dist[i][cur[0]][cur[1]][0] = cur[2];
        vist[i][cur[0]][cur[1]][0] = true;

        for (pair<int, int> m : moves) {
            int new_x = cur[0] + m.first;
            int new_y = cur[1] + m.second;
            
            if (new_x >= 0 && new_x < c && new_y >= 0 && new_y < r) {
                if (!vist[i][new_x][new_y][0]) {
                    q.push({new_x, new_y, cur[2] + 1});
                }
            }
        }
    }

    int mini = INF;
    priority_queue<array<int, 3>, vector<array<int, 3>>, decltype(&comp)> q2(comp);
    for (int j = 0; j < c; j++) {
        for (int k = 0; k < r; k++) {
            dist[i][j][k][1] = dist[i][j][k][0] + max(abs(king.first - i), abs(king.second - j));

            if (dist[i][j][k][1] < mini) {
                q2 = {};
                mini = dist[i][j][k][1];
                q2.push({j, k, dist[i][j][k][1]});
            } else if (dist[i][j][k][1] == mini) {
                q2.push({j, k, dist[i][j][k][1]});
            }
        }
    }

    while (!q2.empty()) {
        cout << q2.size() << '\n';
        array<int, 3> cur = q2.top();
        q2.pop();

        if (vist[i][cur[0]][cur[1]][1]) {
            continue;
        }

        vist[i][cur[0]][cur[1]][1] = true;
        dist[i][cur[0]][cur[1]][1] = cur[2];

        for (pair<int, int> m : moves) {
            int new_x = m.first + cur[0];
            int new_y = m.second + cur[1];

            if (new_x >= 0 && new_x < c && new_y >= 0 && new_y < r) {
                if (!vist[i][new_x][new_y][1]) {
                    int d = min(dist[i][new_x][new_y][1], cur[2] + 1);
                    q2.push({new_x, new_y, d});
                }
            }
        }
    }
}

int main() {
    ifstream fin("camelot.in");
    ofstream fout("camelot.out");

    fin >> r >> c;
    char kf; int ks; fin >> kf >> ks;
    king = {kf - 'A', ks - 1};

    for (int i = 0; i < r * c; i++) {
        char kr; int kc; fin >> kr >> kc;
        if (fin.eof()) {
            break;
        }
        pair<int, int> k = {kr - 'A', kc - 1};
        knights.push_back(k);
        //cout << k.first << ' ' << k.second << '\n';
    }

    sz = (int)(knights.size());

    if (sz == 0) {
        fout << "0\n";
        return 0;
    }

    for (int a = 0; a < 780; a++) {
        for (int b = 0; b < 26; b++) {
            for (int c = 0; c < 30; c++) {
                for (int d = 0; d < 2; d++) {
                    dist[a][b][c][d] = INF;
                    vist[a][b][c][d] = false;
                }
            }
        }
    }
    
    for (int i = 0; i < sz; i++) {
        calc_dist(i);
    }

    int mini = INF;

    for (int x = 0; x < c; x++) {
        for (int y = 0; y < r; y++) {
            int sum = 0;
            for (int i = 0; i < sz; i++) {
                sum += dist[i][x][y][0];
            }

            for (int i = 0; i < sz; i++) {
                sum -= dist[i][x][y][0];
                sum += dist[i][x][y][1];
                mini = min(mini, sum);
                cout << sum << '\n';
                sum -= dist[i][x][y][1];
                sum += dist[i][x][y][0];
            }
        }
    }

    fout << mini << '\n';

    return 0;
}
