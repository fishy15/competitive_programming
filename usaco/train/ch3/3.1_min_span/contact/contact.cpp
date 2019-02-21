/*
ID: aaryan.1
TASK: contact
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <assert.h>

using namespace std;

int main() {
    ifstream fin("contact.in");
    ofstream fout("contact.out");

    int a, b, n; fin >> a >> b >> n;
    string s = "";
    string temp;
    while (fin >> temp){
        s += temp;
    }

    int sz = (int)(s.size());
    if (b > sz) {
        b = sz;
    }

    vector<map<string, int>> vals(b - a + 1);

    for (int i = 0; i < sz - b + 1; i++) {
        string sub = s.substr(i, b);
        if (!vals[0].count(sub)) {
            vals[0][sub] = 1;
        } else {
            vals[0][sub]++;
        }
    }

    for (int len = b - 1; len >= a; len--) {
        for (auto p : vals[b - len - 1]) {
            string sub = p.first.substr(0, len);
            if (!vals[b - len].count(sub)) {
                vals[b - len][sub] = p.second;
            } else {
                vals[b - len][sub] += p.second;
            }
        }

        string sub = s.substr(sz - len, len);
        if (!vals[b - len].count(sub)) {
            vals[b - len][sub] = 1;
        } else {
            vals[b - len][sub]++;
        }
    }

    map<int, vector<string>> ans;
    for (auto m : vals) {
        for (auto p : m) {
            int num = p.second;
            string str = p.first;
            ans[num].push_back(str);
        }
    }
    
    auto it = ans.rbegin();
    int counter = 0;
    while (it != ans.rend()) {
        //cout << "HI\n";
        if (counter == n) {
            break;
        }

        fout << it->first << '\n';

        sort(it->second.begin(), it->second.end(), [](const string &s1, const string &s2) {
                if (s1.size() == s2.size()) {
                    return s1 < s2;
                }
                return s1.size() < s2.size();
        });

        for (int i = 0; i < it->second.size(); i++) {
            fout << it->second[i];
            if (i % 6 == 5 || i == it->second.size() - 1) {
                fout << '\n';
            } else {
                fout << ' ';
            }
        }

        it++;
        counter++;
    }

    return 0;
}
