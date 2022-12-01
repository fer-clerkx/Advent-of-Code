#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::string;
using std::vector;
using matrix = vector<string>;

void import_values(matrix& data, string* input_file) {
    std::ifstream input(*input_file);
    if (input.fail()) {
        std::cerr << "Error opening input file";
        exit(1);
    }

    while(!input.eof()) {
        char temp1[150];
        input.getline(temp1, 150);
        string temp2 = temp1;
        data.push_back(temp2);
    }
    input.close();
}

int get_incorrect(matrix& data) {
    int sum = 0;
    for (int j = 0; j < data.size(); j++) {
        string row = data[j];
        int temp = 0;
        for (int i = 1; i < row.size(); i++) {
            if (row[i] == ')') {
                if (row[i-1] == '(') {
                    row.erase(row.begin()+i);
                    row.erase(row.begin()+i-1);
                    i -= 2;
                } else {
                    temp = 3;
                    i = row.size();
                }
            } else if (row[i] == ']') {
                if (row[i-1] == '[') {
                    row.erase(row.begin()+i);
                    row.erase(row.begin()+i-1);
                    i -= 2;
                } else {
                    temp = 57;
                    i = row.size();
                }
            } else if (row[i] == '}') {
                if (row[i-1] == '{') {
                    row.erase(row.begin()+i);
                    row.erase(row.begin()+i-1);
                    i -= 2;
                } else {
                    temp = 1197;
                    i = row.size();
                }
            } else if (row[i] == '>') {
                if (row[i-1] == '<') {
                    row.erase(row.begin()+i);
                    row.erase(row.begin()+i-1);
                    i -= 2;
                } else {
                    temp = 25137;
                    i = row.size();
                }
            }
        }
        if (temp != 0) {
            sum += temp;
            data.erase(data.begin() + j);
            j--;
        }
    }
    return sum;
}

long long get_incomplete(matrix& data) {
    vector<long long> scores;
    for (string row : data) {
        for (int i = 0; i < row.size(); i++) {
            if (row[i] == ')' || row[i] == ']' || row[i] == '}' || row[i] == '>') {
                row.erase(row.begin() + i);
                row.erase(row.begin() + i - 1);
                i -= 2;
            }
        }
        string append;
        for (int i = row.size() - 1; i >= 0; i--) {
            switch(row[i]) {
                case '(':
                    append += ')';
                break;
                case '[':
                    append += ']';
                break;
                case '{':
                    append += '}';
                break;
                case '<':
                    append += '>';
                break;
            }
        }
        long long sum = 0;
        for (int i = 0; i < append.size(); i++) {
            sum *= 5;
            switch(append[i]) {
                case ')':
                    sum += 1;
                break;
                case ']':
                    sum += 2;
                break;
                case '}':
                    sum += 3;
                break;
                case '>':
                    sum += 4;
                break;
            }
        }
        scores.push_back(sum);
    }
    std::sort(scores.begin(), scores.end());
    return scores[scores.size() / 2];
}

int main() {
    matrix values;
    string filename = "Data/Day10.txt";
    import_values(values, &filename);
    get_incorrect(values);
    cout << get_incomplete(values);
}