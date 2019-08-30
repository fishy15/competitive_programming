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
// :pray: :hyacllh:
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

ll r, c;
ll k;
pair<ll, ll> king;
vector<pair<ll, ll>> knights;
ll dist[780][26][30][2];
bool vist[780][26][30][2];

vector<pair<ll, ll>> moves = {
    {1, 2},
    {1, -2},
    {-1, 2},
    {-1, -2},
    {2, 1},
    {2, -1},
    {-2, 1},
    {-2, -1}
};

bool comp(const array<ll, 4> &a1, const array<ll, 4> &a2) {
    return a1[3] > a2[3];
}

void find_dist(ll i) {
    array<ll, 4> arr = {knights[i].first, knights[i].second, 0, 0};
    //priority_queue<array<ll, 4>, vector<array<ll, 4>>, decltype(&comp)>q(comp);
    queue<array<ll, 4>> q;
    q.push(arr);
    while (!q.empty()) {
        array<ll, 4> cur = q.front();
        q.pop();

        if (vist[i][cur[0]][cur[1]][cur[2]]) {
            continue;
        }

        dist[i][cur[0]][cur[1]][cur[2]] = cur[3];
        vist[i][cur[0]][cur[1]][cur[2]] = true;

        for (auto m : moves) {
            ll new_x = cur[0] + m.first;
            ll new_y = cur[1] + m.second;

            if (new_x >= 0 && new_y >= 0 && new_x < r && new_y < c) {
                if (!vist[i][new_x][new_y][0]) {
                    q.push({new_x, new_y, 0, cur[3] + 1});
                }
            }
        }
    }

    vector<pair<ll, ll>> start;
    ll mini = INF;
    for (ll j = 0; j < r; j++) {
        for (ll k = 0; k < c; k++) {
            dist[i][j][k][1] = dist[i][j][k][0] + max(abs(king.first - j), abs(king.second - k));
            if (dist[i][j][k][1] < mini) {
                start = {{j, k}};
                mini = dist[i][j][k][1];
            } else if (dist[i][j][k][1] == mini) {
                start.push_back({j, k});
            }
        }
    }

    q = {};
    priority_queue<array<ll, 4>, vector<array<ll, 4>>, decltype(&comp)>q2(comp);
    for (auto x : start) {
        q.push({x.first, x.second, 1, mini});
    }
    while (!q.empty()) {
        array<ll, 4> cur = q.top();
        q.pop();

        if (vist[i][cur[0]][cur[1]][1]) {
            continue;
        }

        //cout << cur[3] << '\n';

        dist[i][cur[0]][cur[1]][cur[2]] = cur[3];
        vist[i][cur[0]][cur[1]][cur[2]] = true;

        for (auto m : moves) {
            ll new_x = cur[0] + m.first;
            ll new_y = cur[1] + m.second;

            if (new_x >= 0 && new_y >= 0 && new_x < r && new_y < c) {
                ll d = min(dist[i][new_x][new_y][1], cur[3] + 1);
                if (!vist[i][new_x][new_y][1]) {
                    q.push({new_x, new_y, 1, d});
                }
            }
        }
    }
}

int main() {
    ifstream fin("camelot.in");
    ofstream fout("camelot.out");

    fin >> r >> c;
    char kf; ll ks; fin >> kf >> ks;
    king = {kf - 'A', ks - 1};

    //cout << king.first << ' ' << king.second << '\n';
    for (ll i = 0; i < r * c; i++) {
        char kr; ll kc; fin >> kr >> kc;
        //cout << "TEST\n";
        //cout << kr << ' ' << kc << '\n';
        if (fin.eof()){
            break;
        }
        pair<ll, ll> k = {kr - 'A', kc - 1};
        knights.push_back(k);
    }

    k = (ll)(knights.size());

    for (ll i = 0; i < k; i++) {
        find_dist(i);
    }

    ll mini = INF;

    for (ll x = 0; x < r; x++) {
        for (ll y = 0; y < r; y++) {
            for (ll i = 0; i < k; i++) {
                ll sum = 0;
                for (ll j = 0; j < k; j++) {
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

    /* for (ll a = 0; a < 4; a++) { */
    /*     for (ll b = 0; b < 2; b++) { */
    /*         for (ll i = 0; i < r; i++) { */
    /*             for (ll j = 0; j < c; j++) { */
    /*                 cout << dist[a][i][j][b] << ' '; */
    /*             } */

    /*             cout << '\n'; */
    /*         } */
    /*         cout << "-----\n"; */
    /*     } */
    /* } */

    return 0;
}
