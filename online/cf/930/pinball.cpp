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

template<typename T>
T qry(const vector<T> &v, int l, int r) {
    return v[r] - v[l];
}

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    // just as defaults
    s = ">" + s + "<";
    n += 2;

    vector<ll> left(n + 1);
    vector<int> leftc(n + 1);
    for (int i = 0; i < n; i++) {
        left[i + 1] += left[i];
        leftc[i + 1] += leftc[i];
        if (s[i] == '>') {
            left[i + 1] += i;
            leftc[i + 1]++;
        }
    }

    vector<ll> right(n + 1);
    vector<int> rightc(n + 1);
    for (int i = 0; i < n; i++) {
        right[i + 1] += right[i];
        rightc[i + 1] += rightc[i];
        if (s[i] == '<') {
            right[i + 1] += i;
            rightc[i + 1]++;
        }
    }

    // answer queries
    for (int i = 1; i < n - 1; i++) {
        auto left_to_left = qry(leftc, 0, i);
        auto right_to_right = qry(rightc, i+1, n);

        /* cout << i << ' ' << left_to_left << ' ' << right_to_right << '\n'; */

        /* auto sum_lefts = 2 * ((ll) left_to_left * i - qry(left, 0, i)); */
        /* auto sum_rights = 2 * (qry(right, i+1, n) - (ll) right_to_right * i); */

        ll ans;
        if (left_to_left < right_to_right || (left_to_left == right_to_right && s[i] == '<')) {
            // will leave on the left
            
            if (s[i] == '<') {
                right_to_right = left_to_left - 1;
            } else {
                right_to_right = left_to_left;
            }
            
            int l = i+1;
            int r = n+1;
            int res = -1;
            while (l <= r) {
                int m = (l + r) / 2;
                if (qry(rightc, i+1, m) >= right_to_right) {
                    res = m;
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }

            auto sum_lefts = 2 * ((ll) left_to_left * i - qry(left, 0, i));
            auto sum_rights = 2 * (qry(right, i+1, res) - (ll) right_to_right * i);

            ans = sum_lefts + sum_rights - i; 
        } else {
            if (s[i] == '>') {
                left_to_left = right_to_right - 1;
            } else {
                left_to_left = right_to_right;
            }

            int l = 0;
            int r = i;
            int res = -1;
            while (l <= r) {
                int m = (l + r) / 2;
                if (qry(leftc, m, i) >= left_to_left) {
                    res = m;
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }

            auto sum_lefts = 2 * ((ll) left_to_left * i - qry(left, res, i));
            auto sum_rights = 2 * (qry(right, i+1, n) - (ll) right_to_right * i);

            ans = sum_lefts + sum_rights - ((n - 1) - i); 
        }

        cout << ans << ' ';
    }
    cout << '\n';
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
