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

struct SeeAllDifferences {
    double solve(int D, vector<int> rolled) {
        vector<double> prob(D);
        prob[0] = 1.0 / D;

        for (int i = 1; i < D; i++) {
            prob[i] = 2.0 * (D - i) / D / D;
        }

        vector<bool> done(D);
        for (int i = 0; i < (int) rolled.size() - 1; i++) {
            int diff = abs(rolled[i + 1] - rolled[i]);
            done[diff] = true;
        }

        double ans = 0;
        for (int i = 0; i < D; i++) {
            if (!done[i]) {
                ans += 1 / prob[i];
            }
        }

        return ans;
    }
};
