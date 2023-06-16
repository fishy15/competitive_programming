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
#define MAXN 2000010

using namespace std;

string s;
string pattern;
string tot;
int p[MAXN];
int ans;
int sz;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s >> pattern;
    tot = pattern + "#" + s;
    sz = (int)(tot.size());

    for (int i = 1; i < sz; i++) {
        int j =  p[i - 1];
        while (j > 0 && tot[i] != tot[j]) j = p[j - 1];
        if (tot[i] == tot[j]) j++;
        p[i] = j;
        if (p[i] == pattern.size()) ans++;
    }

    cout << ans << '\n';

    return 0;
}
