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
#define MAXN 100000

using namespace std;

int n;
int nums[MAXN];

bool check(int k) {
    vector<int> qq;
    for (int i = 0; i <= k; i++) {
        qq.push_back(nums[i]);
    }

    sort(qq.begin(), qq.end());

    int cnt = 1;
    for (int i : qq) {
        cout << '\t' << i << ' ' << cnt << '\n';
        if (i <= cnt) {
            return true;
        }
        cnt++;
    }

    return false;
}

int main() {
    ifstream fin("greedy.in");
    ofstream fout("greedy.out");

    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> nums[i];
        nums[i] = n - nums[i];
    }

    int l = 0;
    int r = n - 1;
    int ans = 0;
    while (l <= r) {
        int m = l + (r - l) / 2;
        bool res = check(m);
        if (res) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    cout << ans << '\n';

    fout << n - ans - 1 << '\n';

    return 0;
}
