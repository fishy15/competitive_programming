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

class StepHopJumpEasy {
public:
    string solve(string level) {
        int cur = 0;
        int n = level.size();
        string ans = "";
        while (cur < n - 1) {
            if (level[cur + 1] == '-') {
                ans += 'S';
                cur++;
            } else if (cur < n - 2 && level[cur + 2] == '-') {
                ans += 'H';
                cur += 2;
            } else if (cur < n - 3 && level[cur + 3] == '-') {
                ans += 'J';
                cur += 3;
            } else {
                return "";
            }
        }

        return ans;
    }
};
