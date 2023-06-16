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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n;
vector<int> adj[6];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> v = {0, 1, 2, 3, 4};
    do {
        int a = v[0];
        int b = v[1];
        int c = v[2];

        bool ab = count(adj[a].begin(), adj[a].end(), b);
        bool ac = count(adj[a].begin(), adj[a].end(), c);
        bool bc = count(adj[b].begin(), adj[b].end(), c);

        if (ab == ac && ab == bc) {
            cout << "Happy Doggos!\n";
            return 0;
        }

    } while (next_permutation(v.begin(), v.end()));

    cout << "Sad Doggos...\n";

    return 0;
}
