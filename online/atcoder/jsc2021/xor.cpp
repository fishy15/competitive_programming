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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    set<int> a;
    set<int> b;
    set<int> ans;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a.insert(x);
    }

    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        b.insert(x);
    }

    for (int x : a) {
        if (!b.count(x)) {
            ans.insert(x);
        }
    }

    for (int x : b) {
        if (!a.count(x)) {
            ans.insert(x);
        }
    }

    for (int i : ans) {
        cout << i << ' ';
    }
    cout << '\n';

    return 0;
}
