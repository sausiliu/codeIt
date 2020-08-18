#include <iostream>
#include <vector>

using namespace std

class Soution {
public:
	int numPairsDivisibleBy60(vector<int>& time) {
		if (time.size() <= 1) return 0;

		unordered_map<int, int> record;
		for(auto& t:time) t = t % 60;
		for(auto t:time) {
			int residue = (60 - t) % 60;
			if(record.fine(residue) != record.end()) {
				residue += record[residue];
			}
			record[t] += 1;
		}
	}

};

int main(int argc, char *argv[])
{
	int data[] = {20, 50, 50, 40, 10, 20, 30, 40, 50, 60, 70};

	vector<int> test(data, data + 10);
	cout << "hello world" << endl;

	new Soution();

	Soution();
	return 0;
}
