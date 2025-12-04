import copy
from typing import Iterable

with open("25/inputs/input04.txt") as input_file:
    input_lines = input_file.readlines()

input_lines = [list(input_line.strip()) for input_line in input_lines]

class AdjecentIterator:
    def __init__(self, input: Iterable[Iterable], idx_y: int, idx_x: int):
        self.grid = input
        self.len_x = len(input[0])
        self.len_y = len(input)
        self.center_x = idx_x
        self.center_y = idx_y
        self.index = 0

    def __iter__(self):
        return self

    def __next__(self):
        while (True):
            if self.index == 9:
                raise StopIteration
            if self.index == 4:
                self.index += 1
                continue
            idx_y = self.center_y + self.index // 3 - 1
            idx_x = self.center_x + self.index % 3 - 1
            if idx_y < 0 or idx_y >= self.len_y \
               or idx_x < 0 or idx_x >= self.len_x:
                self.index += 1
                continue
            elem = self.grid[idx_y][idx_x]
            break
        self.index += 1
        return elem

def count_and_replace(input: Iterable[Iterable])\
        -> tuple[Iterable[Iterable], int]:
    sum = 0
    input_return_copy = copy.deepcopy(input)
    for y, row in enumerate(input):
        for x, elem in enumerate(row):
            if elem != '@':
                continue
            adjecent_count = 0
            for adjecent_elem in AdjecentIterator(input, y, x):
                adjecent_count += 1 if adjecent_elem == '@' else 0
            if adjecent_count < 4:
                sum += 1
                input_return_copy[y][x] = 'X'
    return input_return_copy, sum

_, sum = count_and_replace(input_lines)
print(f"Part A: {sum}")

sum = 0
while (True):
    input_lines, local_sum = count_and_replace(input_lines)
    sum += local_sum
    if local_sum == 0:
        break
print(f"Part B: {sum}")
