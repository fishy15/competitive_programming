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

constexpr int MAX_DEPTH = 30;

struct trie {
    struct resp {
        int t; // zero, one, or two
        int val;

        static resp I() {
            return {0, 0};
        }

        resp operator+(const resp other) const {
            switch (t) {
                case 0:
                    return other;
                case 1:
                    switch (other.t) {
                        case 0:
                            return *this;
                        case 1:
                            return {2, val ^ other.val};
                        case 2:
                            return other;
                    }
                case 2:
                    switch (other.t) {
                        case 0: case 1:
                            return *this;
                        case 2:
                            return {2, min(val, other.val)};
                    }
                default:
                    // should not happen
                    return I();
            }
        }
    };

    struct node {
        node *l = nullptr;
        node *r = nullptr;
        int cnt = 0;
        resp rr = resp::I();

        bool is_r;
        node(bool is_r) : is_r(is_r) {}

        void comp() {
            if (cnt == 0) {
                rr = resp::I();
            } else if (cnt == 1) {
                rr = {1, is_r ? 1 : 0};
            } else {
                rr = {2, 0};
            }
        }

        static resp get(node *v) {
            if (v == nullptr) {
                return resp::I();
            }
            return v->rr;
        }

        static int gc(node *v) {
            return v == nullptr ? 0 : v->cnt;
        }

        void add(int idx) {
            rr = get(l) + get(r);

            // if single one, then bits have influence
            if (rr.t == 1 && is_r) {
                rr.val += 1 << (idx + 1);
            }

            cnt = gc(l) + gc(r); 
        }
    };

    node *root = new node(false);

    void add(node *const cur, int x, int idx) {
        // at the end of the tree
        if (idx == -1) {
            cur->cnt++;
            cur->comp();
        } else {
            if ((x & (1 << idx)) == 0) {
                if (cur->l == nullptr) {
                    cur->l = new node(false);
                }
                add(cur->l, x, idx - 1);
            } else {
                if (cur->r == nullptr) {
                    cur->r = new node(true);
                }
                add(cur->r, x, idx - 1);
            }

            cur->add(idx);
        }
    }

    void add(int x) {
        add(root, x, MAX_DEPTH - 1);
    }

    void rem(node *const cur, int x, int idx) {
        // at the end of the tree
        if (idx == -1) {
            cur->cnt--;
            cur->comp();
        } else {
            if ((x & (1 << idx)) == 0) {
                rem(cur->l, x, idx - 1);
            } else {
                rem(cur->r, x, idx - 1);
            }

            cur->add(idx);
        }
    }

    void rem(int x) {
        rem(root, x, MAX_DEPTH - 1);
    }

    int qry() const {
        return root->rr.val;
    }

    void pr() const { pr(root, 0); cout.flush(); }
    void pr(node *v, int d) const {
        for (int i = 0; i < d; i++) cout << '\t';
        if (v == nullptr) {
            cout << "-\n";
        } else {
            cout << v->cnt << ' ' << v->rr.t << ' ' << v->rr.val << '\n';
            pr(v->l, d + 1);
            pr(v->r, d + 1);
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int q;
    cin >> q;

    trie tt;

    while (q--) {
        int t;
        cin >> t;

        if (t == 1) {
            int x;
            cin >> x;
            tt.add(x);
        } else if (t == 2) {
            int x;
            cin >> x;
            tt.rem(x);
        } else {
            cout << tt.qry() << '\n';
        }
    }

    return 0;
}
