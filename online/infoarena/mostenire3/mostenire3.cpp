// :pray: :arrayman:
// :pray: :summit:
// :pray: :pusheen:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eed:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinx:
// :pray: :eyg:
// :pray: :evan:
// :pray: :cj:
// :pray: :steph:
// :pray: :fatant:
// :pray: :mathbot:
// :pray: :dolphin:
// :pray: :stef:
// :pray: :geothermal:
// :pray: :mikey:
// :pray: :horse:
// :pray: :snek:
// :pray: :wayne:
// :pray: :wu:
// :pray: :vmaddur:
// :pray: :dorijanko:
// :pray: :gaming:
// :pray: :kassuno:
// :pray: :hyacinth:
// :pray: :chilli:
// :pray: :dhruv:
// :pray: :philip:
// :pray: :paiman:
// :pray: :camel:
// :pray: :tree:
// :pray: :tux:
// :pray: :jony:
// :pray: :kage:
// :pray: :ghost:
// :pray: :aha:
// :pray: :coolguy:
// :pray: :imax:
// :pray: :howlet:
// :pray: :darren:
// :pray: :arie: 
// :pray: :blastman: 
// :pray: :zephyr: 
// :pray: :bigc:

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

int n, k;
int nums[MAXN];

int check(int val) {
    int pos = 0;
    int mini = INF;
    for (int i = 0; i < k - 1; i++) {
        int sum = 0;
        int start = pos;
        while (pos < n && sum < val) {
            sum += nums[pos];
            pos++;
        }

        if (pos == n) {
            return -1;
        }

        mini = min(mini, sum);
    }
    
    int sum = 0;
    for (int i = pos; i < n; i++) {
        sum += nums[i];
    }

    if (sum >= val) {
        return min(mini, sum);
    }

    return -1;
}

int main() {
    ifstream fin("mostenire3.in");
    ofstream fout("mostenire3.out");

    fin >> n >> k;
    for (int i = 0; i < n; i++) {
        fin >> nums[i];
    }

    int l = 1;
    int r = (int)(1e9);
    int ans = -1;

    while (l < r) {
        int mid = l + (r - l) / 2;
        int a = check(mid);
        if (a == -1) {
            r = mid - 1;
        } else {
            l = a + 1;
            ans = a;
        }
    }

    vector<array<int, 4>> a;
    int pos = 0;
    for (int i = 0; i < k - 1; i++) {
        int start = pos;
        int sum = 0;
        while (sum < ans) {
            sum += nums[pos];
            pos++;
        }

        a.push_back({i, pos - start, sum, 0});
    }

    int sum = 0;
    for (int i = pos; i < n; i++) {
        sum += nums[i];
    }

    a.push_back({k - 1, n - pos, sum, 0});
    sort(a.begin(), a.end(), [](const array<int, 4> &arr1, const array<int, 4> &arr2) {
        return arr1[2] < arr2[2]; 
    });

    for (int i = 0; i < k; i++) {
        a[i][3] = i;
    }

    sort(a.begin(), a.end());

    fout << ans << '\n';
    for (auto x : a) {
        fout << (k - x[3]) << ' ' << x[1] << '\n';
    }

    return 0;
}
