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

    string s1, s2; cin >> s1 >> s2;
    sort(s2.rbegin(), s2.rend());

    int pos = 0;
    for (int i = 0; i < s1.size(); i++) {
        if (s1[i] < s2[pos]) {
            s1[i] = s2[pos];
            pos++;
        }

        if (pos == s2.size()) break;
    }

    cout << s1 << '\n';

    return 0;
}
