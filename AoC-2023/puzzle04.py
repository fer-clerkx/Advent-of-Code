import re
import numpy as np

FILE_PATH = f"input/input{__file__[-5:-3]}.txt"

with open(FILE_PATH) as input_file:
    input_lines = input_file.readlines()

left_groups = (map(int, re.split("[:|]", line)[1].split())
               for line in input_lines)
right_groups = ({int(number): True
                 for number in re.split("[:|]", line)[2].split()}
                 for line in input_lines)
num_cards = np.ones(len(input_lines), dtype=np.uint32)

points = 0
for i, (left_numbers, right_numbers) in enumerate(
                                        zip(left_groups, right_groups)):
    num_matches = len([card for card in left_numbers & right_numbers.keys()])
    points += 2**(num_matches-1) if num_matches > 0 else 0
    num_cards[i+1:i+1+num_matches] += num_cards[i]

print("Solution 1:", points)

print("Solution 2:", sum(num_cards))