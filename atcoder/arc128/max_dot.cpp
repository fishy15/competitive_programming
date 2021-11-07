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

int n, m, s;
int nums[MAXN];

ld solve(int r, ld max, ld left) {
    if (r < 0) return 0;

    vector<ld> div(r);
    ll sum = 0;
    for (int i = r - 1; i >= 0; i--) {
        sum += nums[i];
        div[i] = (ld) sum / (r - i);
    }

    int m_loc = max_element(div.begin(), div.end()) - div.begin();
    int len = r - m_loc;

    if (left / len <= max) {
        return left * div[m_loc];
    } else {
        left -= len * max;
        return div[m_loc] * len * max + solve(m_loc, max, left);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> s;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << fixed << setprecision(12) << solve(n, m, s) << '\n';

    return 0;
}
