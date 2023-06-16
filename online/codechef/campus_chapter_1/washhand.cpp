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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int d; cin >> d;
    vector<int> days;
    vector<int> blocked(n, false);
    for (int i = 0; i < d; i++) {
        int x; cin >> x;
        days.push_back(x - 1);
    }

    vector<int> cur;
    int curDay = 0;
    int ans = 0;
    blocked[days[0]] = true;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            ans++;
            if (i > 0 && !blocked[i] && s[i - 1] == '0') {
                cur.push_back(i - 1);
            }
            if (i < n - 1 && !blocked[i + 1] && s[i + 1] == '0') {
                cur.push_back(i + 1);
            }
        }
    }

    while(!cur.empty()) {
        curDay++;
        if (curDay < d) blocked[days[curDay]] = true;
        vector<int> cur2;
        for (int i : cur) {
            if (s[i] == '1') continue;
            ans++;
            s[i] = '1';
            if (i > 0 && !blocked[i] && s[i - 1] == '0') {
                cur2.push_back(i - 1);
            }
            if (i < n - 1 && !blocked[i + 1] && s[i + 1] == '0') {
                cur2.push_back(i + 1);
            }
        }
        cur = cur2;
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
