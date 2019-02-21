#include <iostream>
#include <string> 

using namespace std;

typedef struct mytime mytime;

struct mytime {
	int hour, minute;

	mytime(int h, int m) {
		hour = h;
		minute = m;
	}

	void addMin() {
		minute++;
		
		if (minute > 59) {
			minute -= 60;
			hour++;
		}

		hour = hour % 24;
	}

	bool checkPali() {
		return (hour / 10 == minute % 10) && (hour % 10 == minute / 10);
	}
};

int main() {
	string time; cin >> time;
	int h = (time[0] - '0') * 10 + time[1] - '0';
	int m = (time[3] - '0') * 10 + time[4] - '0';
	mytime t(h, m);

	int count = 0;
	while (!t.checkPali()) {
		t.addMin();
		count++;
	}

	cout << count << endl;

	return 0;
}
