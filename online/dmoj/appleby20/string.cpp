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

int n, m;
string s, t;

vector<int> pos[26];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> s >> t;

    for (int i = 0; i < n; i++) {
        pos[s[i] - 'a'].push_back(i);
    }

    int cur_copy = 0;
    int cur_idx = -1;
    for (int i = 0; i < m; i++) {
        int c = t[i] - 'a';
        if (pos[c].empty()) {
            cout << "-1\n";
            return 0;
        }
        if (upper_bound(pos[c].begin(), pos[c].end(), cur_idx) == pos[c].end()) {
            cur_copy++;
            cur_idx = pos[c][0];
        } else {
            cur_idx = *upper_bound(pos[c].begin(), pos[c].end(), cur_idx);
        }
    }

    cout << (ll)cur_copy * n + cur_idx + 1 << '\n';

    return 0;
}
