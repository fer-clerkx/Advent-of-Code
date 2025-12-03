with open("25/inputs/input03.txt") as input_file:
    input_lines = input_file.readlines()

input_lines = [line.strip() for line in input_lines]

# Part A
sum = 0
for line in input_lines:
    max_value = max(line[:-1])
    max_index = line.index(max_value)

    second_max_value = max(line[max_index+1:])

    combined_value = int(max_value + second_max_value)
    sum += combined_value

print(f"Part A: {sum}")

# Part B
sum = 0
for line in input_lines:
    digits = []
    last_index = -1
    for i in range(0, 12):
        digits.append(max(line[last_index+1:-(11-i) or None]))
        last_index = line[last_index+1:].index(digits[-1]) + last_index + 1

    combined_value = int(''.join(digits))
    sum += combined_value

print(f"Part B: {sum}")
