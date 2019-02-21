#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    ifstream fin("mountains.in");
    ofstream fout("mountains.out");

    int n; fin >> n;
    vector<pair<int, int>> mounts;
    for (int i = 0; i < n; i++) {
        int x, y; fin >> x >> y;
        mounts.push_back({x - y, x + y});
    }

    sort(mounts.begin(), mounts.end(), [](const pair<int, int> &p1, const pair<int, int> &p2) {
        if (p1.first == p2.first) {
            return p1.second > p2.second;
        }

        return p1.first < p2.first;
    });

    int max_front = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        while (max_front < i && mounts[max_front].second < mounts[i].second) {
            max_front++;
        }

        if (max_front == i) {
            ans++;
        }
    }

    fout << ans << '\n';
    return 0;
}
