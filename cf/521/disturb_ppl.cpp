// i have no idea what this is 
// obviously does not work

#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> ppl;
int count;

void fix() {
    vector<bool> need_fix;
    bool redo = false;
    for (int i = 1; i < n -1; i++) {
        need_fix.push_back(ppl[i - 1] == 1 && ppl[i + 1] == 1);
    }

    for (int i = 1; i < need_fix.size() - 1; i++) {
        if (need_fix[i-1] && need_fix[i+1]) {
            ppl[i + 2] = 0;
            redo = true;
            break;
        }
    }

    if (redo) {
        ::count++;
        fix();
    }

    for (int i = 0; i < need_fix.size(); i++) {
        if (need_fix[i]) {
            ppl[i] = 0;
            redo = true;
            break;
        }
    }

    if (redo) {
        ::count++;
        fix();
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
    cout << ::count << '\n';
    return 0;
}
