/*
ID: aaryan.1
TASK: job
LANG: C++14
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

vector<int> solve(int n, const vector<int> machine) {
    vector<int> end(machine.size());
    vector<int> res;
    for (int j = 0; j < n; j++) {
        int t = 0;
        pair<int, int> best = {INF, -1};
        for (int i = 0; i < (int)(machine.size()); i++) {
            int will_end = max(t, end[i]) + machine[i];
            best = min(best, {will_end, i});
        }
        
        res.push_back(best.first);
        end[best.second] = best.first;
    }

    return res;
}

int main() {
    ifstream fin("job.in");
    ofstream fout("job.out");

    int n, m1, m2; fin >> n >> m1 >> m2;
    vector<int> a, b;

    for (int i = 0; i < m1; i++) {
        int x; fin >> x;
        a.push_back(x);
    }

    for (int i = 0; i < m2; i++) {
        int x; fin >> x;
        b.push_back(x);
    }

    vector<int> first_res = solve(n, a);
    vector<int> second_res = solve(n, b);

    int ans2 = 0;
    for (int i = 0; i < n; i++) {
        ans2 = max(ans2, first_res[i] + second_res[n - i - 1]);
    }

    fout << first_res[n - 1] << ' ' << ans2 << '\n';

    return 0;
}
