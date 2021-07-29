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

bool solve() {
    int n, k; cin >> n >> k;
    vector<vector<int>> s(k);

    for (int i = 0; i < k; i++) {
        int c; cin >> c;
        for (int j = 0; j < c; j++) {
            int a; cin >> a;
            s[i].push_back(a);
        }
    }

    cout << "? " << n << ' ';
    for (int i = 1; i <= n; i++) {
        cout << i << ' ';
    }
    cout << '\n';
    cout.flush();
    int mm; cin >> mm;
    if (mm == -1) return false;

    int l = 0;
    int r = k - 1;

    while (l < r) {
        int m = (l + r) / 2;
        vector<int> cur;
        for (int i = l; i <= m; i++) {
            for (int j : s[i]) {
                cur.push_back(j);
            }
        }
        cout << "? " << cur.size() << ' ';
        for (int j : cur) {
            cout << j << ' ';
        }
        cout << '\n';
        cout.flush();

        int ans; cin >> ans;
        if (ans == -1) {
            return false;
        }

        if (ans == mm) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    set<int> tot;
    for (int i = 1; i <= n; i++) {
        tot.insert(i);
    }
    for (int i : s[l]) {
        tot.erase(i);
    }

    cout << "? " << tot.size() << ' ';
    for (int i : tot) {
        cout << i << ' ';
    }
    cout << '\n';
    cout.flush();

    int temp; cin >> temp;
    if (temp == -1) return false;

    cout << "! ";
    for (int i = 0; i < k; i++) {
        if (i == l) {
            cout << temp << ' ';
        } else {
            cout << mm << ' ';
        }
    }
    cout << '\n';
    cout.flush();

    string res; cin >> res;
    if (res == "Incorrect") return false;

    return true;
}

int main() {
    int t; cin >> t;

    while (t-- && solve()) {}

    return 0;
}
