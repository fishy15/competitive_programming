#include <iostream>
#include <vector>

using namespace std;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int N; cin >> N;
    int sum1 = 0;
    int sum2 = 0;

    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        sum1 += x;
    }

    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        sum2 += x;
    }

    if (sum1 >= sum2) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}
