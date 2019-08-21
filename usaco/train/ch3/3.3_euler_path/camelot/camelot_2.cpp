/*
ID: aaryan.1
TASK: camelot
LANG: C++11
*/
// :pray: :arrayman:
// :pray: :summit:
// :pray: :pusheen:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eed:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinx:
// :pray: :eyg:
// :pray: :evan:
// :pray: :cj:
// :pray: :steph:
// :pray: :fatant:
// :pray: :mathbot:
// :pray: :dolphin:
// :pray: :stef:
// :pray: :geothermal:
// :pray: :mikey:
// :pray: :horse:
// :pray: :snek:
// :pray: :wayne:
// :pray: :wu:
// :pray: :vmaddur:
// :pray: :dorijanko:
// :pray: :gaming:
// :pray: :kassuno:
// :pray: :hyacinth:
// :pray: :chilli:
// :pray: :dhruv:
// :pray: :philip:
// :pray: :paiman:
// :pray: :camel:
// :pray: :tree:
// :pray: :tux:
// :pray: :jony:
// :pray: :kage:
// :pray: :ghost:
// :pray: :aha:
// :pray: :coolguy:
// :pray: :imax:
// :pray: :howlet:
// :pray: :darren:
// :pray: :arie: 
// :pray: :blastman: 
// :pray: :zephyr: 
// :pray: :bigc:

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
int k;
pair<int, int> king;
vector<pair<int, int>> knights;
int dist[780][26][30][2];

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

bool comp(const array<int, 4> &a1, const array<int, 4> &a2) {
    return a1[3] > a2[3];
}

void find_dist(int i) {
    array<int, 4> arr = {knights[i].first, knights[i].second, 0, 0};
    //priority_queue<array<int, 4>, vector<array<int, 4>>, decltype(&comp)>q(comp);
    queue<array<int, 4>> q;
    q.push(arr);
    while (!q.empty()) {
        array<int, 4> cur = q.front();
        q.pop();

        if (dist[i][cur[0]][cur[1]][cur[2]] || \
                (cur[0] == knights[i].first && cur[1] == knights[i].second && cur[2] == 0 && cur[3] > 0)) {
            continue;
        }

        dist[i][cur[0]][cur[1]][cur[2]] = cur[3];

        for (auto m : moves) {
            int new_x = cur[0] + m.first;
            int new_y = cur[1] + m.second;

            if (new_x >= 0 && new_y >= 0 && new_x < r && new_y < c) {
                if (!dist[i][new_x][new_y][0] && \
                    !(new_x == knights[i].first && new_y == knights[i].second)) {
                    q.push({new_x, new_y, 0, cur[3] + 1});
                }
            }
        }
    }

    vector<pair<int, int>> start;
    int mini = INF;
    for (int j = 0; j < r; j++) {
        for (int k = 0; k < c; k++) {
            dist[i][j][k][1] = dist[i][j][k][0] + max(abs(king.first - j), abs(king.second - k));
            if (dist[i][j][k][1] < mini) {
                start = {{j, k}};
                mini = dist[i][j][k][1];
            } else if (dist[i][j][k][1] == mini) {
                start.push_back({j, k});
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

    //cout << king.first << ' ' << king.second << '\n';
    for (int i = 0; i < r * c; i++) {
        char kr; int kc; fin >> kr >> kc;
        //cout << "TEST\n";
        //cout << kr << ' ' << kc << '\n';
        if (fin.eof()){
            break;
        }
        pair<int, int> k = {kr - 'A', kc - 1};
        knights.push_back(k);
    }

    k = (int)(knights.size());

    for (int i = 0; i < k; i++) {
        find_dist(i);
    }

    int mini = INF;

    for (int x = 0; x < r; x++) {
        for (int y = 0; y < r; y++) {
            for (int i = 0; i < k; i++) {
                int sum = 0;
                for (int j = 0; j < k; j++) {
                    if (i == j) {
                        sum += dist[j][x][y][1];
                    } else {
                        sum += dist[j][x][y][0];
                    }
                }

                mini = min(mini, sum);
            }
        }
    }

    if (k == 0) {
        fout << 0 << '\n';
    } else {
        fout << mini << '\n';
    }

    /* for (int a = 0; a < 4; a++) { */
    /*     for (int b = 0; b < 2; b++) { */
    /*         for (int i = 0; i < r; i++) { */
    /*             for (int j = 0; j < c; j++) { */
    /*                 cout << dist[a][i][j][b] << ' '; */
    /*             } */

    /*             cout << '\n'; */
    /*         } */
    /*         cout << "-----\n"; */
    /*     } */
    /* } */

    return 0;
}
