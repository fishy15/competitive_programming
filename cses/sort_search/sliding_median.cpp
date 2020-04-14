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

int n, k;
int kk;
int nums[MAXN];
multiset<int> b;
multiset<int> f;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 0; i < k; i++) {
        f.insert(nums[i]);
    }
    
    if (k % 2 == 0) {
        kk = k / 2 - 1;
    } else {
        kk = k / 2;
    }

    while (b.size() < kk) {
        int v = *f.begin();
        f.erase(f.begin());
        b.insert(v);
    }

    cout << *f.begin() << ' ';

    for (int i = 1; i <= n - k; i++) {
        if (b.count(nums[i - 1])) {
            b.erase(b.find(nums[i - 1]));
        } else {
            f.erase(f.find(nums[i - 1]));
        }

        f.insert(nums[i + k - 1]);

        while (b.size() < kk) {
            int v = *f.begin();
            f.erase(f.begin());
            b.insert(v);
        }

        while (b.size() > 0 && *b.rbegin() > *f.begin()) {
            int a = *b.rbegin();
            int c = *f.begin();
            b.erase(--b.end());
            f.erase(f.begin());
            f.insert(a);
            b.insert(c);
        }

        cout << *f.begin() << '\n';
    } cout << '\n';

    return 0;
}
