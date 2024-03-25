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

struct team {
    string code;
    int idx;
    int score;

    bool operator<(const team &t) const {
        if (score == t.score) {
            return idx < t.idx;
        }
        return score > t.score;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n;
    cin >> n;

    vector<team> tt;
    for (int i = 0; i < n; i++) {
        string code;
        cin >> code;

        int p;
        cin >> p;

        array<int, 6> e;
        for (auto &x : e) cin >> x;

        sort(e.begin(), e.end());

        int score = 10 * p + accumulate(e.begin() + 1, e.end() - 1, 0);
        tt.push_back({code, i, score});
    }

    sort(tt.begin(), tt.end());

    set<int> at_most;

    int cnt = 0;
    for (auto &t : tt) {
        cnt++;
        at_most.insert(t.score);
        if ((cnt <= 3 || t.score == tt[2].score) && cnt <= 1000) {
            cout << t.code << ' ' << t.score << '\n';
        }
    }

    return 0;
}
