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

int n;
int pos[MAXN];
int q[MAXN];

ll gcd(ll a, ll b) {
    if (a > b) {
        return gcd(b, a);
    }

    if (a == 0) {
        return b;
    }

    return gcd(b % a, a);
}

struct frac {
    ll n, d; 

    frac(ll a, ll b) {
        n = a;
        d = b;
    }

    bool operator<(const frac &f2) const {
        return n * f2.d < f2.n * d;
    }

    void simp() {
        if (d < 0) {
            n = -n;
            d = -d;
        }
        ll g = gcd(n, d);
        n /= g;
        d /= g;
    }
};

void solve(int i, ofstream &fout) {
    vector<bool> visited(n, false);
    vector<frac> dist;
    for (int a = 0; a < n; a++) {
        dist.push_back(frac(INF, 1));
    }

    for (int a = 0; a < n; a++) {
        pair<frac, int> top = {frac(INF, 1), 0};
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                if (dist[j] < top.first) {
                    top.first = dist[j];
                    top.second = j;
                }
            }
        }

        if (top.second == q[i]) {
            fout << top.first.n << '/' << top.first.d << '\n';
            return;
        }

        visited[top.second] = true;

        for (int j = 0; j < n; j++) {
            if (top.second != j && !visited[j]) {
                frac t = frac(pos[top.second] - pos[j], top.second - j);
                if ((t.n > 0) == (t.d > 0)) {
                    t.simp();
                    if (!(t < top.first)) {
                        if (t < dist[j]) {
                            dist[j] = t;
                        }
                    }
                }
            }
        }
    }

    fout << "-1\n";
}

int main() {
    ifstream fin("falling.in");
    ofstream fout("falling.out");

    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> pos[i];
    }

    for (int i = 0; i < n; i++) {
        fin >> q[i];
        q[i]--;
    }

    for (int i = 0; i < n; i++) {
        solve(i, fout);
    }

    return 0;
}
