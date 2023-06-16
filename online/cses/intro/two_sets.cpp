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
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;

    if (n % 4 == 1 || n % 4 == 2) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    if (n % 4 == 3) {
        cout << n / 2 + 1 << '\n';
        cout << "1 2 ";
        for (int i = 1; i <= n / 4; i++) {
            cout << 4 * i << ' ' << 4 * i + 3 << ' ';
        }
        cout << '\n';
        cout << n / 2 << '\n';
        cout << "3 ";
        for (int i = 1; i <= n / 4; i++) {
            cout << 4 * i + 1 << ' ' << 4 * i + 2 << ' ';
        }
        cout << '\n';
        return 0;
    }

    cout << n / 2 << '\n';
    for (int i = 0; i < n / 4; i++) {
        cout << 4 * i + 1 << ' ' << 4 * i + 4 << ' ';
    } cout << '\n';
    cout << n / 2 << '\n';
    for (int i = 0; i < n / 4; i++) {
        cout << 4 * i + 2 << ' ' << 4 * i + 3 << ' ';
    } cout << '\n';

    return 0;
}
