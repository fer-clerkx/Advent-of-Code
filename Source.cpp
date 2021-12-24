#include <iostream>
#include <vector>

using std::vector;

void markNumber(int number, vector<vector<int>> unchecked, vector<vector<bool>> checked) {
	for (int i = 0; i < unchecked.size(); i++) {
		vector<int> to_check;
		for (int j = 0; j < unchecked[i].size(); j++) {
			if (unchecked[i][j] == number) {
				checked[i][j] = true;
				to_check.push_back(j);
			}
		}
		checkBingo(checked[i], to_check);
	}
}

void checkBingo(vector<bool> board, vector<int> changed) {

}