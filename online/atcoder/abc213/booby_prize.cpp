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
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<pair<int, int>> ppl(n);

    for (int i = 0; i < n; i++) {
        cin >> ppl[i].first;
        ppl[i].second = i + 1;
    }

    sort(ppl.begin(), ppl.end());
    cout << ppl[n - 2].second << '\n';

    return 0;
}
