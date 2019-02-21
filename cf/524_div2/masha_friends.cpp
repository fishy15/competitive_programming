#include <iostream>
using namespace std;

// assumes lower left corner is white
int white_under(int w, int h) {
    if (w % 2 == 0 || h % 2 == 0) {
        return w*h/2;
    } else {
        return (w+1)*h/2 - (h+1)/2;
    }
}

int black_under(int w, int h) {
    return w*h - white_under(w, h);
}

int is_black(int x, int y) {
    return (x + y) % 2 == 0;
}

int min(int x, int y) {
    return x < y ? x : y;
}

int max(int x, int y) {
    return x > y ? x : y;
}

int main() {
    int n; cin >> n;

    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        int white[4]; 
        for (int i = 0; i < 4; i++) {
            cin >> white[i];
        }

        int black[4];
        for(int i = 0; i < 4; i++) {
            cin >> black[i];
        }

        int wTotal = white_under(x, y);

        if (is_black(white[0], white[1])) {
            wTotal += white_under(white[2] - white[0], white[3] - white[1]);
        } else {
            wTotal += black_under(white[2] - white[0], white[3] - white[0]);
        }

        if (is_black(black[0], black[1])) {
            wTotal += black_under(black[2] - black[0], black[3] - black[1]);
        } else {
            wTotal += white_under(black[2] - black[0], black[3] - black[0]);
        }

        int inter[4];
        inter[0] = max(white[0], black[0]);
        inter[1] = max(white[1], black[1]);
        inter[2] = min(white[2], black[2]);
        inter[3] = min(white[3], black[3]);

        if (inter[3] > inter[1] && inter[2] > inter[0]) {
            if (is_black(inter[0], inter[1])) {
                wTotal -= white_under(inter[2] - inter[0], inter[3] - inter[1]);
            } else {
                wTotal -= black_under(inter[2] - inter[0], inter[3] - inter[1]);
            }
        }

        cout << wTotal << ' ' << x*y - wTotal << '\n';
    }

    return 0;
}
