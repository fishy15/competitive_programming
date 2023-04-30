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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s, t;
    cin >> s >> t;

    int m = t.size();

    // if we match that many characters
    vector<bool> front_possible(m + 1);
    vector<bool> back_possible(m + 1);

    front_possible[0] = true;
    for (int i = 0; i < m; i++) {
        if (s[i] != '?' && t[i] != '?' && s[i] != t[i]) {
            break;
        }

        front_possible[i + 1] = true;
    }

    back_possible[0] = true;
    for (int i = 0; i < m; i++) {
        auto s_cur = s.rbegin()[i];
        auto t_cur = t.rbegin()[i];
        if (s_cur != '?' && t_cur != '?' && s_cur != t_cur) {
            break;
        }

        back_possible[i + 1] = true;
    }

    for (int i = 0; i <= m; i++) {
        if (front_possible[i] && back_possible[m - i]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
