import re
from collections import namedtuple

FILE_PATH = "input/test.txt"

def main():
	solutionA = solvePuzzle05A()
	print("Solution A:", solutionA)
	solutionB = solvePuzzle05B()
	print("Solution B:", solutionB)

def solvePuzzle05A():
	# Read input file
	inputFile = open(FILE_PATH, "r", encoding="UTF-8")
	inputLines = inputFile.readlines()
	inputFile.close()

	# Parse numbers from seeds
	numbers = list(map(int, re.findall("\d+", inputLines[0])))

	# Filter out map section headers
	inputMapsString = []
	for line in inputLines[1:]:
		if re.findall("^\d+[\d\s]+$", line):
			inputMapsString[-1].append(line)
		elif re.findall("map:", line):
			inputMapsString.append([])

	# Parse numbers from maps
	inputMaps = []
	mapTuple = namedtuple('mapTuple', 'destination source range')
	for inputMapStrings in inputMapsString:
		inputMaps.append([])
		for inputMapString in inputMapStrings:
			# Parse numbers into tuple and append to map
			inputMapList = map(int, re.findall("\d+", inputMapString))
			inputMaps[-1].append(mapTuple._make(inputMapList))

	# Iterate through numbers
	for i in range(len(numbers)):
		# Iterate through maps
		for inputMap in inputMaps:
			for mapLine in inputMap:
				# If number is in source range
				if numbers[i] >= mapLine.source and numbers[i] < mapLine.source+mapLine.range:
					# Update number
					numbers[i] = numbers[i]-mapLine.source+mapLine.destination
					# Each number only mapped once
					break
	# Return smallest number
	return min(numbers)

def solvePuzzle05B():
	# Read input file
	inputFile = open(FILE_PATH, "r", encoding="UTF-8")
	inputLines = inputFile.readlines()
	inputFile.close()

	# Parse number ranges from seeds
	numberRanges = []
	numberRangesRaw = list(map(int, re.findall("\d+", inputLines[0])))
	for i in range(0, len(numberRangesRaw), 2):
		numberRanges.append(range(numberRangesRaw[i], numberRangesRaw[i]+numberRangesRaw[i+1]))

	# Filter out map section headers
	inputMapsString = []
	for line in inputLines[1:]:
		if re.findall("^\d+[\d\s]+$", line):
			inputMapsString[-1].append(line)
		elif re.findall("map:", line):
			inputMapsString.append([])

	# Parse numbers from maps
	inputMaps = []
	mapTuple = namedtuple('mapTuple', 'destination source range')
	for inputMapStrings in inputMapsString:
		inputMaps.append([])
		for inputMapString in inputMapStrings:
			# Parse numbers into tuple and append to map
			inputMapList = map(int, re.findall("\d+", inputMapString))
			inputMaps[-1].append(mapTuple._make(inputMapList))

	# Return smallest number
	return 0

main()