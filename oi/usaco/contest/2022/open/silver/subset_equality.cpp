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

bool check(const string &s, const string &t, char c1, char c2) {
    auto it1 = s.begin();
    auto it2 = t.begin();

    while (true) {
        while (it1 != s.end() && (*it1 != c1 && *it1 != c2)) {
            it1++;
        }

        while (it2 != t.end() && (*it2 != c1 && *it2 != c2)) {
            it2++;
        }

        if (it1 == s.end() || it2 == t.end()) {
            return it1 == s.end() && it2 == t.end();
        } else {
            if (*it1 != *it2) {
                return false;
            }

            it1++;
            it2++;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s, t;
    cin >> s >> t;

    array<array<char, 26>, 26> ok{};
    for (char c1 = 'a'; c1 <= 'r'; c1++) {
        for (char c2 = c1 + 1; c2 <= 'r'; c2++) {
            ok[c1 - 'a'][c2 - 'a'] = check(s, t, c1, c2);
        }
    }

    array<int, 26> single_ok{};
    for (char c = 'a'; c <= 'r'; c++) {
        single_ok[c - 'a'] = count(s.begin(), s.end(), c) == count(t.begin(), t.end(), c);
    }

    int q;
    cin >> q;
    while (q--) {
        string qry;
        cin >> qry;

        int sz = qry.size();
        bool works = true;
        for (int i = 0; i < sz; i++) {
            for (int j = i + 1; j < sz; j++) {
                if (!ok[qry[i] - 'a'][qry[j] - 'a']) {
                    works = false;
                    goto loop_end;
                }
            }

            if (!single_ok[qry[i] - 'a']) {
                works = false;
                goto loop_end;
            }
        }

loop_end:
        cout << (works ? 'Y' : 'N');
    }

    cout << '\n';

    return 0;
}
