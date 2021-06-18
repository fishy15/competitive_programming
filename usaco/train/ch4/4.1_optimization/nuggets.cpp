/*
ID: aaryan.1
TASK: nuggets
LANG: C++11
*/
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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n;
int nums[10];
bool dp[256*256];

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    ifstream fin("nuggets.in");
    ofstream fout("nuggets.out");

    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> nums[i];
    }

    sort(nums, nums + n);
    int g = nums[0];
    for (int i = 1; i < n; i++) {
        g = gcd(g, nums[i]);
    }

    if (g > 1) {
        fout << 0 << '\n';
    } else {
        dp[0] = true;
        int ans = 0;
        for (int i = 1; i < 256*256; i++) {
            for (int j = 0; j < n; j++) {
                if (i >= nums[j] && dp[i - nums[j]]) {
                    dp[i] = true;
                }
            }
            if (!dp[i]) ans = i;
        }
        fout << ans << '\n';
    }

    return 0;
}
