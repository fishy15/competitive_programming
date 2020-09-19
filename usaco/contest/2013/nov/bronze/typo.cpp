#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream fin("typo.in");
    ofstream fout("typo.out");

    string s; fin >> s;
    int sz = (int)(s.size());

    vector<int> left = vector(sz + 1);
    vector<int> right = vector(sz + 1);

    left[0] = 0;
    right[0] = 0;

    for (int i = 1; i <= sz; i++) {
        if (s[i] == '(') {
            left[i] = left[i - 1] + 1;
            right[i] = right[i - 1];
        } else {
            left[i] = left[i - 1];
            right[i] = right[i - 1] + 1;
        }
    }

    vector<bool> worksFromFront;
    for (int i = 0; i < sz; i++) {
                    
    }

    return 0;
}
