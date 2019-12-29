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

struct node {
    node* child[26];
    int cnt;

    ~node() {
        for (int i = 0; i < 26; i++) {
            delete child[i];
        }
    }
};

void insert(node* cur, string &w, int pos) {
    if (pos == w.size()) return;

    int c = w[pos] - 'a';

    cur->cnt++;
    if (!cur->child[c]) {
        node* n = new node;
        cur->child[c] = n;
    }

    insert(cur->child[c], w, pos + 1);
}

void remove(node* cur, string &w, int pos) {
    if (pos == w.size()) return;

    int c = w[pos] - 'a';

    cur->cnt--;

    if (cur->cnt) {
        remove(cur->child[c], w, pos + 1);
    } else {
        delete cur;
    }
}

int query_count(node* cur, string &w, int pos) {
    if (pos == w.size()) {
        int ans = cur->cnt;
        for (int i = 0; i < 26; i++) {
            if (cur->child[i]) {
                ans -= cur->child[i]->cnt;
            }
        }

        return ans;
    }

    int c = w[pos] - 'a';

    if (cur->child[c]) {
        return query_count(cur->child[c], w, pos + 1);
    } else {
        return 0;
    }
}

int query_prefix(node* cur, string &w, int pos) {
    if (pos == w.size()) {
        return 0;
    } 

    int c = w[pos] - 'a';

    if (cur->child[c]) {
        return 1 + query_prefix(cur->child[c], w, pos + 1);
    }

    return 0;
}

int main() {
    ifstream fin("trie.in");
    ofstream fout("trie.out");

    int c;
    string w;
    node* root = new node;
    while (fin >> c >> w) {
        if (c == 0) {
            insert(root, w, 0);
        } else if (c == 1) {
            remove(root, w, 0);
        } else if (c == 2) {
            cout << query_count(root, w, 0) << '\n';
        } else {
            cout << query_prefix(root, w, 0) << '\n';
        }
    }

    return 0;
}
