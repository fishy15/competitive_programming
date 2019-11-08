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
    ifstream fin("empty.in");
    ofstream fout("empty.out");

    int n, k; fin >> n >> k;

    vector<int> cows(n);

    int pos = 0;

    for (int i = 0; i < k; i++) {
        ll x, y, a, b; fin >> x >> y >> a >> b;
        for (int i = 1; i <= y; i++) {
            int loc = (a * i + b) % n;
            cows[loc] += x;
            if (x > 1) pos = loc; 
        }
    }


    for (int i = 0; i < 3; i++) {
        for (int pos = 0; pos < n - 1; pos++) {
            if (cows[pos] > 1) {
                cows[pos + 1] += cows[pos] - 1;
                cows[pos] = 1;
            }
        }

        if (cows[n - 1] > 1) {
            cows[0] += cows[n - 1] - 1;
            cows[n - 1] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (cows[i] == 0) {
            fout << i << '\n';
            return 0;
        }
    }

    return 0;
}
