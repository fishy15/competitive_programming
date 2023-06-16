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
array<int, 2> jobs[MAXN];

vector<int> now() {
    multiset<int> use_end;
    vector<int> ans;

    int future_done = 0;
    for (int i = 0; i < n; i++) {
        while (!use_end.empty() && *use_end.begin() <= jobs[i][0]) {
            use_end.erase(use_end.begin());
        }

        int end = jobs[i][0] + jobs[i][1];
        if ((int) use_end.size() < k) {
            use_end.insert(end);
            future_done++;
        }

        ans.push_back(future_done);
    }

    return ans;
}

vector<int> best() {
    multiset<int> use_end;
    vector<int> ans;

    int future_done = 0;
    for (int i = 0; i < n; i++) {
        while (!use_end.empty() && *use_end.begin() <= jobs[i][0]) {
            use_end.erase(use_end.begin());
        }

        int end = jobs[i][0] + jobs[i][1];
        if ((int) use_end.size() < k) {
            use_end.insert(end);
            future_done++;
        } else {
            if (end < *use_end.rbegin()) {
                use_end.erase(prev(use_end.end()));
                use_end.insert(end);
            }
        }

        ans.push_back(future_done);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> jobs[i][0] >> jobs[i][1];
    }

    auto be = best();
    auto no = now();

    for (int i = 0; i < n; i++) {
        cout << be[i] - no[i] << '\n';
    }

    return 0;
}
