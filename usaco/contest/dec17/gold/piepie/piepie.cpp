#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

int lower(vector<pair<int, int>> &v, int target, bool first) {
    int max = v.size() - 1;
    int min = 0;
    int ans = -1;

    while (min < max) {
        int mid = (min + max) / 2;
        if (first) {
            if (v[mid].first <= target) {
                ans = mid;
                min = mid + 1;
            } else {
                max = mid - 1;
            }
        } else {
            if (v[mid].second <= target) {
                ans = mid;
                min = mid + 1;
            } else {
                max = mid - 1;
            }
        }
    }

    return ans;
}


int upper(vector<pair<int, int>> &v, int target, bool first) {
    int max = v.size() - 1;
    int min = 0;
    int ans = -1;

    while (min < max) {
        int mid = (min + max) / 2;
        if (first) {
            if (v[mid].first >= target) {
                ans = mid;
                max = mid - 1;
            } else {
                min = mid + 1;
            } 
        } else {
            if (v[mid].second >= target) {
                ans = mid;
                max = mid - 1;
            } else {
                min = mid + 1;
            }
        }
    }

    return ans;
}

int main() {
    ifstream fin("piepie.in");
    ofstream fout("piepie.out");

    int n, d; fin >> n >> d;

    vector<pair<int, int>> bessie;
    vector<pair<int, int>> elsie;

    for (int i = 0; i < n; i++) {
        int x, y; fin >> x >> y;
        bessie.push_back({x, y});
    }

    for (int i = 0; i < n; i++) {
        int x, y; fin >> x >> y;
        elsie.push_back({x, y});
    }

    vector<pair<int, int>> b_connect(n);
    vector<pair<int, int>> e_connect(n);

    sort(bessie.begin(), bessie.end(), [](const pair<int, int> &p1, const pair<int, int> &p2) {
        if (p1.second == p2.second) {
            return p1.first < p2.first;
        }

        return p1.second < p2.second;
    });

    sort(elsie.begin(), elsie.end(), [](const pair<int, int> &p1, const pair<int, int> &p2) {
        if (p1.first == p2.first) {
            return p1.second < p2.second;
        }

        return p1.first < p2.first;
    });

    for (int i = 0; i < n; i++) {
        b_connect[i] = {lower(elsie, bessie[i].first - d, true), upper(elsie, bessie[i].first, true)};
        e_connect[i] = {lower(bessie, elsie[i].second - d, false), upper(bessie, elsie[i].second, false)};
    }

    for (auto p : b_connect) {
        cout << p.first << ' ' << p.second << '\n';
    }

    for (auto p : e_connect) {
        cout << p.first << ' ' << p.second << '\n';
    }
}