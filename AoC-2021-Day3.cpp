#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using matrix = std::vector<std::vector<bool>>;

//Input:    filename:   path to file containg diagnostic report
//          data:       pointer to 2D vector of bool's where report will be imported to
void import_values(std::string* filename, matrix& data) {
    //Open input file
    std::ifstream input(*filename);
    if(input.fail()) {
        std::cerr << "Error opening input file";
        exit(1);
    }

    //Import diagnostic report
    std::string c_temp;
    while(!input.eof()) {
        std::vector<bool> b_temp;
        input >> c_temp;    //Import as string
        for (int i = 0; i < 12; i++) {
            b_temp.push_back(c_temp[i] - '0');   //Convert from ASCII to bool
        }
        data.push_back(b_temp);
    }
}

//Input:    pointer to vector of bool's containing input data
//Output:   Returns bool which represents the most common bit
//          In the event of an even amount of 1's and 0's, a 1 will be returned
bool get_most_common_bit(matrix input, int position) {
    //Count amount of 1's
    int count = 0;
    for (int i = 0; i < input.size(); i++) {
        if (input[i][position])
            count++;
    }

    //Compare amount of 1's and 0's
    bool result;
    if (count >= round(input.size() / double(2)))
        result = 1;
    else
        result = 0;
    
    return result;
}

//Input:    pointer to vector of bool's containing input data
//Output:   Returns bool which represents the least common bit
//          In the event of an even amount of 1's and 0's, a 0 will be returned
bool get_least_common_bit(matrix input, int position) {
    //Count amount of 1's
    int count = 0;
    for (int i = 0; i < input.size(); i++) {
        if (input[i][position])
            count++;
    }

    //Compare amount of 1's and 0's
    bool result;
    if (count >= round(input.size() / double(2)))
        result = 0;
    else
        result = 1;
    
    return result;
}

//Input:    binary: binary value
//          width: size of binary
//Output:   Decimal version of input
int binary_to_decimal(std::vector<bool> binary, int width) {
    int decimal = 0;
    for (int i = 0; i < width; i++) {
        int multiplier = pow(2, width - i - 1);
        decimal += binary[i] * multiplier;
    }
    return decimal;
}

//Input:    name of file containing diagnostic report
//From the input file, calculate the gamma- and epsilon rate, and from that calculate the power consumption
//Output:   the power consumption
int calculate_power_consumption(matrix data) {
    //Calculate binary gamma and epsilon values
    std::vector<bool> b_gamma(12);
    std::vector<bool> b_epsilon(12);
    for(int i = 0; i < 12; i++) {   //Itterate through each position
        b_gamma[i] = get_most_common_bit(data, i);
        b_epsilon[i] = !b_gamma[i];
    }

    //Calculate decimal gamma and epsilon values
    int d_gamma = binary_to_decimal(b_gamma, 12);
    int d_epsilon = binary_to_decimal(b_epsilon, 12);

    //Calculate power consumption
    int power = d_gamma * d_epsilon;
    return power;
}

//Input:    pointer to 2D vector of bool's
//Output:   oxygen rating
int calculate_oxygen_rating(matrix data) {
    matrix clone = data;        //Create copy of data to modify
    bool mcb;       //most common bit
    
    //itterate through all 12 bits
    for(int i = 0; i < 12; i++) {
        mcb = get_most_common_bit(clone, i);    //get mcb for current bit position
        for(int j = 0; j < clone.size(); j++) {
            if(clone[j][i] != mcb) {
                clone.erase(std::next(clone.begin(), j));      //Erase words that don't match mcb
                j--;    //prevents wrongly itterating through vector due to shifted index's
            }
        }
        if(clone.size() == 1)        //Stop if only one word remains
            i = 12;
    }
    return binary_to_decimal(clone[0], 12);
}

//Input:    pointer to 2D vector of bool's
//Output:   CO2 rating
int calculate_co2_rating(matrix data) {
    matrix clone = data;        //Create copy of data to modify
    bool lcb;       //least common bit
    
    //itterate through all 12 bits
    for(int i = 0; i < 12; i++) {
        lcb = get_least_common_bit(clone, i);    //get lcb for current bit position
        for(int j = 0; j < clone.size(); j++) {
            if(clone[j][i] != lcb) {
                clone.erase(std::next(clone.begin(), j));      //Erase words that don't match lcb
                j--;     //prevents wrongly itterating through vector due to shifted index's
            }
        }
        if(clone.size() == 1)        //Stop if only one word remains
            i = 12;
    }
    return binary_to_decimal(clone[0], 12);
}

int calculate_life_support_rating(matrix data) {
    int oxygen_rating = calculate_oxygen_rating(data);
    int co2_rating = calculate_co2_rating(data);
    int life_support_rating = oxygen_rating * co2_rating;
    return life_support_rating;
}

int main() {
    std::string inputFile = "Data/Day3.txt";
    matrix data;
    import_values(&inputFile, data);

    std::cout << "Power consumption: " << calculate_power_consumption(data) << '\n';
    std::cout << "Life Support Rating: " << calculate_life_support_rating(data) << '\n';
}