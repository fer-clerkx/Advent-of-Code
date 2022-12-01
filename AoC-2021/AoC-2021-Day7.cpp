#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>
#include<climits>

using std::string;
using std::vector;
using std::cout;

void import_values(string* filename, vector<int>& values) {
    std::ifstream input(*filename);
    if (input.fail()) {
        std::cerr << "Error opening file";
        exit(1);
    }
    
    char buffer[5];
    while(!input.eof()) {
        input.getline(buffer, 5, ',');
        values.push_back(std::stoi(buffer, nullptr));
    }

    input.close();
}

int get_diff_sum(vector<int>& values, int target) {
    int sum = 0;
    int diff;
    for (int ele : values) {
         diff = abs(ele - target);
         for (int i = 0; i < diff; i++)
            sum += i + 1;
    }
    return sum;
}

void get_fuel(vector<int>& values, vector<int>& output) {
    const int last_pos = values[values.size() - 1] + 1;
    int position;
    int last_fuel = INT_MAX;
    for (int i = values[0]; i < last_pos; i++) {
        int fuel = get_diff_sum(values, i);
        if (fuel > last_fuel) {
            position = i - 1;
            i = last_pos;
        }
        else
            last_fuel = fuel;
    }
    output = {position, last_fuel};
}

int main() {
    string input_file = "Data/Day7.txt";
    vector<int> crabs;
    import_values(&input_file, crabs);
    std::sort(crabs.begin(), crabs.end());
    vector<int> results(2);
    get_fuel(crabs, results);
    cout << "Horizontal position " << results[0]
        << " requires " << results[1] << " fuel\n";
}