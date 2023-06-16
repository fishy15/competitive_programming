#include <iostream>
#include <set>

using namespace std;

int bfs(int n, int m) {
	bool notFound = true;
	set<int> cur;
	cur.insert(n);
	int level = 0;
	while (notFound) {
		set<int> next;
		for (auto i : cur) {
			if (i == m) {
				notFound = false;
				break;
			}

			int a = i - 1;
			int b = i * 2;

			if (a > 0) {
				next.insert(a);
			}

			if (b < 2*m) {
				next.insert(b);
			}
		}

		cur = next;
		//cout << level << endl;
		level++;
	}

	return (level - 1);
}



int main() {
	int n, m; cin >> n >> m;

	if (n > m) {
		cout << (n - m) << "\n";
	} else {
		cout << bfs(n, m) << "\n";
	}

	return 0;
}


