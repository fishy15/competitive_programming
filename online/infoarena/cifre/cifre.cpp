#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

#define ll long long 

using namespace std;

ll vals[10][10];

string a, b;
char c;
int k;

void createTable();
string pad(string);
ll calcAbove(string);
ll calcVal(int, int);
bool works(string);

int main() {
    ifstream fin("cifre.in");
    ofstream fout("cifre.out");

    int a2, b2;
	fin >> a2 >> b2 >> c >> k;

    a = to_string(a2);
    b = to_string(b2 + 1);

    createTable();

    /*
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << calcVal(i, j) << ' ';
        }
        cout << endl;
    }
    */

    a = pad(a);
    b = pad(b);

    ll val1 = calcAbove(a);
    ll val2 = calcAbove(b);

    if (b2 == 999999999) {
        val2 = -works("1000000000"); 
    } else if (b2 == 1000000000) {
        val2 = 0;
    }

    //cout << val1 << ' ' << val2 << '\n';
    double totalNums = b2 - a2 + 1;

    if (val1 - val2 == 0) {
        fout << "0.0000\n"; 
        return 0;
    }

    fout << setprecision(4) << (val1 - val2) / totalNums << '\n';
    return 0;
}

void createTable() {
    for (int digs = 0; digs <= 9; digs++) {
        for (int needed = 0; needed <= 9; needed++) {
            if (digs < needed) {
                vals[digs][needed] = 0;
            } else if (digs == needed) {
                vals[digs][needed] = 1;
            } else {
                vals[digs][needed] = vals[digs - 1][needed] * 9 + vals[digs - 1][needed - 1];
            }
        }
    }

    for (int digs = 0; digs <= 9; digs++) {
        ll sum = 0;
        for (int i = 9; i >= 0; i--) {
            sum += vals[digs][i];
            vals[digs][i] = sum;
        }
    }
}

string pad(string s) {
    string ans = s;
    while (ans.size() < 9) {
        ans = '0' + ans; 
    }

    return ans;
}

ll calcAbove(string s) {
    //cout << s << endl;
    int needed = k;
    ll ans = 0;
    for (int sameDig = 1; sameDig <= 9; sameDig++) {
        // calc diff first
        for (int i = s[sameDig - 1] + 1; i <= '9'; i++) {
            //cout << 9 - sameDig + 1 << ' ' << needed << ' ';
            if (i == c && needed > 0) {
                ans += calcVal(9 - sameDig, needed - 1);
                //cout << calcVal(9 - sameDig, needed - 1) << endl;
            } else {
                ans += calcVal(9 - sameDig, needed);
                //cout << calcVal(9 - sameDig, needed) << endl;
            }
        }

        if (s[sameDig - 1] == c) {
            needed -= 1;
        }
    }

    return ans;
}

ll calcVal(int dig, int needed) {
    if (needed < 0) {
        return 0;
    }

    return vals[dig][needed];
}

bool works(string s) {
    int count = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            count++;
        }
    }

    return count >= k;
}
