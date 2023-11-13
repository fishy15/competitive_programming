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

bool is_upper(char c) {
    return 'A' <= c && c <= 'Z';
}

bool is_lower(char c) {
    return 'a' <= c && c <= 'z';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    string cur;
    cin >> cur;

    int my_loc = cur.find('?');
    int l = my_loc;
    int r = my_loc;
    array<bool, 26> key{};
    int no_progress = 0;
    while (l != 0 && r != n - 1) {
        l = my_loc;
        r = my_loc;
        while (l > 0 && !is_upper(cur[l - 1])) {
            l--;
            if (is_lower(cur[l])) {
                key[cur[l] - 'a'] = true;
                cur[l] = '.';
            }
        }
        while (r < n - 1 && !is_upper(cur[r + 1])) {
            r++;
            if (is_lower(cur[r])) {
                key[cur[r] - 'a'] = true;
                cur[r] = '.';
            }
        }

        bool ok = false;
        if (l != 0) {
            if (key[cur[l - 1] - 'A']) {
                cur[l - 1] = '.';
                ok = true;
            }
        }

        if (r != n - 1) {
            if (key[cur[r + 1] - 'A']) {
                cur[r + 1] = '.';
                ok = true;
            }
        }

        if (!ok) {
            no_progress++;
        }

        if (no_progress >= 10) {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";

    return 0;
}
