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

    array<string, 7> schedule;
    for (int i = 0; i < 7; i++) {
        cin >> schedule[i];
    }

    int d, h;
    cin >> d >> h;

    array<int, 7> perm;
    iota(perm.begin(), perm.end(), 0);

    int best = 0;

    do {
        array<int, 24> cnts{};
        for (int i = 0; i < d; i++) {
            int day = perm[i];
            for (int j = 0; j < 24; j++) {
                if (schedule[day][j] == '.') {
                    cnts[j]++;
                }
            }
        }

        sort(cnts.begin(), cnts.end(), greater<>{});
        best = max(best, accumulate(cnts.begin(), cnts.begin() + h, 0));
    } while (next_permutation(perm.begin(), perm.end()));

    auto ans = (ld) best / h / d;

    cout << fixed << setprecision(20);
    cout << ans << '\n';


    return 0;
}
