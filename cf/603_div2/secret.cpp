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
#define MAXN 200000

using namespace std;

int dsu[MAXN + 1];
int size[MAXN + 1];

int find(int x) {
    if (dsu[x] == x) return x;
    return find(dsu[x]);
}

void join(int x, int y) {
    if ((x = find(x)) != (y = find(y))) {
        if (size[x] < size[y]) {
            dsu[x] = y;
            size[y] += size[x];
        } else {
            dsu[y] = x;
            size[x] += size[y];
        }
    }
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n; cin >> n;
    vector<string> s;
    for (int i = 0; i < n; i++) {
        string ss; cin >> ss;
        s.push_back(ss);
        dsu[i] = i;
        size[i] = 1;
    }

    for (char c = 'a'; c <= 'z'; c++) {
        int pos = -1;
        for (int i = 0; i < n; i++) {
            bool is = false;
            for (char c2 : s[i]) {
                if (c == c2) {
                    is = true;
                    //cout << c << " in " << s[i] << '\n';
                    break;
                }
            }
            if (is) {
                if (pos == -1) {
                    pos = i;
                } else {
                    //cout << c << ' ' << i << ' ' << pos << '\n';
                    join(pos, i);
                }
            }
        }
    }

    set<int> x;
    for (int i = 0; i < n; i++) {
        x.insert(find(i));
    }
    
    cout << x.size() << '\n';

    return 0;
}
