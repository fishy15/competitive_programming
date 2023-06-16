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
#define MAXN 400000

using namespace std;

int dist[MAXN];
int dist2[MAXN];
bool vis[MAXN];
vector<int> mul = {40320, 5040, 720, 120, 24, 6, 2, 1, 0};

int ckmin(int &a, int b) {
    return a = min(a, b);
}

int calc(vector<int> nums) {
    int res = 0;
    for (int &i : nums) i--;

    for (int i = 0; i < 9; i++) {
        res += mul[i] * nums[i];
        for (int j = i + 1; j < 9; j++) {
            if (nums[i] < nums[j]) nums[j]--;
        }
    }

    return res;
}

void d(vector<int> nums, int *dd) {
    queue<vector<int>> q;
    q.push(nums);

    for (int i = 0; i < MAXN; i++) {
        dd[i] = INF;
        vis[i] = 0;
    }

    int cc = calc(nums);
    dd[cc] = 0;
    vis[cc] = true;

    while (true) {
        vector<int> v = q.front();
        q.pop();
        int val = calc(v);
        if (dd[val] >= 8) break;

        for (int i = 0; i < 9; i++) {
            if (i % 3 != 2) {
                swap(v[i], v[i + 1]);
                int val2 = calc(v);
                if (!vis[val2]) {
                    dd[val2] = dd[val] + 1;
                    vis[val2] = true;
                    q.push(v); 
                }
                swap(v[i], v[i + 1]);
            }
        }

        for (int i = 0; i < 6; i++) {
            swap(v[i], v[i + 3]);
            int val2 = calc(v);
            if (!vis[val2]) {
                dd[val2] = dd[val] + 1;
                vis[val2] = true;
                q.push(v); 
            }
            swap(v[i], v[i + 3]);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    vector<int> nums(9);

    for (int i = 0; i < 9; i++) cin >> nums[i];

    d(nums, dist);
    d({1, 2, 3, 4, 5, 6, 7, 8, 9}, dist2);

    int ans = dist[0];
    for (int i = 0; i < MAXN; i++) {
        ckmin(ans, dist[i] + dist2[i]); 
    }

    cout << ans << '\n';

    return 0;
}
