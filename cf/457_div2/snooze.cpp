#include <iostream>

using namespace std;

typedef struct mytime mytime;

struct mytime {
	int hour, minute;
	
	mytime(int h, int m) {
		hour = h;
		minute = m;	 
	}

	void subTime(int min) {
		minute -= min;
		while (minute < 0) {
			minute += 60;
			hour--;
		}

		while (hour < 0) {
			hour += 24;
		}

		hour = hour % 24;
	}

	bool checkSeven() {
		if (hour % 10 == 7) {
			return true;
		}

		if (minute % 10 == 7) {
			return true;
		}

		return false;
	}
};

int main() {
	int x; cin >> x;
	int h, m; cin >> h >> m;
	
	mytime t(h, m);

	int count = 0;

	while (!t.checkSeven()) {
		t.subTime(x);
		count++;
	}

	cout << count << endl;
	return 0;
}
