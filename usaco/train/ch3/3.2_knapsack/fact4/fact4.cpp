/*
ID: aaryan.1
TASK: fact4
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("fact4.in");
    ofstream fout("fact4.out");

    int n; fin >> n;
    int prod = 1;
    for (int i = 1; i <= n; i++) {
        prod *= i;

        while (prod % 10 == 0) {
            prod /= 10;
        }

        prod %= 1000;
    }

    fout << prod % 10 << '\n';
    return 0;
}
