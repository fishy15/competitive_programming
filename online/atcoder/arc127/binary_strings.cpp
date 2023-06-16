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

int n;
string x;

bool subtract(int shift) {
    for (int i = n - shift - 1; i >= 0; i--) {
        if (x[i] == '0') {
            x[i] = '1';
        } else {
            x[i] = '0';
            return false;
        }
    }

    return true;
}

void answer(string res) {
    cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    cin >> x;

    reverse(x.begin(), x.end());
    while ((int) x.size() < n) x += '0';
    reverse(x.begin(), x.end());

    if (subtract(0)) {
        cout << "0\n";
        return 0;
    }

    string res = "1";
    for (int i = 0; i < n; i++) {
        if (x[i] == '0') {
            if (subtract(0)) {
                answer(res);
                return 0;
            } else {
                res += '0';
            }
        } else {
            subtract(n - i - 1);
            res += '1';
        }
    }

    answer(res);

    return 0;
}
