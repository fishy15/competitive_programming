/* this was a geniosity program
 * **xxxxxxxxxxxxx
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <stack>

using namespace std;

typedef struct cow cow;
struct cow {
    int start, end, y;
    
    cow(int x, int y, int r) {
        start = x * r * -1;
        end = start + r;
        this->y = y;
    }
};

int main() {
    ifstream fin("stampede.in");
    ofstream fout("stampede.out");

    int N; fin >> N;
    vector<cow> cows;
    
    for (int i = 0; i < N; i++) {
        int x, y, r; fin >> x >> y >> r;
        cows.push_back(cow(x, y, r));
    }

    sort(cows.begin(), cows.end(), [](const cow& cow1, const cow& cow2) {
        if (cow1.start == cow2.start) {
            if (cow1.end == cow2.end) {
                return cow1.y < cow2.y;
            }

            return cow1.end < cow2.end;
        }

        return cow1.start < cow2.start;
    });

    stack<cow> visible;
    int count = 0;
    for (int i = 0; i < N; i++) {
        while (!visible.empty() && cows[i].start > visible.top().end) {
            visible.pop();
        }

        if (visible.empty()) {
            visible.push(cows[i]);
            count++;
        } else {
            if (cows[i].y < visible.top().y) {
                visible.push(cows[i]);
                count++;
            } else {
                if (cows[i].end < visible.top().end) {
                    visible.pop();
                    visible.push(cows[i]);
                    count++;
                }
            }
        }
    }

    fout << count << '\n';

    return 0;
}
