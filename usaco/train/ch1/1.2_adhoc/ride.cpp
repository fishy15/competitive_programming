/*
ID: aaryan.1
TASK: ride
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
    string ship, comet; 
    fin >> ship >> comet; 
    
    int cometSum = 1, shipSum = 1; 
    for (int i = 0; i < comet.size(); i++)
    {
        cometSum *= comet[i] - 'A' + 1;
        cometSum = cometSum % 47;   
    }
    for (int i = 0; i < ship.size(); i++)
    {
        shipSum *= ship[i] - 'A' + 1;
        shipSum = shipSum % 47;  
    }
    if (shipSum == cometSum)
        fout << "GO\n"; 
    else 
        fout << "STAY\n"; 
    return 0;
}
