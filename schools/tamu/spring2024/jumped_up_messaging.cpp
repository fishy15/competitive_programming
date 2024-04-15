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
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

string ALPHA = "abcdefghijklmnopqrstuvwxyz_,.?!():;"s;
int SZ = ALPHA.size();

int val(char c) {
    return ALPHA.find(c);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string qry;
    cin >> qry;
    int y = qry.size();

    // prompts 1 and 2
    string s, t;
    for (int i = 0; i < y; i++) {
        int idx1 = i / SZ;
        int idx2 = i % SZ;
        s += ALPHA[idx1];
        t += ALPHA[idx2];
    }

    string res1, res2;
    cout << s << endl;
    cin >> res1;
    cout << t << endl;
    cin >> res2;

    vector<int> p(y);
    vector<int> inv(y);
    for (int i = 0; i < y; i++) {
        p[i] = val(res1[i]) * SZ + val(res2[i]);
        inv[p[i]] = i;
    }

    string ans;
    for (int i = 0; i < y; i++) {
        ans += qry[inv[i]];
    }

    cout << ans << endl;

    return 0;
}
