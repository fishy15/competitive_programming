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

bool can_make(const vector<int> &a, int val) {
    for (auto x : a) {
        if (x % val != 0) {
            if (val > ((x + 1) / 2) - 1) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }

    auto mn = *min_element(a.begin(), a.end());
    if (can_make(a, mn)) {
        cout << mn << '\n';
    } else {
        cout << mn / 2 << '\n';
    }
    

    return 0;
}

