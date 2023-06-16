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

void check(int x, const vector<int> &a, const vector<int> &b, set<int> &ans) {
    vector<int> a2;
    for (int v : a) {
        a2.push_back(v ^ x);
    }

    sort(a2.begin(), a2.end());
    if (a2 == b) {
        ans.insert(x);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<int> a(n);
    vector<int> b(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    sort(b.begin(), b.end());

    set<int> ans;
    for (int v : b) {
        check(a[0] ^ v, a, b, ans);
    }

    cout << ans.size() << '\n';
    for (int x : ans) {
        cout << x << '\n';
    }

    return 0;
}
