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
    string a, b; cin >> a >> b;
    
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        int apos = i / 2;
        int bpos = n - i - 1;
        if (i % 2 == 1) {
            apos = n - 1 - i / 2;
        }
        char aval = a[apos];
        if (i % 2 == 1) {
            if (aval == '0') {
                aval = '1';
            } else {
                aval = '0';
            }
        }
        char bval = b[bpos];
        if (aval == bval) {
            ans.push_back(1);
        }
        ans.push_back(n - i);
    }
    cout << ans.size() << ' ';
    for (int i : ans) {
        cout << i << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
