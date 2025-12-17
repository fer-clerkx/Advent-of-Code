import re
from collections import defaultdict

with open("25/inputs/input07.txt") as file:
    input_string_list = [line.strip() for line in file.readlines()]

# Find start
start_index = input_string_list[0].find('S')

beam_dict = defaultdict(bool)
beam_dict[start_index] = True
split_counter = 0
for line in input_string_list[1:]:
    beam_dict_next = beam_dict.copy()
    for beam_index in beam_dict.keys():
        if beam_dict.get(beam_index) and line[beam_index] == '^':
            split_counter += 1
            beam_dict_next[beam_index] = False
            beam_dict_next[beam_index-1] = True
            beam_dict_next[beam_index+1] = True
    beam_dict = beam_dict_next

print(f"Part A: {split_counter}")

# Stores number of paths which reach that index
beam_dict = defaultdict(int)
beam_dict[start_index] = 1
for line in input_string_list[1:]:
    beam_dict_next = beam_dict
    beam_splitter_index_list = [x.start() for x in re.finditer(r'\^', line)]
    for beam_splitter_index in beam_splitter_index_list:
        beam_dict_next[beam_splitter_index-1] += beam_dict[beam_splitter_index]
        beam_dict_next[beam_splitter_index+1] += beam_dict[beam_splitter_index]
        beam_dict_next[beam_splitter_index] = 0
    beam_dict = beam_dict_next

print(f"Part B: {sum(beam_dict.values())}")
