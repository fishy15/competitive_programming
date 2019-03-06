#include <iostream>
#include <vector>

using namespace std;

vector<int> ppl;
vector<int> size;
vector<bool> happy;

int find(int a) {
	if (ppl[a] == a) {
		return a;
	}
	
	ppl[a] = find(ppl[a]);
	return ppl[a];
}

void join(int a, int b) {
	if ((a = find(a)) != (b = find(b))) {
		if (size[a] > size[b]) {
			ppl[b] = ppl[a];
			size[b] += size[a];
		} else {
			ppl[a] = ppl[b];
			size[a] += size[b];
		}
		
		happy[a] = happy[a] || happy[b];
		happy[b] = happy[a] || happy[b];
	}
}

int main() {
	int n, m; 
	cin >> n >> m;
	ppl = vector<int>(n + m);
	size = vector<int>(n + m);
	happy = vector<bool>(n + m);
	
	for (int i = 0; i < n + m; i++) {
		ppl[i] = i;
		size[i] = 1;
		happy[i] = false;
	}
	
	int b; cin >> b;
	for (int i = 0; i < b; i++) {
		int x; cin >> x;
		happy[x] = true;
	}
	
	int g; cin >> g;
	for (int i = 0; i < g; i++) {
		int x; cin >> x;
		happy[x + n] = true;
	}
	
	for (int i = 0; i < n * m; i++) {
		join(i % n, i % m + n);
	}
	
	for (int i = 0; i < n + m; i++) {
		if (!happy[find(i)]) {
			cout << "No\n";
			return 0;
		}
	}
	
	cout << "Yes\n";
	return 0;
}