#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using std::vector;
using std::string;
using std::cout;
using matrix = vector<vector<int>>;

//Imports vent values to vector vents
void import_values(string* filename, matrix& vents) {
    //Open input file
    std::ifstream input(*filename);
    if (input.fail()) {
        std::cerr << "Error opening file";
        exit(1);
    }

    while(!input.eof()) {
        vector<int> buffer(4);
        char temp[4];
        input.getline(temp, 4, ',');
        buffer[0] = std::stoi(temp, nullptr);
        input.getline(temp, 4, ' ');
        buffer[1] = std::stoi(temp, nullptr);
        input.getline(temp, 4, ' ');
        input.getline(temp, 4, ',');
        buffer[2] = std::stoi(temp, nullptr);
        input.getline(temp, 4);
        buffer[3] = std::stoi(temp, nullptr);

        if (buffer[0] == buffer[2] || buffer[1] == buffer[3]) {     //Horizontal or vertical lines
            if (buffer[0] > buffer[2])
                std::swap(buffer[0], buffer[2]);
            if (buffer[1] > buffer[3])
                std::swap(buffer[1], buffer[3]);
        }
        else {                                      //Diagonal lines
            if (buffer[0] > buffer[2]) {
               std::swap(buffer[0], buffer[2]);
               std::swap(buffer[1], buffer[3]);
            }
        }
        vents.push_back(buffer);
    }
}

//Size and initialize field matrix to 0
void init_field(matrix& field, matrix& vents) {
    int x_max = 0;
    int y_max = 0;
    for (int i = 0; i < vents.size(); i++) {
        if (x_max < vents[i][0])
            x_max = vents[i][0];
        if (y_max < vents[i][1])
            y_max = vents[i][1];
        if (x_max < vents[i][2])
            x_max = vents[i][2];
        if (y_max < vents[i][3])
            y_max = vents[i][3];
    }
    vector<int> temp(x_max + 1, 0);
    field.resize(y_max + 1, temp);
}

void fill_field(matrix& field, matrix& vents) {
    for (int i = 0; i < vents.size(); i++) {        //Iterate through every vent
        int x_0 = vents[i][0];
        int y_0 = vents[i][1];
        int x_end = vents[i][2];
        int y_end = vents[i][3];
        
        if (x_0 == x_end) {           //If vertical vent
            for (int j = y_0; j < y_end + 1; j++) {
                field[j][x_0]++;
            }
        }
        else if (y_0 == y_end) {      //Horizontal line
            for (int j = x_0; j < x_end + 1; j++) {
                field[y_0][j]++;
            }
        }
        else {                                      //Diagonal line
            int mod;
            if(y_0 < y_end)     //Positive slope
                mod = 1;
            else                //Negative slope
                mod = -1;

            for (int j = 0; j < x_end - x_0 + 1; j++) {
                field[y_0 + j * mod][x_0 + j]++;
            }
        }
    }
}

int count_intersections(matrix& field) {
    int count = 0;
    for (int i = 0; i < field.size(); i++) {
        for (int j = 0; j < field[i].size(); j++) {
            if (field[i][j] > 1)
                count++;
        }
    }
    return count;
}

int main() {
    string filename = "Data/Day5.txt";
    matrix vents;
    import_values(&filename, vents);

    matrix field;
    init_field(field, vents);
    fill_field(field, vents);
    cout << "Number of hot spots: " << count_intersections(field);
}