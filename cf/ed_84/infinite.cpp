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
#define MAXN 200000

using namespace std;

int p[MAXN];
int c[MAXN];
bool visited[MAXN];

bool check(const vector<int> &v, int k) {
    for (int i = 0; i < k; i++) {
        int cc = c[v[i]];
        bool good = true;
        for (int j = i; j < (int)(v.size()); j += k) {
            if (c[v[j]] != cc) {
                good = false;
                break;
            }
        }  

        if (good) {
            return true;
        }
    }

    return false;
}

void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        visited[i] = false;
    }

    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    
    vector<vector<int>> cycles;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            vector<int> loop = {i};
            int cur = p[i];
            visited[i] = true;
            while (cur != i) {
                loop.push_back(cur);
                visited[cur] = true;
                cur = p[cur];
            }
            cycles.push_back(loop);
        }
    }

    int ans = INF;
    for (vector<int> &v : cycles) {
        int sz = (int)(v.size());
        for (int i = 1; i <= sqrt(sz); i++) {
            if (sz % i == 0) {
                bool res = check(v, i);
                if (res) {
                    ans = min(ans, i);
                }
                if (i * i != sz) {
                    bool res = check(v, sz / i);
                    if (res) {
                        ans = min(ans, sz / i);
                    }
                }
            }
        }
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
