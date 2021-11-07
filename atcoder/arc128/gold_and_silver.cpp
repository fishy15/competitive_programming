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
#define MAXN 200010

using namespace std;

int n;
int nums[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int l = 0;
    vector<int> ans;
    while (l < n) {
        int start = l;
        while (l + 1 < n && nums[l] < nums[l + 1]) {
            l++;
        }

        if (l == n - 1) {
            break;
        }

        int l2 = l + 1;
        while (l2 + 1 < n && nums[l2] > nums[l2 + 1]) {
            l2++;
        }

        for (int i = start; i < l; i++) {
            ans.push_back(0);
        }

        ans.push_back(1);

        for (int i = l + 1; i < l2; i++) {
            ans.push_back(0);
        }

        ans.push_back(1);

        l = l2 + 1;
    }

    ans.resize(n);

    for (int x : ans) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}
