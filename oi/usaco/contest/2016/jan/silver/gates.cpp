#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

int grid[4001][4001];
int curX = 2000;
int curY = 2000;

void floodfill(int x, int y, int num) {
    if (grid[x][y] != 0) {
        return;
    }

    cout << x << ' ' << y << endl;
    grid[x][y] = num;
    if (x > 0 && !grid[x - 1][y]) {
        floodfill(x - 1, y, num);
    }

    if (x < 4001 && !grid[x + 1][y]) {
        floodfill(x + 1, y, num);
    }

    if (y > 0 && !grid[x][y - 1]) {
        floodfill(x, y - 1, num);
    }

    if (y < 4001 && !grid[x][y + 1]) {
        floodfill(x, y + 1, num);
    }

}

int main() {
    ifstream fin("gates.in");
    ofstream fout("gates.out");

    int n; fin >> n;
    string x; fin >> x;

    for (int i = 0; i < n; i++) {
        switch(x[i]) {
            case 'N':
                grid[curX][curY] = -1;
                curX++;  
                grid[curX][curY] = -1;
                curX++; 
                break;
            case 'S':
                grid[curX][curY] = -1;
                curX--;  
                grid[curX][curY] = -1;
                curX--; 
                break;
            case 'E':
                grid[curX][curY] = -1;
                curY++;  
                grid[curX][curY] = -1;
                curY++; 
                break;
            case 'W':
                grid[curX][curY] = -1;
                curY--;  
                grid[curX][curY] = -1;
                curY--; 
                break;
        }
    }

    int count = 1;
    for (int i = 0; i < 4001; i++) {
        for (int j = 0; j < 4001; j++) {
            if (grid[i][j] == 0) {
                cout << "HI" << '\n';
                floodfill(i, j, count);
                count++;
            }
        }
    }

    cout << count - 1 << '\n';
    return 0;
}
