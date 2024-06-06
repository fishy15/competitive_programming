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

void solve() {
    string s;
    cin >> s;

    string a, b, c;

    int n = s.size();

    bool all_same = true;
    int first_diff = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] != s[0]) {
            all_same = false;
            first_diff = i;
            break;
        }
    }

    if (all_same) {
        a = s.substr(0, 1);
        b = s.substr(1, n-2);
        c = s.substr(n-1, 1);
    } else {
        // check if everything post first_diff is the same
        bool post_same = true;
        int second_diff = -1;
        for (int i = first_diff; i < n; i++) {
            if (s[i] != s[first_diff]) {
                post_same = false;
                second_diff = i;
                break;
            }
        }

        if (post_same) {
            // some sequence of as then sequence of bs or vice versa
            if (first_diff == n-1) {
                if (s[0] == 'a') {
                    // if its all as and a single b
                    a = s.substr(0, n-2);
                    b = s.substr(n-2, 1);
                    c = s.substr(n-1, 1);
                } else {
                    // if its all bs and a single a
                    a = s.substr(0, 1);
                    b = s.substr(1, n-2);
                    c = s.substr(n-1, 1);
                }
            } else {
                if (s[0] == 'a') {
                    // a followed by multiple bs
                    a = s.substr(0, first_diff);
                    b = s.substr(first_diff, n - first_diff - 1);
                    c = s.substr(n-1, 1);
                } else {
                    // b followed by multiple as
                    a = s.substr(0, first_diff);
                    b = s.substr(first_diff, 1);
                    c = s.substr(first_diff+1, n - first_diff - 1);
                }
            }
        } else {
            a = s.substr(0, first_diff);
            b = s.substr(first_diff, second_diff - first_diff);
            c = s.substr(second_diff, n - second_diff);
        }
    }

    cout << a << ' ' << b << ' ' << c << endl;
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
