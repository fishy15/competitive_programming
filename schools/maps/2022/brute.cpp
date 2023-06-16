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
#define MAXN 10000000000

using namespace std;

int p[MAXN];

vector<pair<int, int>> factor(int x) {
    vector<pair<int, int>> ans;
    while (x > 1) {
        int pp = p[x];
        x /= pp;

        if (ans.empty() || ans.back().first != pp) {
            ans.push_back({pp, 1});
        } else {
            ans.back().second++;
        }
    }

    return ans;
}

bool check(int x) {
    auto factors = factor(x);
    
    ll fnn = 1;
    for (auto [_, e] : factors) {
        fnn *= x * e + 1;
    }

    auto factors2 = factor(fnn);
    ll ffnn = 1;
    for (auto [_, e] : factors2) {
        ffnn *= e + 1;
    }

    return x % ffnn == 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (ll i = 2; i < MAXN; i++) {
        if (p[i] == 0) {
            p[i] = i;
            for (ll j = i * i; j < MAXN; j += i) {
                p[j] = i;
            }
        }
    }

    int x = 1;
    while (true) {
        cout << "checking " << x << endl;
        if (check(x)) cout << x << endl;
        x += 2;
    }

    return 0;
}
