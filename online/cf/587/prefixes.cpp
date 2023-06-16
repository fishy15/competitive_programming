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
    
    int len; cin >> len;
    string s; cin >> s;
    int ans = 0;

    for (int i = 0; i < len; i += 2) {
        string sub = s.substr(i, 2);
        if (sub == "ab" || sub == "ba") {
            continue;
        } else if (sub == "aa") {
            ans++;
            s[i] = 'b';
        } else {
            ans++;
            s[i] = 'a';
        }
    }

    cout << ans << '\n' << s << '\n';

    return 0;
}
