/*
ID: aaryan.1
TASK: spin
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct wedge wedge;
struct wedge {
    int start;
    int end;

    wedge(int start, int span) {
        this->start = start;
        end = (start + span) % 360;
    }

    bool checkInside(int pos) {
        if (start > end) {
            if (pos < start) {
                pos += 360;
            }

            return pos >= start && pos <= (end + 360);
        }

        return pos >= start && pos <= end;
    }

    void moveForward(int val) {
        start += val;
        end += val;
        start %= 360;
        end %= 360;
    }
};

typedef struct wheel wheel;
struct wheel {
    int speed;
    vector<wedge> wedges;

    void moveForward() {
        for (wedge &w : wedges) {
            w.moveForward(speed);
        }
    }
};

int main() {
    ifstream fin("spin.in");
    ofstream fout("spin.out");

    vector<wheel> wheels(5);

    for (int i = 0; i < 5; i++) {
        int n;
        fin >> wheels[i].speed >> n;
        for (int j = 0; j < n; j++) {
            int start, span; fin >> start >> span;
            wheels[i].wedges.push_back(wedge(start, span));
        }
    }

    for (int d = 0; d < 360; d++) {
        for (int theta = 0; theta < 360; theta++) {
            bool works2 = true;
            for (int j = 0; j < 5; j++) {
                bool works = false;
                for (wedge w : wheels[j].wedges) {
                    if (w.checkInside(theta)) {
                        works = true;
                        break;
                    }
                }

                if (!works) {
                    works2 = false;
                    break;
                }
            }

            if (works2) {
                fout << d << '\n';
                return 0;
            }
        }

        for (int i = 0; i < 5; i++) {
            wheels[i].moveForward();
        }
    }

    fout << "none\n";
    return 0;
}
