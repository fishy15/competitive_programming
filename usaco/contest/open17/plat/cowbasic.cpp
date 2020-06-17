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
#include <cstring>
#include <sstream>
#include <stack>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n = 10;

struct M {
    const static int maxn = 101;
    ll m[maxn][maxn];
    M() { memset(m, 0, sizeof m); }
    M operator*(const M& m2) {
        M res;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int a = 0; a < n; a++) {
                    res.m[i][j] += m[i][a] * m2.m[a][j];
                    if (res.m[i][j] >= MOD) res.m[i][j] %= MOD;
                }
            }
        }
        return res;
    }
    static M pow(M &m, int e) {
        M res = I();
        while (e) {
            if (e & 1) res = res * m;
            m = m * m;
            e >>= 1;
        }
        return res;
    }
    static M I() {
        M m;
        for (int i = 0; i < maxn; i++) m.m[i][i] = 1;
        return m;
    }
};

struct level {
    int loop;
    M cur;
    level(int n) : loop(n), cur(M::I()) {} 
};

vector<vector<string>> program;
map<string, int> var;
stack<level> st;

int main() {
    ifstream fin("cowbasic.in");
    ofstream fout("cowbasic.out");

    string line;
    int cnt = 1;
    st.push(1);
    while (getline(fin, line)) {
        vector<string> v;
        stringstream ss(line);
        string cur;
        while (getline(ss, cur, ' ')) {
            if (cur != "") { 
                if ('a' <= cur[0] && cur[0] <= 'z') {
                    if (!var.count(cur)) {
                        var[cur] = cnt++;
                    }
                }
                if (cur != "(" && cur != ")" && cur != "+" && cur != "{") v.push_back(cur);
            }
        }
        n = (int)(var.size()) + 3;
        if (v[0][0] == 'R') {
            int qq = var[v[1]];
            fout << st.top().cur.m[0][qq] << '\n';
        } if ('0' <= v[0][0] && v[0][0] <= '9') {
            st.push(stoi(v[0]));
        } else if (v[0][0] != '}') {
            M stat = M::I();
            int val = var[v[0]];
            stat.m[val][val] = 0;
            for (int i = 1; i < v.size(); i++) {
                if ('a' <= v[i][0] && v[i][0] <= 'z') {
                    stat.m[var[v[i]]][val]++;
                } else if ('0' <= v[i][0] && v[i][0] <= '9') {
                    int qq = stoi(v[i]);
                    stat.m[0][val] += qq;
                    if (stat.m[0][val] >= MOD) stat.m[0][val] -= MOD;
                }
            }
            st.top().cur = st.top().cur * stat;
        } else {
            auto t = st.top();
            st.pop();
            t.cur = M::pow(t.cur, t.loop);
            st.top().cur = st.top().cur * t.cur;
        }
    }

    return 0;
}
