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

vector<array<int, 26>> nxt_occur(const string &s) {
    int n = s.size();

    vector<array<int, 26>> res(n + 1);
    res.back().fill(-1);

    for (int i = n - 1; i >= 0; i--) {
        res[i] = res[i + 1];
        res[i][s[i] - 'a'] = i + 1;
    }

    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s, t;
    cin >> s >> t;

    auto nxt = nxt_occur(s);
    int idx = 0;
    int days = 1;

    for (char c : t) {
        idx = nxt[idx][c - 'a'];
        if (idx == -1) {
            days++;
            idx = nxt[0][c - 'a'];
        }
    }

    cout << days << '\n';

    return 0;
}
