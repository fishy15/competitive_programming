#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>

#define ll long long 

using namespace std;

int main() {
    int num; cin >> num;
    while (num != 0) {
        vector<pair<int, int>> poly;
        for (int i = 0; i < num; i++) {
            int x, y; cin >> x >> y;
            poly.push_back({x, y});
        }

        ll sum1 = 0;
        for (int i = 0; i < num - 1; i++) {
            sum1 += poly[i].first * poly[i + 1].second;
        }
        sum1 += poly[num - 1].first * poly[0].second;

        ll sum2 = 0;
        for (int i = 0; i < num - 1; i++) {
            sum2 += poly[i].second * poly[i + 1].first;
        }
        sum2 += poly[num - 1].second * poly[0].first;

        double ans = (sum1 - sum2) / 2.0;
        if (ans > 0) {
            printf("CCW %.1f\n", ans);
        } else {
            printf("CW %.1f\n", -ans);
        }
        cin >> num;
    }

    return 0;
}
