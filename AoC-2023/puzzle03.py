import re
import math

FILE_PATH = f"input/input{__file__[-5:-3]}.txt"

with open(FILE_PATH) as input_file:
    input_lines = input_file.read().split()

symbols_by_pos = {(row, col): (symbol, [])
                  for row, line in enumerate(input_lines)
                  for col, symbol in enumerate(line)
                  if symbol != "." and not symbol.isdigit()}

sum_parts = 0
for row, line in enumerate(input_lines):
    for match in re.finditer("\d+", line):
        for d_row in (-1, 0, 1):
            for col in range(match.start()-1, match.end()+1):
                if (row+d_row, col) in symbols_by_pos:
                    number = int(match.group(0))
                    sum_parts += number
                    symbols_by_pos[row+d_row, col][1].append(number)

sum_gears = sum(
                math.prod(numbers)
                for (symbol, numbers)in symbols_by_pos.values()
                if symbol == "*" and len(numbers) > 1
            )

print("Solution 1:", sum_parts)

print("Solution 2:", sum_gears)