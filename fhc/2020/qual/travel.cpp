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
    int n; cin >> n;
    string in, out; 
    cin >> in >> out;
    bool ans[55][55];
    memset(ans, 0, sizeof ans);
    for (int i = 0; i < n; i++) {
        ans[i][i] = 1;
        for (int j = i - 1; j >= 0; j--) {
            if (out[j + 1] == 'Y' && in[j] == 'Y') {
                ans[i][j] = 1;
            } else {
                break;
            }
        }

        for (int j = i + 1; j < n; j++) {
            if (out[j - 1] == 'Y' && in[j] == 'Y') {
                ans[i][j] = 1;
            } else {
                break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "NY"[ans[i][j]];
        }
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": \n";
        solve();
    }

    return 0;
}
