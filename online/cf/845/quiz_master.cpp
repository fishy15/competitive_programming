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
#define MAXN 100000

using namespace std;

vector<int> factors_of[MAXN + 1];

void precomp() {
    for (int i = 1; i <= MAXN; i++) {
        for (int j = i; j <= MAXN; j += i) {
            factors_of[j].push_back(i);
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    set<int> nums;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        nums.insert(x);
    }

    map<int, vector<int>> person_can_do;
    vector<deque<int>> topic_needed(m + 1);
    for (auto x : nums) {
        for (int i : factors_of[x]) {
            if (i <= m) {
                person_can_do[x].push_back(i);
                topic_needed[i].push_back(x);
            }
        }
    }

    set<int> cur;
    for (int i = 1; i <= m; i++) {
        if (topic_needed[i].empty()) {
            cout << "-1\n";
            return;
        } else {
            cur.insert(topic_needed[i][0]);
        }
    }

    auto calc = [&]() { return *cur.rbegin() - *cur.begin(); };
    int ans = calc();

    for (auto [a, does] : person_can_do) {
        if (cur.count(a)) {
            cur.erase(a);
            for (auto t : does) {
                topic_needed[t].pop_front();
                if (topic_needed[t].empty()) {
                    goto done;
                } else {
                    cur.insert(topic_needed[t][0]);
                }
            }

            ans = min(ans, calc());
        }
    }

done:
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
