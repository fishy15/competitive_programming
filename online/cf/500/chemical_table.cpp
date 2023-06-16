#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<int> vals;
vector<int> size;

int find(int a) {
	if (a == vals[a]) {
		return a;
	}
	
	return (vals[a] = find(vals[a]));
}

void join(int a, int b) {
	if ((a = find(a)) != (b = find(b))) {
		if (size[a] > size[b]) {
			vals[b] = vals[a];
			size[a] += size[b];
		} else {
			vals[a] = vals[b];
			size[b] += size[a];
		}
	}
}

int main() {
	int n, m, q; cin >> n >> m >> q;
	
	vals = vector<int>(n + m);
	size = vector<int>(n + m);
	
	for (int i = 0; i < n + m; i++) {
		vals[i] = i;
		size[i] = 1;
	}
	
	for (int i = 0; i < q; i++) {
		int x, y; cin >> x >> y;
		join(x - 1, n + y - 1);
	} 
	
	set<int> connect;
	for (int i = 0; i < n + m; i++) {
		connect.insert(find(i));
	}
	
	cout << connect.size() - 1 << '\n';
	return 0;
}