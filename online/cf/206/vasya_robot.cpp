// :pray: :arrayman:
// :pray: :summitosity:
// :pray: :pusheenosity:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk-duk-go:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eediosity:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinxiosity
// :pray: :eggyosity:
// :pray: :squares-are-fine:
// :pray: :see-jay:
// :pray: :stephiosity:
// :pray: :fatant:
// :pray: :mathbot:
// :pray: :dolphin:
// :pray: :stef:
// :pray: :geothermal:
// :pray: :mikey:
// :pray: :horse:
// :pray: :snek:
// :pray: :wayne:
// :pray: :wu:
// :pray: :void:
// :pray: :pushbackeeen:

#include <iostream>
#include <string>
#include <cmath>

#define MAXN 200000

using namespace std;

int n;
string path;
int x[MAXN + 1];
int y[MAXN + 1];
int x_end;
int y_end;

int dist(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int main() {
    cin >> n >> path;
    cin >> x_end >> y_end;
    for (int i = 0; i < n; i++) {
        if (path[i] == 'L') {
            x[i + 1] = x[i] - 1;
            y[i + 1] = y[i];
        } else if (path[i] == 'R') {
            x[i + 1] = x[i] + 1;
            y[i + 1] = y[i];
        } else if (path[i] == 'U') {
            x[i + 1] = x[i];
            y[i + 1] = y[i] + 1;
        } else if (path[i] == 'D') {
            x[i + 1] = x[i];
            y[i + 1] = y[i] - 1;
        }
    }
    
    int min = 0;
    int max = n + 1;
    int ans = -1;
    
    while (min < max) {
        int mid = (min + max) / 2;
        bool cont = false;
        
        for (int i = 0; i < n - mid + 1; i++) {
            int new_x = x[n] - (x[i + mid] - x[i]);
            int new_y = y[n] - (y[i + mid] - y[i]);
            int d = dist(new_x, new_y, x_end, y_end);
            if (d <= mid && d % 2 == mid % 2) {
                //cout << i << ' ' << mid << '\n';
                //cout << new_x << ' ' << new_y << ' ' << x_end << ' ' << y_end << '\n';
                ans = mid;
                max = mid;
                cont = true;
                break;
            }
        }
        
        if (!cont) {
            min = mid + 1;
        }
    }
    
    cout << ans << '\n';
    return 0;
}