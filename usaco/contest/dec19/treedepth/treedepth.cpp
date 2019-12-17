// :pray: :steph:
// :pray: :bakekaga:

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

int n, k, m;
int ans[20];

void calc_ans(const vector<int> &arr, int l, int r, int d) {
    if (r < l) return;
    int pos = l;
    for (int i = l + 1; i <= r; i++) {
        if (arr[i] < arr[pos]) {
            pos = i;
        }
    }

    ans[pos] += d;
    if (ans[pos] > m) ans[pos] -= m;
    if (l < pos) calc_ans(arr, l, pos - 1, d + 1);
    if (pos < r) calc_ans(arr, pos + 1, r, d + 1);
}

int main() {
   ifstream fin("treedepth.in");
    ofstream fout("treedepth.out");

    fin >> n >> k >> m;
    vector<int> arr;
    for (int i = 1; i <= n; i++) {
        arr.push_back(i);
    }

    do {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i] > arr[j]) cnt++;
            }
        }
        if (cnt == k) {
            calc_ans(arr, 0, n - 1, 1);
        }
    } while (next_permutation(arr.begin(), arr.end()));

    for (int i = 0; i < n; i++) {
        fout << ans[i];
        if (i < n - 1) fout << ' ';
    } fout << '\n';

    return 0;
}
