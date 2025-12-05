import re
from enum import IntEnum

with open("25/inputs/input05.txt") as input_file:
    fresh_string_list = []
    while True:
        string = input_file.readline()
        if string != '\n':
            fresh_string_list.append(string)
        else:
            break
    ingredient_list = input_file.readlines()

EndpointType = IntEnum('EndpointType', [('START', 0), ('END', 1)])
endpoint_list = []
for string in fresh_string_list:
    re_match = re.match(r"(\d+)-(\d+)", string)
    endpoint_list.append((int(re_match[1]), EndpointType.START))
    endpoint_list.append((int(re_match[2]), EndpointType.END))

# Merge overlapping ranges
endpoint_list.sort()
fresh_range_list = []
start_count = 0
for endpoint in endpoint_list:
    if start_count == 0:
        current_start = endpoint[0]
    if endpoint[1] == EndpointType.START:
        start_count += 1
    else:
        start_count -= 1
        if start_count == 0:
            fresh_range_list.append(range(current_start, endpoint[0] + 1))

sum = 0
for ingredient in ingredient_list:
    for fresh_range in fresh_range_list:
        if int(ingredient) in fresh_range:
            sum += 1
            break
print(f"Part A: {sum}")

sum = 0
for fresh_range in fresh_range_list:
    sum += len(fresh_range)
print(f"Part B: {sum}")
