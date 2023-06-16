#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <set>

#define ll long long

using namespace std;

int main() {
    ifstream fin("hayfeast.in");
    ofstream fout("hayfeast.out");

    ll n, m; fin >> n >> m;
    vector<pair<ll, ll>> nums;

    for (int i = 0; i < n; i++) {
        int a, b; fin >> a >> b;
        nums.push_back({a, b});
    }

    ll flavor = 0;
    multiset<int> spicy;

    int front = 0;
    int back = 0;
    while (flavor < m) {
        flavor += nums[front].first;
        spicy.insert(nums[front].second);
        front++;
    }

    ll ans = *(--spicy.end());
    front--;
    while (front < n) {
        front++;
        flavor += nums[front].first;
        spicy.insert(nums[front].second);

        while (flavor - nums[back].first >= m) {
            flavor -= nums[back].first;
            spicy.erase(spicy.find(nums[back].second));
            back++;
        }

        ll max = *(--spicy.end());
        ans = max < ans ? max : ans;
    }

    fout << ans << '\n';
    return 0;
}