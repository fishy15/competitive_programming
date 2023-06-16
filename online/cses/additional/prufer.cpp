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

int n;
int par[MAXN];
int deg[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n - 2; i++) {
        cin >> par[i];
        par[i]--;
        deg[par[i]]++;
    }

    set<int> cur;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            cur.insert(i);
        }
    }

    for (int i = 0; i < n - 2; i++) {
        int x = *cur.begin();
        cur.erase(x);

        cout << x + 1 << ' ' << par[i] + 1 << '\n';
        deg[par[i]]--;

        if (deg[par[i]] == 0) {
            cur.insert(par[i]);
        }
    }

    cout << *cur.begin() + 1 << ' ' << *cur.rbegin() + 1 << '\n';

    return 0;
}
