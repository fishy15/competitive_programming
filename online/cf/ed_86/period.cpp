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
    string s; cin >> s;
    int n = (int)(s.size());

    set<char> s2;
    for (char c : s) {
        s2.insert(c);
    }

    if (s2.size() == 1) {
        cout << s << '\n';
    } else {
        for (int i = 0; i < n; i++) {
            cout << "01";
        } cout << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
