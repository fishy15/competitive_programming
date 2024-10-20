#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ifstream fin("dkl.in");
    ofstream fout("dkl.out");

    int d, k, l;
    fin >> d >> k >> l;

    if (k <= l && l <= d) {
        // in this case it is guaranteed possible
        vector<pii> edges;
        vector<int> clique1(d + 1), clique2(d + 1);
        iota(all(clique1), 1);
        iota(all(clique2), d+2);

        rep(i, 0, d) {
            rep(j, i+1, d+1) {
                edges.pb({clique1[i], clique1[j]});
                edges.pb({clique2[i], clique2[j]});
            }
        }

        // draw the l edges
        int betw_edges = 0;
        rep(offset, 0, k) {
            rep(i, 0, k) {
                if (betw_edges < l) {
                    int other_idx = (i + offset) % k;
                    edges.pb({clique1[i], clique2[other_idx]});
                    betw_edges++;
                }
            }
        }

        // add some other stuff in the other component
        rep(other_idx, k, d+1) {
            rep(i, 0, k) {
                if (betw_edges < l) {
                    edges.pb({clique1[i], clique2[other_idx]});
                    betw_edges++;
                }
            }
        }

        fout << 2 * d + 2 << ' ' << sz(edges) << '\n';
        for (auto [a, b] : edges) {
            fout << a << ' ' << b << '\n';
        }
    } else {
        fout << "0 0\n";
    }

    return 0;

}

