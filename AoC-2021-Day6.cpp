#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::string;
using std::vector;
using std::cout;

void import_values(string* filename, vector<long>& fish) {
    std::ifstream input(*filename);
    if (input.fail()) {
        std::cerr << "Error opeing file";
        exit(1);
    }

    char buffer[2];
    vector<int> values;
    while (!input.eof()) {
        input.getline(buffer, 2, ',');
        values.push_back(std::stoi(buffer, nullptr));
    }

    for (int i = 0; i < 7; i++) {
        for (int ele : values) {
            if (ele == i)
                fish[i]++;
        }
    }
}

void itterate(vector<long>& values) {
    std::rotate(values.begin(), values.begin() + 1, values.end() - 2);
    long ind6 = values[6];
    values[6] += values[7];
    values[7] = values[8];
    values[8] = ind6;
}

int main() {
    string filename = "Data/Day6.txt";
    vector<long> fish(9, 0);
    import_values(&filename, fish);

    for (int i = 0; i < 256; i++) {
        itterate(fish);
    }
    long sum = 0;
    for (long ele : fish)
        sum += ele;
    cout << sum;
}