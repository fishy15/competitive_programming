#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int mod(int x, int m) {
    if (x < 0) {
        return (m - (-x % m));
    }

    return x % m;
}

int ans[7][2];
bool visited[7];

int main() {
    ifstream fin("div7.in");
    ofstream fout("div7.out");

    int N; fin >> N;
    vector<int> nums;

    for (int i = 0; i < 7; i++) {
        ans[i][0] = N;
    }
        
    int sum = 0;

    for (int i = 0; i < N; i++) {
        int x; fin >> x;
        sum += x;
        sum %= 7;
        nums.push_back(sum);
        //cout << sum << endl;
    }

    for (int i = 0; i < N; i++) {
        if (i < ans[nums[i]][0]) {
            visited[nums[i]] = true;
            ans[nums[i]][0] = i;
        }

        if (i > ans[nums[i]][1]) {
            visited[nums[i]] = true;
            ans[nums[i]][1] = i;
        }
    }

    ans[0][0] = 0;

    int max = 0;
    for (int i = 0; i < 7; i++) {
        //cout << ans[i][0] << ' ' << ans[i][1] << endl;
        if (ans[i][1] - ans[i][0] > max && visited[i]) {
            max = ans[i][1] - ans[i][0];
        }
    }

    fout << max << '\n';

    return 0;
}
