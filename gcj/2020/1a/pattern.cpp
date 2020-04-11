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
    int n; cin >> n;
    vector<string> start;
    vector<string> end;
    vector<string> a;
    string mid = "";

    string slong = "";
    string elong = "";

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        string ss = "";
        string ee = "";

        for (int i = 0; i < s.size() - 1; i++) {
            if (s[i] == '*') break;
            ss += s[i];
        }

        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == '*') break;
            ee += s[i];
        }


        start.push_back(ss);
        end.push_back(ee);
        if (ss.size() > slong.size()) slong = ss;
        if (ee.size() > elong.size()) elong = ee;

        string q = "";
        for (char c : s) {
            if (c != '*') q += c;
        }
        a.push_back(q);
    }

    for (string &cur : start) {
        for (int i = 0; i < cur.size(); i++) {
            if (cur[i] != slong[i]) {
                cout << "*\n";
                return;
            }
        }
    }

    for (string &cur : end) {
        for (int i = 0; i < cur.size(); i++) {
            if (cur[i] != elong[i]) {
                cout << "*\n";
                return;
            }
        }
    }

    cout << slong;
    for (string &q : a) cout << q;
    reverse(elong.begin(), elong.end());
    cout << elong << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
