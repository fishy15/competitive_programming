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

    for (int p = 13; p >= 1; p--) {
        int num = ((2 << p) - 1) * (2 << (p - 1)); 
        if (n % num == 0) {
            cout << num << '\n';
            return 0;
        }
    }

    cout << 1 << '\n';

    return 0;
}
