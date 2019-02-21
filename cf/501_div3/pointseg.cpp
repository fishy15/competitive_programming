#include <iostream>
#include <vector>

#define MAX_M 100

using namespace std;

int n, m;
bool points[MAX_M + 1];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        for (int i = l; i <= r; i++) {
            points[i] = true;
        }
    }

    int count = 0;
    vector<int> ans;
    for (int i = 1; i <= m; i++) {
       if (!points[i]) {
           count++;
           ans.push_back(i);
       }
    }

    cout << count << '\n';
    for (int i = 0; i < count; i++) {
        cout << ans[i] << ' ';
    }

    cout << '\n';
    return 0;
}
