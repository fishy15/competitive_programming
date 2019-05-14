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

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cstdlib>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 10000007

#define MAXN 50

using namespace std;

int n, h, m;
int nums[MAXN];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> h >> m;
    for (int i = 0; i < n; i++) {
        nums[i] = h;
    }
    
    for (int i = 0; i < m; i++) {
        int l, r, h1; cin >> l >> r >> h1;
        for (int i = l - 1; i < r; i++) {
            nums[i] = min(nums[i], h1);
        }
    }
    
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += nums[i] * nums[i];
    }
    
    cout << sum << '\n';

    return 0;
}
