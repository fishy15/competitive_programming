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
    int n, k; cin >> n >> k;
    string s; cin >> s;
    vector<set<int>> vals(k);
    for (int i = 0; i < n; i++) {
        if (s[i] != '?') {
            vals[i % k].insert(s[i] - '0');
            if (vals[i % k].size() > 1) {
                cout << "NO\n";
                return;
            }
        } else {
            if (!vals[i % k].empty()) {
                s[i] = *vals[i % k].begin() + '0';
            }
        }
    }
    int zerocnt = 0;
    int onecnt = 0;
    int idk = 0;
    for (int i = 0; i < k; i++) {
        if (s[i] == '0') {
            zerocnt++;
        } else if (s[i] == '1') {
            onecnt++;
        } else {
            idk++;
        }
    }
    if (abs(zerocnt - onecnt) > idk) {
        cout << "NO\n";
        return;
    }
    for (int i = k; i < n; i++) {
        if (s[i - k] == '0') {
            zerocnt--;
        } else if (s[i - k] == '1') {
            onecnt--;
        } else {
            idk--;
        }
        if (s[i] == '0') {
            zerocnt++;
        } else if (s[i] == '1') {
            onecnt++;
        } else {
            idk++;
        }
        if (abs(zerocnt - onecnt) > idk) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
