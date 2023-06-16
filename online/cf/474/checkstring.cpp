#include <iostream>
#include <string>

using namespace std;

int main() {
	string name; cin >> name;
	bool fail = false; 
	int aCount = 1;
	int bCount = 0;
	int cCount = 0;
	
	for (int i = 1; i < name.size(); i++) {
		if (name[i] != 'a' && name[i] != 'b' && name[i] != 'c') {
			fail = true;
			break;
		}
		
		if (name[0] != 'a') {
			fail = true;
			break;
		}
		
		if (name[i] == 'a' && name[i - 1] == 'b') {
			fail = true;
			break;
		}
		
		if (name[i] == 'a' && name[i - 1] == 'c') {
			fail = true;
			break;
		}
		
		if (name[i] == 'b' && name[i - 1] == 'c') {
			fail = true;
			break;
		}
		
		if (name[i] == 'c' && name[i - 1] == 'a') {
			fail = true;
			break;
		}
		
		if (name[i] == 'a') {
			aCount++;
		}
		
		if (name[i] == 'b') {
			bCount++;
		}
		
		if (name[i] == 'c') {
			cCount++;
		}
	}
	
	//cout << aCount << " " << bCount << " " << cCount << " ";
	if ((aCount == cCount ||bCount == cCount) && !fail && name.size() >= 3) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
	}
}
