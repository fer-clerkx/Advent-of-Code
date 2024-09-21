#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using matrix = vector<vector<int>>;

void import_values(matrix& map, string* filename) {
    std::ifstream input(*filename);
    if (input.fail()) {
        std::cerr << "Error opening data file";
        exit(1);
    }

    while(!input.eof()) {
        map.push_back(vector<int>(100));
        for (int i = 0; i < map.back().size(); i++) {
            map.back().at(i) = input.get() - '0';
        }
        input.ignore(1);
    }

    input.close();
}

int sum_lowpoints(matrix& map) {
    int sum = 0;
    int up, down, left, right, center;
    for (int i = 0; i < map.size(); i++) {          //row
        for (int j = 0; j < map[i].size(); j++) {   //collumn
            center = map[i][j];
            if (center == 0)
                sum += 1;
            else {
                if (i == 0)
                up = 10;
                else
                    up = map[i-1][j];
                if (i == map.size() - 1)
                    down = 10;
                else
                    down = map[i+1][j];
                if (j == 0)
                    left = 10;
                else   
                    left = map[i][j-1];
                if (j == map[i].size() - 1)
                    right = 10;
                else
                    right = map[i][j+1];

                if (center < up && center < down && center < left && center < right) {
                    sum += center + 1;
                }
            }
        }
    }
    return sum;
}

void recursive(matrix& map, int row, int col, int* sum) {
    map[row][col] = 9;
    *sum = *sum + 1;
    if (map[row][col] != 0) {
        if (col != 0) {                         //left
            if (map[row][col-1] < 9)
                recursive(map, row, col - 1, sum);
        }
        if (row != 0) {                         //up
            if (map[row-1][col] < 9)
                recursive(map, row - 1, col, sum);
        }
        if (col != map[row].size() - 1) {       //right
            if (map[row][col+1] < 9)
                recursive(map, row, col + 1, sum);
        }
        if (row != map.size() - 1) {            //down
            if (map[row+1][col] < 9)
                recursive(map, row + 1, col, sum);
        }
    }
}

int get_basins(matrix& map) {
    vector<int> tops(3, 0);
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] < 9) {
                int local = 0;
                recursive(map, i, j, &local);
                if (local > tops[0]) {
                    tops[2] = tops[1];
                    tops[1] = tops[0];
                    tops[0] = local;
                }
                else if (local > tops[1]) {
                    tops[2] = tops[1];
                    tops[1] = local;
                }
                else if (local > tops[2])
                    tops[2] = local;
            }
        }
    }
    for (int ele : tops)
        cout << ele << '\n';
    return tops[0] * tops[1] * tops[2];
}

int main() {
    string input_file = "Data/Day9.txt";
    matrix map;
    import_values(map, &input_file);
    cout << get_basins(map);
}