#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> nums;
int ans;
int ind;
int curPos;

void dfs() {
    if (ind == n) {
        // idk
    } else {
        //cout << "sad\n";
        if (nums[ind] % (curPos + 1) == 0) {
            //cout << "add " << ind << '\n';
            curPos++;
            ind++;
            ans++;
            dfs();
            ind--;
            curPos--;
            //cout << "remove " << ind << '\n';
        }

        ind++;
        dfs();
        ind--;
    }
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    dfs();
    cout << ans << '\n';
}
