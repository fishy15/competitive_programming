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

class Scoreboard {
public:
    int getScore(string s) {
        map<char, int> m = {
            {'B', 1000},
            {'b', 250},
            {'R', 50},
            {'J', 10000},
            {'D', 20000}
        };

        int ans = 0;
        for (char c : s) {
            ans += m[c];
        }

        return ans;
    }
};
