/* 
ID: aaryan.1
TASK: friday
LANG: C++
*/ 
#include <iostream>
#include <fstream>
#include <string>
using namespace std; 

bool notLeap(int year) {
    if (year % 400 == 0) {
        return false;
    } else if (year % 100 == 0) {
        return true; 
    } else if (year % 4 == 0) {
        return false; 
    }

    return true;
}

int main() {
    ifstream fin ("friday.in");
    ofstream fout ("friday.out");
    int n; fin >> n; 
    int days[] = {0, 0, 0, 0, 0, 0, 0}; //ssmtwtf
    int thirteen = 0; 
    for(int i = 0; i < n; i++) {
        if (notLeap(1900+i)) {
            days[(thirteen + 0) % 7]++;
            days[(thirteen + 3) % 7]++;
            days[(thirteen + 3) % 7]++;
            days[(thirteen + 6) % 7]++;
            days[(thirteen + 1) % 7]++;
            days[(thirteen + 4) % 7]++;
            days[(thirteen + 6) % 7]++;
            days[(thirteen + 2) % 7]++;
            days[(thirteen + 5) % 7]++;
            days[(thirteen + 0) % 7]++;
            days[(thirteen + 3) % 7]++;
            days[(thirteen + 5) % 7]++;
            thirteen = (thirteen + 1) % 7;
        } else {
            days[(thirteen + 0) % 7]++;
            days[(thirteen + 3) % 7]++;
            days[(thirteen + 4) % 7]++;
            days[(thirteen + 0) % 7]++;
            days[(thirteen + 2) % 7]++;
            days[(thirteen + 5) % 7]++;
            days[(thirteen + 0) % 7]++;
            days[(thirteen + 3) % 7]++;
            days[(thirteen + 6) % 7]++;
            days[(thirteen + 1) % 7]++;
            days[(thirteen + 4) % 7]++;
            days[(thirteen + 6) % 7]++;
            thirteen = (thirteen + 2) % 7;
        }
   }
    for (int i = 0; i < 6; i++) {
        fout << days[i] << " ";
    }
    fout << days[6] << endl;
}    