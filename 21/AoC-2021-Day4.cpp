#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
using boards_int = vector<vector<int>>;
using boards_bool = vector<vector<bool>>;

//Input:    filename:   path to file containg data
//          values:     vector for the drawn numbers
//          boards:     2D vector for the bingo boards
//          data:       pointer to 2D vector of bool's where report will be imported to
void import_values(string* filename, vector<int>& values, boards_int& boards) {
    //Open input file
    ifstream input(*filename);
    if(input.fail()) {
        cerr << "Error opening input file";
        exit(1);
    }
    //Import drawn numbers
    char temp[3];
    while (input.peek() != '\n') {
        input.getline(temp, 3, ',');            //Import values as chars
        values.push_back(stoi(temp, nullptr));  //Convert to ints and put in vector
    }
    //Import bingo boards
    while (!input.eof()) {                  //Iterate through all boards
        boards.resize(boards.size() + 1);
        int buffer;
        for (int i = 0; i < 25; i++) {      //Iterate through board
            input >> buffer;
            boards.back().push_back(buffer);
        }
    }
}

bool checkBingo(vector<bool> board, int position) {
    int countRow = 0;
    int countCol = 0;
    int row = position / 5;
    int col = position % 5;
    for (int i = 0; i < 5; i++) {
        if (board[row * 5 + i])
            countRow++;
        if (board[col + i * 5])
            countCol++;
    }
    bool result;
    if (countRow == 5 || countCol == 5)
        result = true;
    else   
        result = false;
    return result;
}

bool markNumber(int number, boards_int& unchecked, boards_bool& checked) {
	for (int i = 0; i < unchecked.size(); i++) {
		int to_check;
		for (int j = 0; j < unchecked[i].size(); j++) {
			if (unchecked[i][j] == number) {
				checked[i][j] = true;
				to_check = j;
                j = unchecked[i].size();
			}
		}
		if (checkBingo(checked[i], to_check)) {
            if (unchecked.size() > 1) {
                checked.erase(checked.begin() + i);
                unchecked.erase(unchecked.begin() + i);
                i--;
            }
            else
                return true;
        }
	}
    return false;
}

int calculate_score(vector<int>& board, vector<bool>& checked, int last_value) {
    for (int i = 0; i < board.size(); i++) {
        if (checked[i]) {
            checked.erase(checked.begin() + i);
            board.erase(board.begin() + i);
            i--;
        }
    }
    int sum = 0;
    for (int i = 0; i < board.size(); i++) {
        sum += board[i];
    }
    return sum * last_value;
}

int main() {
    string inputFile = "Data/Day4.txt";
    vector<int> values;
    boards_int unchecked;
    boards_bool checked;

    import_values(&inputFile, values, unchecked);
    checked.resize(unchecked.size());
    for (int i = 0; i < checked.size(); i++) {
        checked[i].resize(25, 0);
    }

    int drawn;
    for (int i = 0; i < values.size(); i++) {
        drawn = values[i];
        if (markNumber(drawn, unchecked, checked)) {
            drawn = values[i];
            i = values.size();
        }
    }
    int product = calculate_score(unchecked[0], checked[0], drawn);
    cout << "Number: " << drawn << '\n'
        << "Score: " << product << '\n'; 
}