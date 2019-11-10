// :pray: :steph:
// :pray: :bakekaga:

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

    int n; cin >> n;
    string s; cin >> s;

    if (s == "1") {
        cout << "Yes\n";
        return 0;
    } else if (s == "0") {
        cout << "No\n";
        return 0;
    }

    int zero = 0;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == '1' && s[i + 1] == '1') {
            cout << "No\n";
            return 0;
        }
    }

    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            zero++;
        } else {
            zero = 0;
        }

        if (zero >= 3) {
            cout << "No\n";
            return 0;
        }
    }

    if (s[0] == s[1] || s[n - 2] == s[n - 1]) {
        cout << "No\n";
        return 0;
    }

    cout << "Yes\n";

    return 0;
}
