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

int n, k;
bool in_lis[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;

    int last = 0;
    for (int i = 0; i < k; i++) {
        int x; cin >> x;
        in_lis[x - 1] = true;
        last = x - 1;
    }

    vector<int> p;
    deque<int> dq;

    deque<int> remain;

    for (int i = 0; i < n; i++) {
        if (in_lis[i]) {
            if (i == last) {
                remain = dq;
                dq.clear();
            } else {
                p.push_back(i);
                if (!dq.empty()) {
                    p.push_back(dq.front());
                    dq.pop_front();
                }
            }
        } else {
            dq.push_back(i);
        }
    }

    for (auto it = dq.rbegin(); it != dq.rend(); it++) {
        p.push_back(*it);
    }

    p.push_back(last);

    for (auto it = remain.rbegin(); it != remain.rend(); it++) {
        p.push_back(*it);
    }

    for (int x : p) {
        cout << x + 1 << ' ';
    }
    cout << '\n';

    return 0;
}
