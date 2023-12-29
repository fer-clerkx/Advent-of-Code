import re
import math

FILE_PATH = f"input/input{__file__[-5:-3]}.txt"

with open(FILE_PATH) as input_file:
    input_lines = input_file.readlines()


sum_IDs = 0
sum_powers = 0
for line in input_lines:
    line_parts = re.sub("[:,;]", "", line).split()
    color_max = {}
    for number, color in zip(line_parts[2::2], line_parts[3::2]):
        color_max[color] = max(color_max.get(color, 1), int(number))

    if (color_max["red"] <= 12 and color_max["green"] <= 13
            and color_max["blue"] <= 14):
        sum_IDs += int(line_parts[1])
    sum_powers += math.prod(color_max.values())

# Part 1
print("Solution 1:", sum_IDs)

# Part 2
print("Solution 2:", sum_powers)