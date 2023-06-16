#include <iostream>
#include <string>

using namespace std;

int main() {
	int count = 0;
	string top, bot; cin >> top >> bot;
	for (int i = 0; i < top.size() - 1; i++) {
		if (top[i] == '0' && top[i + 1] == '0' && bot[i] == '0') {
			top[i] = 'X';
			top[i + 1] = 'X';
			bot[i] = 'X';
			count++;
		} else if (top[i] == '0' && top[i + 1] == '0' && bot[i + 1] == '0') {
			top[i] = 'X';
			top[i + 1] = 'X';
			bot[i + 1] = 'X';
			count++;
		} else if (bot[i] == '0' && bot[i + 1] == '0' && top[i] == '0') {
			bot[i] = 'X';
			bot[i + 1] = 'X';
			top[i] = 'X';
			count++;
		} else if (bot[i] == '0' && bot[i + 1] == '0' && top[i + 1] == '0') {
			top[i] = 'X';
			top[i + 1] = 'X';
			bot[i + 1] = 'X';
			count++;
		}
	}

	cout << count << "\n";

	return 0;
}
	
