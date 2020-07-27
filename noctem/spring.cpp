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

int n;
int nums[4010];
ll dp[4010];

int main() {
    ifstream fin("spring.in");
    ofstream fout("spring.out");

    fin >> n;
    for (int i = 0; i < n; i++) fin >> nums[i];

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll mm = 0;
        for (int j = 0; j < i; j++) {
            if (nums[j] <= nums[i]) mm = max(mm, dp[j]);
        }
        dp[i] = mm + nums[i];
        ans = max(ans, dp[i]);
    }

    fout << ans << '\n';


    return 0;
}
