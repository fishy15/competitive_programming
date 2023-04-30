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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    set<int> ppl;
    for (int i = 1; i <= n; i++) {
        ppl.insert(i);
    }

    auto nxt = [&ppl](auto it) {
        it++;
        if (it == ppl.end()) {
            it = ppl.begin();
        }
        return it;
    };

    auto it = ppl.begin();
    while (!ppl.empty()) {
        it = nxt(it);
        cout << *it << ' ';

        auto nxt_it = nxt(it);
        ppl.erase(it);
        it = nxt_it;
    }

    cout << '\n';

    return 0;
}
