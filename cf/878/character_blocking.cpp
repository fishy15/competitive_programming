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
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct state {
    array<string, 2> s;
    set<int> unmatch_b, unmatch_ub;

    state(string s1, string s2) : s{s1, s2} {
        for (int i = 0; i < (int) s[0].size(); i++) {
            add(i);
        }
    }

    void block(int x) {
        if (unmatch_ub.count(x)) {
            unmatch_ub.erase(x);
            unmatch_b.insert(x);
        }
    }

    void unblock(int x) {
        if (unmatch_b.count(x)) {
            unmatch_b.erase(x);
            unmatch_ub.insert(x);
        }
    }

    void add(int x) {
        if (s[0][x] != s[1][x]) {
            unmatch_ub.insert(x);
        }
    }

    void rem(int x) {
        if (s[0][x] != s[1][x]) {
            unmatch_ub.erase(x);
        }
    }

    void swap(int i1, int x1, int i2, int x2) {
        rem(x1);
        if (x1 != x2) rem(x2);

        ::swap(s[i1][x1], s[i2][x2]);

        add(x1);
        if (x1 != x2) add(x2);
    }

    bool valid() {
        return unmatch_ub.empty();
    }
};

void solve() {
    string s1, s2;
    cin >> s1 >> s2;

    int t, q;
    cin >> t >> q;

    vector<array<int, 5>> qry(q);
    for (int i = 0; i < q; i++) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int pos;
            cin >> pos;
            pos--;

            qry[i] = {1, pos, -1, -1, -1};
        } else if (ty == 2) {
            int i1, x1, i2, x2;
            cin >> i1 >> x1 >> i2 >> x2;
            i1--;
            x1--;
            i2--;
            x2--;

            qry[i] = {2, i1, x1, i2, x2};
        } else {
            qry[i] = {3, -1, -1, -1, -1};
        }
    }

    state s(s1, s2);
    for (int i = 0; i < q; i++) {
        if (i >= t && qry[i - t][0] == 1) {
            s.unblock(qry[i - t][1]);
        }

        int ty = qry[i][0];
        if (ty == 1) {
            s.block(qry[i][1]);
        } else if (ty == 2) {
            s.swap(qry[i][1], qry[i][2], qry[i][3], qry[i][4]);
        } else {
            if (s.valid()) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
