#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream fin("cowfind.in");
    ofstream fout("cowfind.out");

    string grass; fin >> grass;
    int sz = (int)(grass.size());
    vector<int> back, front;

    for (int i = 1; i < sz; i++) {
        if (grass[i] == '(' && grass[i - 1] == '(') {
            back.push_back(i);
        } else if (grass[i] == ')' && grass[i - 1] == ')') {
            front.push_back(i); 
        }
    }

    /*
    cout << "f: ";
    for (int i : front) {
        cout << i << ' ';
    }
    cout << '\n';

    cout << "b: ";
    for (int i : back) {
        cout << i << ' ';
    }
    cout << '\n';
    */

    int count = 0;
    for (int i = 0; i < front.size(); i++) {
        int min = 0;
        int max = back.size();

        while (min < max) {
            int mid = (min + max) / 2;
            //cout << min << ' ' << max << endl;
            if (back[mid] < front[i]) {
                min = mid + 1;
            } else {
                max = mid;
            }
        }

        //cout << max << '\n';
        //cout << "cool\n";
        count += max;
    }

    fout << count << '\n';

    return 0;
}
