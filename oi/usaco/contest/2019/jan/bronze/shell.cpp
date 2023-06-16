#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct mov mov;
struct mov {
    int a, b;
    int guess;
};

void trade(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    ifstream fin("shell.in");
    ofstream fout("shell.out");

    int n; fin >> n;
    vector<mov> moves;

    for (int i = 0; i < n; i++) {
        int a, b, g; fin >> a >> b >> g;
        mov m;
        m.a = a;
        m.b = b;
        m.guess = g;
        moves.push_back(m);
    }

    // check 1 0 0 
    int count = 0;
    int max = 0;
    {
        int cups[4] = {0, 1, 0, 0};
        for (mov m : moves) {
            trade(cups[m.a], cups[m.b]);
            if (cups[m.guess] == 1) {
                count++;
            }
        }
    }

    if (count > max) {
        max = count;
    }

    count = 0;

    {
        int cups[4] = {0, 0, 1, 0};
        for (mov m : moves) {
            trade(cups[m.a], cups[m.b]);
            if (cups[m.guess] == 1) {
                count++;
            }
        }
    }

    if (count > max) {
        max = count;
    }

    count = 0;

    {
        int cups[4] = {0, 0, 0, 1};
        for (mov m : moves) {
            trade(cups[m.a], cups[m.b]);
            if (cups[m.guess] == 1) {
                count++;
            }
        }
    }

    if (count > max) {
        max = count;
    }
    
    fout << max << '\n';
}