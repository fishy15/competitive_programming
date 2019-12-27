// :pray: :steph:
// :pray: :bakekaga:

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

    cout << "a" << '\n' << flush;
    int a; cin >> a;
    string s = "";
    int n;
    if (a == 0) {
        cout << "a" << '\n' << flush;
        return 0;
    } else if (a == 300) {
        for (int i = 0; i < 300; i++) {
            cout << "b";
        }
        cout << '\n' << flush;
        return 0;
    }

    n = a + 1;
    for (int i = 0; i < n; i++) {
        s += "a";
    }

    cout << s << '\n' << flush;
    int base; cin >> base;

    if (base >= n) {
        for (int i = 0; i < n - 1; i++) {
            cout << "b";
        } 
        cout << '\n' << flush;
        int res; cin >> res;
        return 0;
    } else if (base == 0) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        s[i] = 'b'; 
        cout << s << '\n' << flush;
        int res; cin >> res;
        if (res < 1) {
            return 0;
        } else if (res > base) {
            s[i] = 'a';
        } else {
            base = res;
        }
    }

    return 0;
}
