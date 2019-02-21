#include <iostream>
#include <string>
#include <vector>

#define ll long long
#define min(a, b) (a) < (b) ? (a) : (b)

using namespace std;

int main() {
    int n; cin >> n;
    vector<string> seq;

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        seq.push_back(s);
    }

    vector<int> front(500001, 0);
    vector<int> back(500001, 0);

    for (int i = 0; i < n; i++) {
        int count = 0;
        int end = (int)(seq[i].size()) - 1;
        for (int j = 0; j < seq[i].size(); j++) {
            if (seq[i][j] == '(') {
                count++;
            } else {
                count--;
            }
        }

        bool bad = false;
        if (count >= 0) {
            int count2 = 0;
            for (int j = 0; j < seq[i].size(); j++) {
                if (seq[i][j] == '(') {
                    count2++;
                } else {
                    count2--;
                }

                if (count2 < 0) {
                    bad = true;
                    break;
                }
            }
        }
        
        if (count <= 0) {
            int count2 = 0;
            for (int j = end; j >= 0; j--) {
                if (seq[i][j] == '(') {
                    count2++;
                } else {
                    count2--;
                }

                if (count2 > 0) {
                    bad = true;
                    break;
                }
            }
        }

        if (bad) {
            continue;
        }

        if (count > 0) {
            front[count]++;
        } else {
            back[-count]++;
        }
    }

    ll ans = 0;
    for (int i = 1; i <= 500000; i++) {
        ans += min(front[i], back[i]);
    }

    ans += (back[0] / 2);

    cout << ans << '\n';
    return 0;
}
