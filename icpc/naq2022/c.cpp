#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    string tot = "";
    string prev = "";
    string cur;
    while (getline(cin, cur)) {
    	swap(prev, tot);
    	merge(prev.begin(), prev.end(), cur.begin(), cur.end(), tot.begin());
    }
    
    cout << tot << '\n';

    return 0;
}

