/*
 * Player 2 will win if the xor of the remaining values is 0, so we want to figure out how many ways there
 * are to pick a multiple of d elements which have an xor equal to the xor of the entire set. We can keep
 * track of the number of objects taken mod d, and we can store in dp[i][j] how many ways there are to
 * get an xor of i by removing x objects such that x % d == j. After sorting the array, we can solve this
 * for successive prefixes. The max number we need to process for i is the power of 2 above a_i, so the 
 * overall complexity is O(sum(a_i)). To ensure we fit in the memory limit, we only need one array, and we
 * can process j and j ^ a_i at the same time to make sure we don't double count.
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
#include <cstdio>
#include <cstring>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 500010

using namespace std;

int n, d;
int nums[MAXN];
int combo[1 << 20][10];
int high[10];
int low[10];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> d;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    sort(nums, nums + n);

    int p = 0;
    combo[0][0] = 1;
    int cur = 0;
    for (int i = 0; i < n; i++) {
        while ((1 << p) < nums[i]) p++;
        cur ^= nums[i];
        for (int j = 0; j < (1 << p); j++) {
            if (j < (j ^ nums[i])) {
                for (int k = 0; k < d; k++) {
                    low[k] = combo[j][k];
                    high[k] = combo[j ^ nums[i]][k];
                }
                for (int k = 0; k < d; k++) {
                    int nxt = (k + 1) % d;
                    combo[j][nxt] += high[k];
                    if (combo[j][nxt] >= MOD) combo[j][nxt] -= MOD;
                    combo[j ^ nums[i]][nxt] += low[k];
                    if (combo[j ^ nums[i]][nxt] >= MOD) combo[j ^ nums[i]][nxt] -= MOD;
                }
            }
        }
    }

    if (n % d == 0) {
        combo[cur][0] -= 1;
        if (combo[cur][0] < 0) combo[cur][0] += MOD;
    }

    cout << combo[cur][0] << '\n';

    return 0;
}
