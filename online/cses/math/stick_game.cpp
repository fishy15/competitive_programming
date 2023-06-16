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
#define MAXN 1000010

using namespace std;

int n, k;
int ans[MAXN];
int p[110];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        cin >> p[i];
    }

    for (int i = 1; i <= n; i++) {
        bool cur = false;
        for (int j = 0; j < k; j++) {
            if (i >= p[j]) cur |= !ans[i - p[j]];
        }
        ans[i] = cur;
    }

    for (int i = 1; i <= n; i++) {
        cout << "LW"[ans[i]];
    }
    cout << '\n';

    return 0;
}
