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

void add_into(int x, int y, int a, int b, set<pair<int, int>> &s) {
    s.insert({x + a, y + b});
    s.insert({x - a, y + b});
    s.insert({x + a, y - b});
    s.insert({x - a, y - b});
}

void solve() {
    int a, b;
    cin >> a >> b;
    int xk, yk;
    cin >> xk >> yk;
    int xq, yq;
    cin >> xq >> yq;

    set<pair<int, int>> knight_k, knight_q;
    add_into(xk, yk, a, b, knight_k);
    add_into(xk, yk, b, a, knight_k);
    add_into(xq, yq, a, b, knight_q);
    add_into(xq, yq, b, a, knight_q);

    int cnt = 0;
    for (auto p : knight_k) {
        if (knight_q.count(p)) {
            cnt++;
        }
    }

    cout << cnt << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
