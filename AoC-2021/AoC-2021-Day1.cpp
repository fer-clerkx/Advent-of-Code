#include<iostream>
#include<fstream>
#include<vector>
#include<string>

//Input:	name of data file
//Output:	ammount of values bigger then the previous one
int check_depth_increase(std::string* filename) {

	//Import values
	std::ifstream input(*filename);
	std::vector<int> list;
	int temp;
	while (!input.eof()) {
		input >> temp;
		list.push_back(temp);
	}

	//Compare current value with previous one
	int count = 0;
	for (int i = 1; i < list.size(); i++) {
		if (list[i] > list[i - 1])
			count++;
	}

	return count;
}

//Input:	name of data file
//Output:	ammount of value windows(3 wide) bigger then the previous one
int check_depth_window_increase(std::string* filename) {
	//Import values
	std::ifstream input(*filename);
	std::vector<int> list;
	int temp;
	while (!input.eof()) {
		input >> temp;
		list.push_back(temp);
	}
	
	//Compare current value window with previously calculated one
	int count = 0;
	int prevSum = list[0] + list[1] + list[2];
	for (int i = 1; i < list.size() - 2; i++) {
		int currentSum = list[i] + list[i + 1] + list[i + 2];
		if (currentSum > prevSum)
			count++;
		prevSum = currentSum;
	}

	return count;
}

int main() {
	std::string inputFile = "/Data/day1.txt";
	std::cout << check_depth_increase(&inputFile) << " measurement(s) were bigger than the previous one\n";
	std::cout << check_depth_window_increase(&inputFile) << " measurement window(s) were bigger than the previous one\n";
}