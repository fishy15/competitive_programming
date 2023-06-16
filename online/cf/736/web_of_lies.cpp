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
#define MAXN 200010

using namespace std;

int n, m;
multiset<int> frs[MAXN];
bool is_removed[MAXN];
int removed = 0;

void add_edge(int a, int b) {
    frs[a].insert(b);
    frs[b].insert(a);

    if (a > b && !is_removed[b]) {
        is_removed[b] = true;
        removed++;
    } else if (b > a && !is_removed[a]) {
        is_removed[a] = true;
        removed++;
    }
}

void remove_edge(int a, int b) {
    frs[a].erase(frs[a].find(b));
    frs[b].erase(frs[b].find(a));

    if ((frs[a].empty() || *frs[a].rbegin() < a) && is_removed[a]) {
        is_removed[a] = false;
        removed--;
    }

    if ((frs[b].empty() || *frs[b].rbegin() < b) && is_removed[b]) {
        is_removed[b] = false;
        removed--;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        add_edge(a, b);
    }

    int q; cin >> q;
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int a, b; cin >> a >> b;
            add_edge(a, b);
        } else if (t == 2) {
            int a, b; cin >> a >> b;
            remove_edge(a, b);
        } else {
            cout << n - removed << '\n';
        }
    }

    return 0;
}
