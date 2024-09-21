#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using std::string;
using std::vector;
using std::cout;
using matrix = vector<vector<string>>;
using std::find;

void import_values(string* filename, matrix& patterns, matrix& output) {
    std::ifstream input(*filename);
    if (input.fail()) {
        std::cerr << "Error opening input file";
        exit(1);
    }

    while(!input.eof()) {
        patterns.resize(patterns.size() + 1);
        patterns.back().resize(10);
        output.resize(output.size() + 1);
        output.back().resize(4);

        char buffer[10];
        for (int i = 0; i < 10; i++) {
            input >> buffer;
            patterns.back()[i] = buffer;
        }
        input >> buffer;
        for (int i = 0; i < 4; i++) {
            input >> buffer;
            output.back()[i] = buffer;
        }
    }

    input.close();
}

void find_segments(vector<string>& patterns, vector<char>& segments) {
    vector<int> numbers(patterns.size(), -1);
    for (int i = 0; i < 10; i++) {
        if (patterns[i].size() == 2)
            numbers[1] = i;
        else if (patterns[i].size() == 3)
            numbers[7] = i;
        else if (patterns[i].size() == 4)
            numbers[4] = i;
        else if (patterns[i].size() == 7)
            numbers[8] = i;
    }
    string one = patterns[numbers[1]];
    string seven = patterns[numbers[7]];
    for (int i = 0; i < 3; i++) {
        if (seven[i] != one[0] && seven[i] != one[1]) {
            segments[0] = seven[i];
        }
    }
    string four = patterns[numbers[4]];
    string three;
    for (auto pattern : patterns) {
        if (pattern.size() == 5) {
            int count = 0;
            for (auto  signal : pattern) {
                if (signal != one[0] && signal != one[1] && signal != segments[0])
                    count++;
            }
            if (count == 2)
                three = pattern;
        }
    }
    for (auto segment_4 : four) {
        if (segment_4 != one[0] && segment_4 != one[1]) {
            for (auto segment_3 : three) {
                if (segment_3 == segment_4) {
                    segments[3] = segment_4;
                }
            }
        }
    }
    for (auto segment_4 : four) {
        if (segment_4 != one[0] && segment_4 != one[1] && segment_4 != segments[3])
            segments[1] = segment_4;
    }
    for (auto segment_3 : three) {
        if (segment_3 != one[0] && segment_3 != one[1] && segment_3 != segments[0] && segment_3 != segments[3])
            segments[6] = segment_3;
    }
    string six;
    for (auto pattern : patterns) {
        if (pattern.size() == 6) {
            int count = 0;
            for (auto segment : pattern) {
                if(segment == one[0] || segment == one[1])
                    count++;
            }
            if (count == 1)
                six = pattern;
        }
    }
    for (auto segment_6 : six) {
        if (segment_6 == one[0]) {
            segments[5] = segment_6;
            segments[2] = one[1];
        }
        else if (segment_6 == one[1]) {
            segments[5] = segment_6;
            segments[2] = one[0];
        }
    }
    for (auto segment_3 : three) {
        if (segment_3 != segments[0] && segment_3 != segments[2] && segment_3 != segments[3] && segment_3 != segments[5])
            segments[6] = segment_3;
    }
    string eight = patterns[numbers[8]];
    for (auto segment : segments) {
        for (int i = 0; i < eight.size(); i++) {
            if (eight[i] == segment) {
                eight.erase(eight.begin()+i);
                i--;
            }
        }
    }
    segments[4] = eight[0];
}

int calculate_output(vector<string>& output, vector<char>& segments) {
    string number;
    for (string display : output) {
        switch (display.size()) {
            case 2: number += '1';
                break;
            case 3: number += '7';
                break;
            case 4: number += '4';
                break;
            case 7: number += '8';
                break;
            case 5: 
                if (find(display.begin(), display.end(), segments[4]) != display.end())
                    number += '2';
                else if (find(display.begin(), display.end(), segments[1]) != display.end())
                    number += '5';
                else
                    number += '3';
                break;
            case 6:
                if (find(display.begin(), display.end(), segments[3]) == display.end())
                    number += '0';
                else if (find(display.begin(), display.end(), segments[2]) != display.end())
                    number += '9';
                else
                    number += '6';
                break;
        }
    }
    return std::stoi(number, nullptr);;
}

int main() {
    string input_file = "Data/Day8.txt";
    matrix patterns;
    matrix output;
    import_values(&input_file, patterns, output);
    vector<vector<char>> segments(patterns.size(), vector<char>(patterns[0].size()));

    int sum = 0;
    for (int i = 0; i < patterns.size(); i++) {
        find_segments(patterns[i], segments[i]);
        sum += calculate_output(output[i], segments[i]);
    }
    cout << sum;
    //2: 1
    //3: 7
    //4: 4
    //5: 2, 3, 5
    //6: 0, 6, 9
    //7: 8
}