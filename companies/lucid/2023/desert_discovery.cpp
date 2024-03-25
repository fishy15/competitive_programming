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

struct species {
    string name;
    set<string> attr;

    int comp(const vector<string> &other_attr) {
        int same = 0;
        int diff = 0;
        for (auto x : other_attr) {
            if (attr.count(x)) {
                same++;
            } else {
                diff++;
            }
        }

        return same - diff;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    string trash;
    getline(cin, trash);
    
    vector<species> s;
    for (int i = 0; i < n; i++) {
        species cur;
        getline(cin, cur.name);

        int sz;
        cin >> sz;
        getline(cin, trash);

        for (int i = 0; i < sz; i++) {
            string s;
            getline(cin, s);
            cur.attr.insert(s);

            cout << "'" << s << "'" << '\n';
        }

        s.push_back(cur);
    }

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
        int sz;
        cin >> sz;
        getline(cin, trash);

        vector<string> attr(sz);
        for (auto &x : attr) {
            getline(cin, x);
            cout << "'" << x << "'" << '\n';
        }

        pair<int, string> best;
        for (auto &ss : s) {
            best = max(best, {ss.comp(attr), ss.name});
        }

        if (2 * best.first >= sz) {
            cout << best.second << '\n';
        } else {
            cout << "Possible New Discovery\n";
        }
    }

    return 0;
}
