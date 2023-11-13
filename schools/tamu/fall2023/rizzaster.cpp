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

    int n;
    cin >> n;

    vector<pair<int, bool>> ppl(n);
    for (int i = 0; i < n; i++) {
        int x;
        char c;
        cin >> x >> c;

        ppl[i] = {x, c == 'L'};
    }

    sort(ppl.begin(), ppl.end());

    int ans = 0;
    if (ppl[0].second) {
        ans += ppl[0].first - 17;
    }

    for (int i = 0; i < n - 1; i++) {
        int int_size = ppl[i + 1].first - ppl[i].first - 1;
        if (ppl[i].second != ppl[i + 1].second) {
            ans += int_size / 2;
        } else if (ppl[i].second && ppl[i + 1].second) {
            ans += int_size;
        }
    }

    if (ppl.back().second) {
        ans += 1'000'000'000 - ppl.back().first;
    }

    for (auto p : ppl) {
        if (p.second) {
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}
