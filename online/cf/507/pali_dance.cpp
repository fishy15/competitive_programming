#include <iostream>
#include <vector>

#define FAIL cout << "-1\n"; return 0;
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, white_cost, black_cost;
    cin >> n >> white_cost >> black_cost;
    int min_coat = white_cost < black_cost ? 0 : 1;

    vector<int> nums;
    int white_init, black_init;
    white_init = black_init = 0;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
        if (x == 0) {
            white_init++;
        } else if (x == 1) {
            black_init++;
        }
    }

    for (int i = 0; i < n; i++) {
        int opp = n - i - 1;
        if (nums[i] == 0) {
            if (nums[opp] == 1) {
                FAIL;
            } else if (nums[opp] == 2) {
                nums[opp] = 0;
            }
        } else if (nums[i] == 1) {
            if (nums[opp] == 0) {
                FAIL;
            } else if (nums[opp] == 2) {
                nums[opp] = 1;
            }
        } else {
            if (nums[opp] == 2) {
               nums[i] = min_coat;
               nums[opp] = min_coat;
            }
        }
    }

    int total_cost = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] == 0) {
            total_cost += white_cost;
        } else {
            total_cost += black_cost;
        }
    }

    total_cost -= white_cost * white_init;
    total_cost -= black_cost * black_init;

    cout << total_cost << '\n';
}
