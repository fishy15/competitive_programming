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

map<pair<int, int>, int> gen_intervals(int n) {
    vector<pair<int, int>> intervals;

    for (int len = 1; len <= n; len *= 2) {
        for (int i = 1; i + len - 1 <= n; i++) {
            intervals.push_back({i, i + len - 1});
        }
    }

    cout << intervals.size() << '\n';
    for (auto [l, r] : intervals) {
        cout << l << ' ' << r << '\n';
    }
    cout.flush();

    // generate mapping
    map<pair<int, int>, int> idx;
    for (int i = 0; i < (int) intervals.size(); i++) {
        idx[intervals[i]] = i + 1;
    }

    return idx;
}

int msb(int x) {
    int msb = 1;
    while (2 * msb <= x) msb *= 2;
    return msb;
}

void answer_qry(const map<pair<int, int>, int> &idx) {
    int q;
    cin >> q;

    while (q--) {
        int l, r;
        cin >> l >> r;

        auto m = msb(r - l + 1);
        auto a = idx.find({l, l + m - 1})->second;
        auto b = idx.find({r - m + 1, r})->second;

        cout << a << ' ' << b << endl;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    auto idx = gen_intervals(n);
    answer_qry(idx);

    return 0;
}
