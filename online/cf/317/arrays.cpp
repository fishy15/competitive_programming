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
#define MAXN 100000

using namespace std;

int n1, n2;
int k,m ;
int a[MAXN];
int b[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n1 >> n2;
    cin >> k >> m;
    for (int i = 0; i < n1; i++) cin >> a[i];
    for (int i = 0; i < n2; i++) cin >> b[i];

    if (a[k - 1] < b[n2 - m]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}
