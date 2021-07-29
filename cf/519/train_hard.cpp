#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<pair<int, int> > ppl;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        pair<int, int> p = {x, y};

        ppl.push_back(p);
    }

    vector<int> scores(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int sum1 = ppl[i].first + ppl[j].second;
            int sum2 = ppl[j].first + ppl[i].second;
            
            if (sum1 < sum2) {
                scores[i] += sum1;
                scores[j] += sum1;
            } else {
                scores[i] += sum2;
                scores[j] += sum2;
            }
            /*j
            if (ppl[i].first < ppl[j].first) {
                scores[i] += ppl[i].first;
                scores[j] += ppl[i].first;
            } else {
                scores[i] += ppl[j].first;
                scores[j] += ppl[j].first;
            }

            if (ppl[i].second < ppl[j].second) {
                scores[i] += ppl[i].second;
                scores[j] += ppl[i].second;
            } else {
                scores[i] += ppl[j].second;
                scores[j] += ppl[j].second;
            }
            */
        }
    }

    // correct so far
    /* 
    for (int i : scores) {
        cout << i << ' ';
    } cout << '\n';
    */
    

    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        //cout << x << ' ' << y << '\n';

        int sum1 = ppl[x].first + ppl[y].second;
        int sum2 = ppl[y].first + ppl[x].second;
        if (sum1 < sum2) {
            scores[x] -= sum1;
            scores[y] -= sum1;
        } else {
            scores[x] -= sum2;
            scores[y] -= sum2;
        }

        //cout << scores[x] << ' ' << scores[y] << '\n';;
    }

    for (int i : scores) {
        cout << i << ' ';
    }

    cout << '\n';
    return 0;
}
