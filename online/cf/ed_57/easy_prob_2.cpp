#include <iostream>
#include <string>
#include <vector>

#define ll long long

using namespace std;

ll calc(int, string, int);
vector<int> a;

int main() {
    int sz; cin >> sz;
    string s; cin >> s;

    for (int i = 0; i < sz; i++) {
        int x; cin >> x;
        a.push_back(x);
    }

    cout << calc(sz, s, 0) << '\n';
    return 0;
}

ll calc(int sz, string s, int pos) {
    //cout << s << '\n';
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

    ll min = (1LL << 63) - 1;
    bool any = false;

    for (int i = pos; i < sz; i++) {
        if (s[i] == 'h') {
            if (aCount - curA > 0 && rCount - curR > 0 && dCount - curD > 0) {
                s[i] = 'x';
                ll val = calc(sz, s, pos) + a[i];
                min = val < min ? val : min;
                s[i] = 'h';
                any = true;
            }
        } else if (s[i] == 'a') {
            if (curH > 0 && rCount - curR > 0 && dCount - curD > 0) {
                s[i] = 'x';
                ll val = calc(sz, s, pos) + a[i];
                min = val < min ? val : min;
                s[i] = 'a';
                any = true;
            }
        } else if (s[i] == 'r') {
            if (curH > 0 && curA > 0 && dCount - curD > 0) {
                s[i] = 'x';
                ll val = calc(sz, s, pos) + a[i];
                min = val < min ? val : min;
                s[i] = 'r';
                any = true;
            }
        } else if (s[i] == 'd') {
            if (curH > 0 && curA > 0 && curR > 0) {
                s[i] = 'x';
                ll val = calc(sz, s, pos) + a[i];
                min = val < min ? val : min;
                s[i] = 'd';
                any = true;
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

    if (any) {
        return min;
    }

    return 0;
}
