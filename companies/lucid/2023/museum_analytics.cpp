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
#include <sstream>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    string trash;
    getline(cin, trash);

    map<string, int> cnt;

    for (int i = 0; i < n; i++) {
        string vote;
        getline(cin, vote);

        stringstream ss(vote);
        while (ss) {
            string cur;
            getline(ss, cur, ',');
            if (cur != "") {
                cnt[cur]++;
            }
        }
    }

    pair<int, string> best;
    for (auto [s, c] : cnt) {
        best = max(best, {c, s});
    }

    cout << best.second << '\n';
    cout << best.first << '\n';

    return 0;
}
