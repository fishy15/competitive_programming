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
    int r, p, s; cin >> r >> p >> s;
    string seq; cin >> seq;
    vector<char> ans(n);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (seq[i] == 'R') {
            if (p) {
                p--;
                ans[i] = 'P';
                cnt++;
            }
        } else if (seq[i] == 'P') {
            if (s) {
                s--;
                ans[i] = 'S';
                cnt++;
            }
        } else {
            if (r) {
                r--;
                ans[i] = 'R';
                cnt++;
            }
        }
    }

    if (cnt < (n + 1) / 2) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            if (ans[i]) {
                cout << ans[i];
            } else {
                if (p) {
                    cout << "P";
                    p--;
                } else if (r) {
                    cout << "R";
                    r--; 
                } else {
                    cout << "S";
                    s--;
                }
            }
        }
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
