#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef struct str str;
struct str {
    string s;
    vector<int> f;
};

string rev(string, int);
vector<int> copy(vector<int>);

int main() {
    string s; cin >> s;

    vector<str> queue;
    str first;
    first.s = s;
    first.f = {};
    for (int i = 0; i < s.size(); i++) {
        vector<str> newqueue;
        for (int j = 0; j < queue.size(); j++) {
            str val1, val2;
            val1.s = queue[i].s;
            val2.s = rev(queue[j].s, i + 1);
            cout << val1.s << ' ' << val2.s << '\n';
            val1.f = copy(queue[j].f);
            val2.f = copy(queue[j].f);
            val1.f.push_back(0);
            val2.f.push_back(1);

            newqueue.push_back(val1);
            newqueue.push_back(val2);
        }

        sort(newqueue.begin(), newqueue.end(), [](const str &a, const str &b) {
            return a.s < b.s;
        });

        queue = vector<str>(0);
        queue.push_back(newqueue[0]);
        queue.push_back(newqueue[1]);

        if (queue.size() > 2) {
            queue.push_back(newqueue[newqueue.size() - 1]);
            queue.push_back(newqueue[newqueue.size() - 2]);
        }
    }

    cout << queue[0].s << '\n';
    for (int i : queue[0].f) {
        cout << i << ' ';
    }

    cout << '\n';
    return 0;
}

string rev(string s, int n) {
    string ans = "";
    for (int i = 0; i < n; i++) {
        ans += s[n - i - 1];
    }

    ans += s.substr(n, s.size() - n);
    return ans;
}

vector<int> copy(vector<int> x) {
    vector<int> copy;
    for (int i = 0; i < x.size(); i++) {
        copy.push_back(x[i]);
    }

    return copy;
}
