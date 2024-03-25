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

    int n;
    cin >> n;

    map<string, int> loc;
    set<int> rele;
    for (int i = 0; i < n; i++) {
        string s;
        int l;
        cin >> s >> l;
        loc[s] = l;

        if (l != 0) {
            rele.insert(l);
        }
    }

    map<int, vector<string>> all_end;
    for (auto [s, x] : loc) {
        if (x != 0) {
            all_end[x].push_back(s);
        }
    }

    for (auto x : rele) {
        cout << x;
        auto &v = all_end[x];
        if (v.empty()) {
            cout << " n/a\n";
        } else {
            for (auto s : v) {
                cout << ' ' << s;
            }
            cout << '\n';
        }
    }

    return 0;
}
