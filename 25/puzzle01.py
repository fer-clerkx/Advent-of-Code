with open("25/inputs/input01.txt") as input:
    input_strs = input.readlines()

sum = 0
dial = 50
for input_string in input_strs:
    rotation_value = int(input_string[1:])
    if input_string[0] == 'L':
        rotation_value *= -1
    dial = (dial + rotation_value) % 100
    if dial == 0:
        sum += 1

print(f"Part A: {sum}")

sum = 0
dial = 50
for input_string in input_strs:
    rotation_value = int(input_string[1:])
    if input_string[0] == 'L':
        rotation_value *= -1

    dial_copy = dial
    dial += rotation_value

    dial_wrapped = dial % 100
    num_wraps = int(abs(dial - dial_wrapped) / 100)
    dial = dial_wrapped

    sum += num_wraps
    if rotation_value < 0:
        if dial_copy == 0:
            sum -= 1
        if dial == 0:
            sum += 1


print(f"Part B: {sum}")
