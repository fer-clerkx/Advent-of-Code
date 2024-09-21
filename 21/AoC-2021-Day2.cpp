#include<iostream>
#include<fstream>
#include<vector>
#include<string>

//Input:	name of data file containing commands
//Calculates horizontal position and depth based on commands in the input file
//Output:	product of final horizontal position and depth
int calculate_position(std::string* filename) {

	//Open data file
	std::ifstream input(*filename);
	if(input.fail()){
		std::cerr << "Error loading input file";
		exit(1);
	}

	//Input values
	std::vector<std::string> oper;	//Vector containing operator
	std::vector<int> value;			//Vector containing operand
	std::string tempOper;
	int tempValue;
	while (!input.eof()) {
		input >> tempOper;
		input >> tempValue;
		oper.push_back(tempOper);
		value.push_back(tempValue);
	}

	//Calculate horizontal position and depth
	int horPos = 0;
	int depth = 0;
	for (int i = 0; i < oper.size(); i++) {
		if(oper[i] == "forward")
			horPos+= value[i];
		else if(oper[i] == "down")
			depth+= value[i];
		else if(oper[i] == "up")
			depth-= value[i];
		else
			std::cout << "Error: incorrecto operator\n";
	}
	
	//Calculate final product
	int product = horPos * depth;
	return product;
}

//Input:	name of data file containing commands
//Calculates horizontal position and depth based on commands in the input file using aim interpritation
//Output:	product of final horizontal position and depth
int calculate_position_with_aim(std::string* filename){
	
	//Open input file
	std::ifstream input(*filename);
	if(input.fail()) {
		std::cerr << "Error opening input file";
		exit(1);
	}

	//Import commands from input file
	std::vector<std::string> oper;
	std::vector<int> value;
	std::string tempOper;
	int tempValue;
	while(!input.eof()) {
		input >> tempOper;
		input >> tempValue;
		oper.push_back(tempOper);
		value.push_back(tempValue);
	}

	//Calculate horizontal position and depth
	int horPos = 0;
	int depth = 0;
	int aim = 0;
	for (int i = 0; i < oper.size(); i++) {
		if (oper[i] == "up")
			aim -= value[i];
		else if (oper[i] == "down")
			aim += value[i];
		else if (oper[i] == "forward") {
			horPos += value[i];
			depth += aim * value[i];
		}
		else
			std::cout << "Error: incorect operator\n";
	}

	//Calculate final product
	int product = horPos * depth;
	return product;
}

int main() {
	std::string inputFile = "Data/Day2.txt";
	std::cout << "Product without using aim: " << calculate_position(&inputFile) << '\n';
	std::cout << "Product using aim: " << calculate_position_with_aim(&inputFile) << '\n';
}