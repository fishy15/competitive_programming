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

pair<int, int> solve(int m) {
    string s;
    cin >> s;

    int num_occupied = count(s.begin(), s.end(), '1');
    
    // benefit for min and max
    int min_benefit = 0;
    int max_benefit = 0;
    for (int i = 0; i < m - 1; i++) {
        if (s[i] == '1' && s[i + 1] == '1') {
            min_benefit++;
            i++;
        }
    }

    for (int i = 0; i < m - 1; i++) {
        if (s[i] != '1' || s[i + 1] != '1') {
            max_benefit++;
            i++;
        }
    }

    min_benefit = min(min_benefit, m / 4);
    max_benefit = m / 4 - min(max_benefit, m / 4);

    return {num_occupied - min_benefit, num_occupied - max_benefit};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    int min_best = 0;
    int max_best = 0;

    for (int i = 0; i < n; i++) {
        auto [a, b] = solve(m);
        min_best += a;
        max_best += b;
    }

    cout << min_best << ' ' << max_best << '\n';

    return 0;
}
