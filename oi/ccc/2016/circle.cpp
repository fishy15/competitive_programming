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
#define MAXN 100010

using namespace std;

ll n, t;
string s;
int arr[MAXN];
int nxt[MAXN];

int& get(int *arr, int x) {
    if (x < 0) x += n;
    if (x >= n) x -= n;
    return arr[x];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> t;
    cin >> s;
    for (int i = 0; i < n; i++) {
        arr[i] = s[i] - '0';
    }

    for (int i = 0; i < 51; i++) {
        if ((1L << i) & t) {
            ll d = 1L << i;
            d %= n;
            for (int j = 0; j < n; j++) {
                get(nxt, j + d) ^= get(arr, j);
                get(nxt, j - d) ^= get(arr, j);
            }
            for (int j = 0; j < n; j++) {
                arr[j] = nxt[j];
                nxt[j] = 0;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << arr[i];
    }
    cout << '\n';

    return 0;
}
