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
#define MAXN 1000

using namespace std;

int n, m;
string grid[MAXN];
vector<int> tree[MAXN];

int main() {
    ifstream fin("cave.in");
    ofstream fout("cave.out");

    fin >> n >> m;
    for (int i = 0; i < n; i++) {
        fin >> grid[i];
    }    

    return 0;
}
