/*
ID: aaryan.1
TASK: heritage
LANG: C++11
*/

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

string in;
string pre;

int n;
int prepos[26];
int child[26][2];
ofstream fout;

int find(int l, int r) {
    if (l > r) return -1;
    int pos = l;
    for (int i = l; i <= r; i++) {
        if (prepos[in[i] - 'A'] < prepos[in[pos] - 'A']) {
            pos = i;
        }
    }

    child[pos][0] = find(l, pos - 1);
    child[pos][1] = find(pos + 1, r);
    return pos;
}

void print(int v) {
    if (child[v][0] != -1) {
        print(child[v][0]);
    }
    if (child[v][1] != -1) {
        print(child[v][1]);
    }
    fout << in[v];
}

int main() {
    ifstream fin("heritage.in");
    fout = ofstream("heritage.out");
    fin >> in >> pre;
    n = (int)(in.size());

    for (int i = 0; i < n; i++) {
        prepos[pre[i] - 'A'] = i;
    }

    int r = find(0, n - 1);
    print(r);
    fout << '\n';

    return 0;
}
