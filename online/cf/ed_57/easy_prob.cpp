#include <iostream>
#include <string>
#include <vector>

#define ll long long

using namespace std;

int main() {
    int sz; cin >> sz;
    string s; cin >> s;
    vector<int> a(sz);

    for (int i = 0; i < sz; i++) {
        cin >> a[i];
    }

    int hCount = 0;
    int aCount = 0;
    int rCount = 0;
    int dCount = 0;

    for (char c : s) {
        if (c == 'h') {
            hCount++;
        } else if (c == 'a') {
            aCount++;
        } else if (c == 'r') {
            rCount++;
        } else if (c == 'd') {
            dCount++;
        }
    }

    int curH = 0;
    int curA = 0;
    int curR = 0;
    int curD = 0;

    ll hSum = 0;
    ll aSum = 0;
    ll rSum = 0;
    ll dSum = 0;

    for (int i = 0; i < sz; i++) {
        if (s[i] == 'h') {
            if (aCount - curA > 0 && rCount - curR > 0 && dCount - curD > 0) {
                hSum += a[i];
            }
        } else if (s[i] == 'a') {
            if (curH > 0 && rCount - curR > 0 && dCount - curD > 0) {
                aSum += a[i];
            }
        } else if (s[i] == 'r') {
            if (curH > 0 && curA > 0 && dCount - curD > 0) {
                rSum += a[i];
            }
        } else if (s[i] == 'd') {
            if (curH > 0 && curA > 0 && curR > 0) {
                dSum += a[i];
            }
        }

    if (s[i] == 'h') {
            curH++;
        } else if (s[i] == 'a') {
            curA++;
        } else if (s[i] == 'r') {
            curR++;
        } else if (s[i] == 'd') {
            curD++;
        }

    }

    ll min = hSum;
    if (aSum < min) {
        min = aSum;
    }

    if (rSum < min) {
        min = rSum;
    }

    if (dSum < min) {
        min = dSum;
    }

    cout << min << '\n';
    return 0;
}
