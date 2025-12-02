import re
import math
import itertools
import time

start_time = time.time()

SEQUENCE_COMB = {
    1:  [],
    2:  [(2, 1)],
    3:  [(3, 1)],
    4:  [(4, 1), (2, 2)],
    5:  [(5, 1)],
    6:  [(6, 1), (3, 2), (2, 3)],
    7:  [(7, 1)],
    8:  [(8, 1), (4, 2), (2, 4)],
    9:  [(9, 1), (3, 3)],
    10: [(10, 1), (5, 2), (2, 5)]
}

def search_magnitude(search_range, sequence_length, num_sequences):
    sequences = range(int(str(search_range[0])[:sequence_length]),
                      int(str(search_range[-1])[:sequence_length]) + 1)

    invalid_ids = []
    for sequence in sequences:
        invalid_id = int(str(sequence) * num_sequences)
        if invalid_id in search_range:
            invalid_ids.append(invalid_id)

    return invalid_ids


with open("25/inputs/input02.txt") as input_file:
    input_str = input_file.readline()
regex = r"(?P<start>\d+)-(?P<end>\d+)"
matches = re.finditer(regex, input_str)

sequence_data = []
for match in matches:
    start = int(match["start"])
    end = int(match["end"])
    sequence_data.append((start, end,
                          int(math.log10(start)), int(math.log10(end))))

invalid_ids_A = []
invalid_ids_B = []
for start, end, start_magnitude, end_magnitude in sequence_data:
    for magnitude in range(start_magnitude, end_magnitude + 1):
        range_start = start if magnitude == start_magnitude else 10**magnitude
        range_end = end+1 if magnitude == end_magnitude else 10**(magnitude+1)
        num_digits = magnitude + 1

        # Part A
        if num_digits % 2 == 0:
            invalid_ids_A.append(search_magnitude(range(range_start, range_end),
                                                  num_digits // 2, 2))

        # Part B
        for num_sequences, sequence_length in SEQUENCE_COMB[num_digits]:
            invalid_ids_B.append(search_magnitude(range(range_start, range_end),
                                                  sequence_length, num_sequences))

invalid_ids_A = itertools.chain.from_iterable(invalid_ids_A)
print(f"Part A: {sum(invalid_ids_A)}")

invalid_ids_B = set(itertools.chain.from_iterable(invalid_ids_B))
print(f"Part B: {sum(invalid_ids_B)}")
print(time.time() - start_time)
