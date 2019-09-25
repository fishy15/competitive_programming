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

    int n; cin >> n;
    int one = 0;
    int two = 0;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x == 1) {
            one++;
        } else {
            two++;
        }
    }

    if (two > 0 && one > 0) {
        cout << "2 1 ";
        for (int i = 0; i < two - 1; i++) {
            cout << "2 ";
        }
        for (int i = 0; i < one - 1; i++) {
            cout << "1 ";
        }
    } else {
        for (int i = 0; i < two; i++) {
            cout << "2 ";
        }
        for (int i = 0; i < one; i++) {
            cout << "1 ";
        }
    }

    return 0;
}
