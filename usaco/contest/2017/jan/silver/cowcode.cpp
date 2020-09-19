#include <iostream>
#include <fstream>
#include <string>

typedef long long ll;

using namespace std;

int main() {
    ifstream fin("cowcode.in");
    ofstream fout("cowcode.out");

    string s; fin >> s;
    ll sz = (ll)(s.size());
    ll num; fin >> num;
    num -= 1;

    for (int i = 0; i < 12; i++) {
        num = i;
        ll lowPow = 0;
        while (((num / sz) >> lowPow) > 0) {
            lowPow++;
        }

        ll lower = sz << lowPow;
        cout << lowPow << ' ' << lower << '\n';
        while (num > sz) {
            if (num < lower / 2) {
                lower /= 2;
                continue;
            }

            num = (num + 1) % lower;
        }

        cout << s[num % sz] << '\n';
    }

    num = 7;
    ll lowPow = 0;
    while (((num / sz) >> lowPow) > 0) {
        lowPow++;
    }

    ll lower = sz << lowPow;

    while (num > sz) {
        if (num < lower / 2) {
            lower /= 2;
            continue;
        }

        if (num == 
    }

    fout << s[num % sz] << '\n';
    
    return 0;
}
