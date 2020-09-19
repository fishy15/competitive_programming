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
#define MAXN 100000

using namespace std;

class BIT {
public:
    vector<int> bit;
    
    int get_max_one(int n) {
        return n & (~n + 1);
    }

    BIT(int sz) {
        bit = vector<int>(sz + 1, 0);
    }

    int get_before(int i) {
        i++;
        int sum = 0;
        
        while (i > 0) {
            sum += bit[i];
            i -= get_max_one(i);
        }

        return sum;
    }

    void add(int i, int val) {
        i++;
        while (i < bit.size()) {
            bit[i] += val;
            i += get_max_one(i);
        }
    }
};

struct cow {
    int num;
    int priority;
    int ans;
    vector<int> child;
};

int n;
int t;
int in[MAXN];
int out[MAXN];
BIT bit(2 * MAXN);
vector<cow> cows;

void dfs(int cur) {
    in[cur] = t++;
    for (int next : cows[cur].child) {
        dfs(next);
    }
    out[cur] = t++;
}

int main() {
    ifstream fin("promote.in");
    ofstream fout("promote.out");

    fin >> n;
    for (int i = 0; i < n; i++) {
        cow c; fin >> c.priority;
        c.num = i;
        cows.push_back(c);
    }

    for (int i = 1; i < n; i++) {
        int x; fin >> x;
        cows[x - 1].child.push_back(i);
    }

    dfs(0);

    sort(cows.begin(), cows.end(), [](const cow &c1, const cow &c2) {
        return c1.priority > c2.priority;
    });

    for (int i = 0; i < n; i++) {
        cows[i].ans = bit.get_before(out[cows[i].num]) - bit.get_before(in[cows[i].num]);
        bit.add(in[cows[i].num], 1);
    }

    sort(cows.begin(), cows.end(), [](const cow &c1, const cow &c2) {
            return c1.num < c2.num;
    });

    for (int i = 0; i < n; i++) {
        fout << cows[i].ans << '\n';
    }

    return 0;
}
