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
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<int> pose(n);
    for (auto &x : pose) {
        cin >> x;
        x--;
    }

    vector<vector<int>> after(m);
    vector<bool> covered(n);
    for (int i = 0; i < m; i++) {
        int sz;
        cin >> sz;

        char div;
        cin >> div;

        for (int j = 0; j < sz; j++) {
            int pet;
            cin >> pet;
            pet--;

            if (pose[pet] == i) {
                covered[pet] = true;
            } else {
                after[i].push_back(pose[pet]);
            }
        }
    }

    bool all_ok = true;
    for (auto x : covered) {
        if (!x) {
            all_ok = false;
            break;
        }
    }

    if (!all_ok) {
        cout << "NO\n";
        return 0;
    }

    vector<int> deg(m);
    queue<int> q;
    for (int i = 0; i < m; i++) {
        for (auto x : after[i]) {
            deg[x]++;
        }
    }

    for (int i = 0; i < m; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }

    int cnt = 0;
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        cnt++;

        for (auto x : after[t]) {
            deg[x]--;
            if (deg[x] == 0) {
                q.push(x);
            }
        }
    }

    if (cnt == m) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}
