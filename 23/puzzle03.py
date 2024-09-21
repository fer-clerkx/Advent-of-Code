import re
import math

FILE_PATH = f"input/input{__file__[-5:-3]}.txt"

with open(FILE_PATH) as input_file:
    input_lines = input_file.read().split()

symbols_by_pos = {(row, col): (symbol, [])
                  for row, line in enumerate(input_lines)
                  for col, symbol in enumerate(line)
                  if symbol != "." and not symbol.isdigit()}

for row, line in enumerate(input_lines):
    for match in re.finditer("\d+", line):
        boundary = {(row, col) for row in range(row-1, row+2)
                               for col in range(match.start()-1,
                                                match.end()+1)}
        for symbol_pos in boundary & symbols_by_pos.keys():
            symbols_by_pos[symbol_pos][1].append(int(match.group(0)))

sum_parts = sum(sum(numbers) for (_, numbers) in symbols_by_pos.values())

sum_gears = sum(
                math.prod(numbers)
                for (symbol, numbers) in symbols_by_pos.values()
                if symbol == "*" and len(numbers) > 1
            )

print(f"Solution 1: {sum_parts}")

print(f"Solution 2: {sum_gears}")