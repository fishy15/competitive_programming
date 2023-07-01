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

struct person {
    ll a, b, idx;

    bool operator<(const person &p) const {
        auto us_val = a * (p.a + p.b);
        auto them_val = p.a * (a + b);
        if (us_val == them_val) {
            return idx < p.idx;
        }
        return us_val > them_val;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<person> ppl;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        ppl.push_back({a, b, i});
    }

    sort(ppl.begin(), ppl.end());

    for (const auto &p : ppl) {
        cout << p.idx + 1 << ' ';
    }
    cout << '\n';

    return 0;
}
