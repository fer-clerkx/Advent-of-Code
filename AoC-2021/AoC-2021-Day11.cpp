#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using std::string;
using std::vector;
using matrix = vector<vector<int>>;
using std::cout;

void import_values(matrix& data, string* input_file) {
    std::ifstream input(*input_file);
    if (input.fail()) {
        std::cerr << "Error opening input file";
        exit(1);
    }
    while(!input.eof()) {
        data.resize(data.size() + 1, vector<int>(10));
        char buffer[11];
        input.getline(buffer, 11);
        for (int j = 0; j < 10; j++) {
            data.back()[j] = buffer[j] - '0';
        }
    }
}

void recursive(matrix& data, int* flashes, vector<int>& xy) {
    const matrix copy = data;
    int local_flash = 0;
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            if (copy[i][j] > 9) {
                local_flash++;
                xy.push_back(i);
                xy.push_back(j);
                if (i == 0)
                    data[i+1][j]++;
                else if (i == 9)
                    data[i-1][j]++;
                else {
                    data[i+1][j]++;
                    data[i-1][j]++;
                }
                if (j == 0)
                    data[i][j+1]++;
                else if (j == 9)
                    data[i][j-1]++;
                else {
                    data[i][j+1]++;
                    data[i][j-1]++;
                }
                if (i > 0) {
                    if (j > 0)
                        data[i-1][j-1]++;
                    if (j < 9)
                        data[i-1][j+1]++;
                }
                if (i < 9) {
                    if (j > 0)
                        data[i+1][j-1]++;
                    if (j < 9)
                        data[i+1][j+1]++;
                }
            }
        }
    }
    *flashes += local_flash;
    for (int i = 0; i < xy.size(); i += 2) {
        data[xy[i]][xy[i+1]] = 0;
    }
    if (local_flash > 0)
        recursive(data, flashes, xy);
}

int step (matrix& data, int* flashes) {
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            data[i][j]++;
        }
    }
    vector<int> xy;
    recursive(data, flashes, xy);
    return xy.size();
}

int main() {
    string filename = "Data/Day11.txt";
    matrix values;
    import_values(values, &filename);
    int flashes = 0;
    int counter = 0;
    do {
        counter++;
    } while(step(values, &flashes) != 200);
    cout << counter;
}