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
#define MAXN 1000000

using namespace std;

void solve() {
    string s; cin >> s;
    int n = s.size();

    vector<pair<char, int>> v;
    string s2 = s;

    int cnt[26]{};
    for (int i = 0; i < n; i++) {
        v.push_back({s[i], i});
        cnt[s[i] - 'a']++;
    }

    int max_cnt = *max_element(cnt, cnt + 26);

    sort(v.begin(), v.end());
    sort(s2.begin(), s2.end());
    rotate(s2.begin(), s2.begin() + max_cnt, s2.end());

    for (int i = 0; i < n; i++) {
        v[i].first = s2[i];
    }

    sort(v.begin(), v.end(), [](const auto &a, const auto &b) {
        return a.second < b.second;
    });

    for (int i = 0; i < n; i++) {
        if (s[i] == v[i].first) {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << v[i].first;
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
