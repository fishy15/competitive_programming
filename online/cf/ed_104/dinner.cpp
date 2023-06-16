#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 150010

using namespace std;

int n1, n2, n3, n4;
int m1, m2, m3, m4;
ll cost[4][MAXN];

vector<int> bad[4][MAXN];

template<int idx>
struct cmp {
    bool operator()(int x, int y) const {
        if (cost[idx][x] == cost[idx][y]) {
            return x < y;
        }
        return cost[idx][x] < cost[idx][y];
    }
};

int main() {

    cin >> n1 >> n2 >> n3 >> n4;

    memset(cost, 0x3f, sizeof cost);

    for (int i = 0; i < n1; i++) {
        cin >> cost[0][i];
    }

    for (int i = 0; i < n2; i++) {
        cin >> cost[1][i];
    }

    for (int i = 0; i < n3; i++) {
        cin >> cost[2][i];
    }

    for (int i = 0; i < n4; i++) {
        cin >> cost[3][i];
    }

    cin >> m1;
    for (int i = 0; i < m1; i++) {
        int x, y; cin >> x >> y;
        bad[0][x - 1].push_back(y - 1);
    }

    cin >> m2;
    for (int i = 0; i < m2; i++) {
        int x, y; cin >> x >> y;
        bad[1][x - 1].push_back(y - 1);
    }

    cin >> m3;
    for (int i = 0; i < m3; i++) {
        int x, y; cin >> x >> y;
        bad[2][x - 1].push_back(y - 1);
    }

    set<int, cmp<3>> cur3;
    for (int i = 0; i < n4; i++) {
        cur3.insert(i);
    }
    for (int i = 0; i < n3; i++) {
        for (int x : bad[2][i]) {
            cur3.erase(x);
        }
        if (cur3.empty() || cost[3][*cur3.begin()] == INFLL) {
            cost[2][i] = INFLL;
        } else {
            cost[2][i] += cost[3][*cur3.begin()];
        }
        for (int x : bad[2][i]) {
            cur3.insert(x);
        }
    }

    set<int, cmp<2>> cur2;
    for (int i = 0; i < n3; i++) {
        cur2.insert(i);
    }
    for (int i = 0; i < n2; i++) {
        for (int x : bad[1][i]) {
            cur2.erase(x);
        }
        if (cur2.empty() || cost[2][*cur2.begin()] == INFLL) {
            cost[1][i] = INFLL;
        } else {
            cost[1][i] += cost[2][*cur2.begin()];
        }
        for (int x : bad[1][i]) {
            cur2.insert(x);
        }
    }

    set<int, cmp<1>> cur1;
    for (int i = 0; i < n2; i++) {
        cur1.insert(i);
    }
    for (int i = 0; i < n1; i++) {
        for (int x : bad[0][i]) {
            cur1.erase(x);
        }
        if (cur1.empty() || cost[1][*cur1.begin()] == INFLL) {
            cost[0][i] = INFLL;
        } else {
            cost[0][i] += cost[1][*cur1.begin()];
        }
        for (int x : bad[0][i]) {
            cur1.insert(x);
        }
    }

    ll min_cost = INFLL;
    for (int i = 0; i < n1; i++) {
        if (cost[0][i] < min_cost) min_cost = cost[0][i];
    }

    if (min_cost == INFLL) {
        cout << "-1\n";
    } else {
        cout << min_cost << '\n';
    }

    return 0;
}
