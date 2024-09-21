import re
import numpy as np

FILE_PATH = f"input/input{__file__[-5:-3]}.txt"

with open(FILE_PATH) as input_file:
    input_lines = input_file.readlines()

left_groups = [{int(number) for number in re.split("[:|]", line)[1].split()}
               for line in input_lines]
right_groups = [{int(number) for number in re.split("[:|]", line)[2].split()}
                for line in input_lines]

matches_per_line = [len(left & right) for (left, right)
                                      in zip(left_groups, right_groups)]
points = sum(2 ** (matches-1) for matches in matches_per_line if matches > 0)

print(f"Solution 1: {points}")

num_cards = np.ones(len(input_lines), dtype=np.uint32)
for i, num_matches in enumerate(matches_per_line):
    num_cards[i+1 : i+1+num_matches] += num_cards[i]

print(f"Solution 2: {num_cards.sum()}")