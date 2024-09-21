#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using list = vector<vector<string>>;
using std::cout;

void import_values(list& connections, const string* filename) {
    std::ifstream input(*filename);
    if (input.fail()) {
        std::cerr << "Error opening input file";
        exit(1);
    }
    char buffer[6];
    while (!input.eof()) {
        connections.resize(connections.size() + 1, vector<string>(2));
        input.getline(buffer, 6, '-');
        connections.back()[0] = buffer;
        input.getline(buffer, 6);
        connections.back()[1] = buffer;
    }
    input.close();
}

void recursive(list copy, list& paths, string loc, vector<string> current_path, const string& intermediate) {
    current_path.push_back(loc);
    vector<string> next;

    for (int i = 0; i < copy.size(); i++) {
        for (int j = 0; j < 2; j++) {
            if (copy[i][j] == loc) {
                if (islower(loc[0])) {
                    copy[i].erase(copy[i].begin() + j);
                    next.push_back(copy[i][0]);
                    copy.erase(copy.begin() + i);
                    j = 2;
                    i--;
                } else if (j == 0) {
                    if (loc == intermediate) {
                        copy[i][0][0] += 0x20;
                        copy[i][0][1] += 0x20;
                    }
                    next.push_back(copy[i][1]);
                    j = 1;   
                } else {
                    if (loc == intermediate) {
                        copy[i][1][0] += 0x20;
                        copy[i][1][1] += 0x20;
                    }
                    next.push_back(copy[i][0]);
                    j = 1;
                }
            }
        }
    }

    if (loc == "end") {
        paths.push_back(current_path);
        current_path.erase(current_path.end() - 1);
    }
    else {
        for (string ele : next) {
            recursive(copy, paths, ele, current_path, intermediate);
        }
    }
}

int main() {
    string input_file = "../Data/Day12test.txt";
    list connections;
    import_values(connections, &input_file);

    list paths;
    vector<string> current_path;
    current_path.reserve(10);
    vector<string> SmallCaves;
    for (vector<string>& row : connections) {
        for (string& ele : row) {
            if (ele != "start" && ele != "end" && islower(ele[0])) {
                if (std::find(SmallCaves.begin(), SmallCaves.end(), ele) == SmallCaves.end()) {
                    SmallCaves.push_back(ele);
                }
            }
        }
    }


    //int max_paths = 0;
    for (string& cave : SmallCaves) {
        for (vector<string>& row : connections) {
            while (std::find(row.begin(), row.end(), cave) != row.end()) {
                vector<string>::iterator ChangedCave = std::find(row.begin(), row.end(), cave);
                row[ChangedCave - row.begin()][0] -= 0x20;
                row[ChangedCave - row.begin()][1] -= 0x20;
            }
        }
        cave[0] -= 0x20;
        cave[1] -= 0x20;
        recursive(connections, paths, "start", current_path, cave);
        if (current_path.size() != 0) {
            "test\n";
        }
        for (vector<string>& row : connections) {
            while (std::find(row.begin(), row.end(), cave) != row.end()) {
                vector<string>::iterator ChangedCave = std::find(row.begin(), row.end(), cave);
                row[ChangedCave - row.begin()][0] += 0x20;
                row[ChangedCave - row.begin()][1] += 0x20;
            }
        }
        /*if (max_paths < paths.size()) {
            max_paths = paths.size();
        }
        paths.clear();*/
    }
    cout << paths.size();
}