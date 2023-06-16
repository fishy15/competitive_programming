// :pray: :fishy:

#include <iostream>
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
    cin.tie(0); ios::sync_with_stdio(0);

    string s; cin >> s;
    int n = (int)(s.size());

    for (int sz = n; sz > 1; sz--) {
        for (int i = 0; i <= n - sz; i++) {
            bool flag = false;
            for (int j = i; j < i + sz; j++) {
                if (s[j] != s[i + sz - j - 1]) {
                    flag = true;
                    break;
                }
            }

            if (flag) {
                cout << sz << '\n';
                return 0;
            }
        }
    }

    cout << 0 << '\n';

    return 0;
}
