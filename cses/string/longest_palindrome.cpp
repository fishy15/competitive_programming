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

string s;

pair<vector<int>, vector<int>> manachers(string s) {
    int n = (int)(s.size());
    vector<int> d1(n);
    vector<int> d2(n);

    int l = 0;
    int r = -1;
    for (int i = 0; i < n; i++) {
        int k = 1;
        if (i <= r) k = min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    l = 0;
    r = -1;
    for (int i = 0; i < n; i++) {
        int k = 0;
        if (i <= r) k = min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n  && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }

    return {d1, d2};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s; cin >> s;
    auto [d1, d2] = manachers(s);

    int max_odd = max_element(d1.begin(), d1.end()) - d1.begin();
    int max_even = max_element(d2.begin(), d2.end()) - d2.begin();

    if (2 * d1[max_odd] - 1 > 2 * d2[max_even]) {
        cout << s.substr(max_odd - d1[max_odd] + 1, 2 * d1[max_odd] - 1) << '\n';
    } else {
        cout << s.substr(max_even - d2[max_even], 2 * d2[max_even]) << '\n';
    }

    return 0;
}
