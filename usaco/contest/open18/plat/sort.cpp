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
#define MAXN 100000

using namespace std;

int n;
int nums[MAXN];
pair<int, int> pos[MAXN];
vector<int> smth;

int main() {
    ifstream fin("sort.in");
    ofstream fout("sort.out");

    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> nums[i];
        pos[i] = {nums[i], i};
    }

    sort(pos, pos + n);

    smth = {0};
    int mm = 0;
    for (int i = 0; i < n; i++) {
        mm = max(mm, pos[i].second);
        smth.push_back(mm - i);
        // cout << mm - i << '\n';
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += max(max(smth[i], smth[i + 1]), 1);
    }

    fout << ans << '\n';

    return 0;
}
