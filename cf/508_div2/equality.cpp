#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n, k; cin >> n >> k;
    string s; cin >> s;
    vector<int> count(k, 0);

    for (auto c : s) {
        int val = c - 'A';
        count[val]++;
    }

    int min = 100001;
    for (int i = 0; i < k; i++) {
        min = min < count[i] ? min : count[i];
    }

    cout << min * k << '\n';
    return 0;
}
