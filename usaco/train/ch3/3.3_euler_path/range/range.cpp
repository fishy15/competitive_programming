/*
ID: aaryan.1
TASK: range
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int n;
vector<string> field;
ofstream fout;

int arr1[250][250];
int arr2[250][250];

void solve(int len) {
    //cout << len << '\n';
    int count = 0;

    for (int i = 0; i < n - len + 1; i++) {
        for (int j = 0; j < n - len + 1; j++) {
            if (len % 2 == 0) {
                arr2[i][j] = (arr1[i][j] + arr1[i + 1][j] + arr1[i][j + 1] + arr1[i + 1][j + 1]) / 4;
                if (arr2[i][j] > 0) {
                    count++;
                }
            } else {
                arr1[i][j] = (arr2[i][j] + arr2[i + 1][j] + arr2[i][j + 1] + arr2[i + 1][j + 1]) / 4;
                if (arr1[i][j] > 0) {
                    count++;
                }
            }
        }
    }

    if (count > 0) {
        fout << len << ' ' << count << '\n';
        solve(len + 1);
    }
}

int main() {
    ifstream fin("range.in");
    fout = ofstream("range.out");

    fin >> n;
    for (int i = 0; i < n; i++) {
        string s; fin >> s;
        field.push_back(s);
    }

    for (int i = 0; i < n; i++) {        
        for (int j = 0; j < n; j++) {
            arr1[i][j] = field[i][j] - '0';
        }
    }

    solve(2);
}