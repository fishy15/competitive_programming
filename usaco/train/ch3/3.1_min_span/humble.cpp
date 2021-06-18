/*
ID: aaryan.1
TASK: humble
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>

#define ll unsigned long long

using namespace std;

int main() {
    ifstream fin("humble.in");
    ofstream fout("humble.out");

    int n, m; fin >> n >> m;
    vector<ll> p;
    set<ll> nums;

    for (int i = 0; i < n; i++) {
        ll x; fin >> x;
        p.push_back(x);
        nums.insert(x);
    }

    auto it = nums.begin();
    int pos = 1;
    while (pos < m) {
        for (int i = 0; i < n; i++) {
            ll val = p[i] * (*it);
            if ((nums.size() > m) && (val > *(--nums.end()))) {
                break; 
            }

            nums.insert(val);
        }

        while (nums.size() > 3 * m / 2) {
            nums.erase(--nums.end());
        }

        pos++;
        it++;
    }

    fout << *it << '\n';
    return 0;
}
