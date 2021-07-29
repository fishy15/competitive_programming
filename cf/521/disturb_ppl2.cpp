// this one works
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> ppl;
int ans;

void fix() {
    // check if we can kill 2 birds w/ 1 stone
    for (int i = 2; i < n - 2; i++) {
        if (ppl[i - 2] && ppl[i] && ppl[i + 2] && !ppl[i - 1] && !ppl[i + 1]) {
            //cout << "off " << i << endl;
            ppl[i] = 0;
            ans++;
            fix();
        }
    }

    // now check for any remaining ppl
    for (int i = 1; i < n - 1; i++) {
        if (ppl[i - 1] && ppl[i + 1] && !ppl[i]) {
            //cout << "off " << i - 1 << endl;
            ppl[i - 1] = 0;
            ans++;
            fix();
        }
    }
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        ppl.push_back(x);
    }

    fix();
    cout << ans << '\n';
    return 0;
}
