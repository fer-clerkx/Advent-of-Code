import re

FILE_NAME = "input/input01.txt"
NUMBER_DICT = {
    "one": "one1one",
    "two": "two2two",
    "three": "three3three",
    "four": "four4four",
    "five": "five5five",
    "six": "six6six",
    "seven": "seven7seven",
    "eight": "eight8eight",
    "nine": "nine9nine"
}

with open(FILE_NAME) as input_file:
    input_string = input_file.read().strip()

def sum_of_digits(string: str):
    strings = string.split("\n")
    digit_lines = [re.findall('\d', string) for string in strings]
    return sum(int(digits[0] + digits[-1]) for digits in digit_lines)


# Part 1
print("Solution 1:", sum_of_digits(input_string))

# Part 2
for key, value in NUMBER_DICT.items():
    # Place text version on both sides to make sure overlapping numbers
    # are still detected.
    input_string = input_string.replace(key, value)
print("Solution 2:", sum_of_digits(input_string))