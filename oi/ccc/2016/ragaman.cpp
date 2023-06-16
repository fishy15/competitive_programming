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

string a, b;
int cnt[26][2];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> a >> b;

    if (a.size() != b.size()) {
        cout << "N\n";
        return 0;
    }

    for (char c : a) {
        cnt[c - 'a'][0]++;
    }
    for (char c : b) {
        if (c != '*') {
            cnt[c - 'a'][1]++;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (cnt[i][0] < cnt[i][1]) {
            cout << "N\n";
            return 0;
        }
    }
    
    cout << "A\n";
    return 0;
    return 0;
}
