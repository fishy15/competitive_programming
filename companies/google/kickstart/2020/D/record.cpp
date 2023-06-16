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

int t; 

void solve() {
    int n; cin >> n;
    vector<int> pos;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        pos.push_back(x);
    }
    pos.push_back(0-1);

    int cur = -1;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (cur < pos[i] && pos[i] > pos[i + 1]) cnt++;
        cur = max(cur, pos[i]);
    }
    
    cout << cnt << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
