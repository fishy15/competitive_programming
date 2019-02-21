/*
ID: aaryan.1
PROB: gift1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string> 

using namespace std; 

int find(vector <string> &names, string name) {
    for (int i = 0; i < names.size(); i++) {
        if (names[i].compare(name) == 0) {
            return i; 
        }
    }

    return -1; 
}

int main() {
    ifstream fin ("gift1.in");
    //ofstream fout ("gift1.out");
    int NP; fin >> NP; 
    vector <string> names;
    for (int i = 0; i < NP; i++) {
        string name; fin >> name;
        names.push_back(name);
    } 

    int money[NP];

    string giver; fin >> giver; 
    int amt, NG; fin >> amt >> NG; 

    while (amt != 0 && NG != 0) {
        money[find(names, giver)] = money[find(names, giver)] - amt + (amt % NG);
        for (int i = 0; i < NG; i++) {
            string n; fin >> n;
            money[find(names, n)] += amt / NG;  
        }
    }

    for (int i = 0; i < NP; i++) {
        cout << names[i] + " " + money[i] << endl; 
    }
}