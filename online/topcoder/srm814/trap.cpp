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

class StepLeapSurviveTraps {
public:
    ll minDamage(int n, int j, int seed, int m) {
        vector<int> t(n + 1);
        for (int i = 1; i <= n; i++) {
            seed = ((ll) seed * 1103515245 + 12345) % (1 << 31);
            t[i] = 1 + seed % m;
        }

        vector<ll> ans(n + 1, INFLL);
        ans[0] = 0;
        multiset<int> pre;
        pre.insert(0);

        for (int i = 1; i <= n; i++) {
            ans[i] = *pre.begin() + t[i];
            pre.insert(ans[i]);
            if (i >= j) pre.erase(pre.find(ans[i - j]));
        }

        return ans[n];
    }
};
