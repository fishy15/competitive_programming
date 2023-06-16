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

int n;
bool card[MAXN + 1];
vector<int> e;
int pre[MAXN + 1];
int suf[MAXN + 1];

int main() {
    ifstream fin("cardgame.in");
    ofstream fout("cardgame.out");

    fin >> n;
    for (int i = 0; i < n; i++) {
        int x; fin >> x;
        card[x] = true;
        e.push_back(x);
    }

    set<int> cur;
    for (int i = 1; i <= 2 * n; i++) {
        if (!card[i]) {
            cur.insert(i);
        }
    }

    for (int i = 0; i < n; i++) {
        auto it = cur.upper_bound(e[i]);
        pre[i + 1] = pre[i];
        if (it != cur.end()) {
            pre[i + 1]++;
            cur.erase(it);
        } 
    }

    cur = {};
    for (int i = 1; i <= 2 * n; i++) {
        if (!card[i]) {
            cur.insert(-i);
        }
    }

    for (int i = 0; i < n; i++) {
        e[i] *= -1;
    }

    for (int i = n - 1; i >= 0; i--) {
        auto it = cur.lower_bound(e[i]);
        suf[i] = suf[i + 1];
        if (it != cur.end()) {
            suf[i]++;
            cur.erase(it);
        }
    }

    int ans = 0;
    for (int i = 0; i <= n; i++) {
        /* cout << pre[i] << ' ' << suf[i] << '\n'; */
        ans = max(ans, pre[i] + suf[i]);
    }

    fout << ans << '\n';

    return 0;
}
