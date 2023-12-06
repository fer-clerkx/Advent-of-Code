import re

FILE_PATH = "input/input03.txt"

def main():
	solutionA = solvePuzzle03A()
	print("Solution A:", solutionA)
	solutionB = solvePuzzle03B()
	print("Solution B:", solutionB)

def solvePuzzle03A():
	inputFile = open(FILE_PATH, "r", encoding="UTF-8")
	lastNumbers = []
	lastSymbols = []
	sum = 0
	while True:
		line = inputFile.readline()
		if line == "":
			break
		paterns = (
			"(?P<number>\d+)",
			"(?P<symbol>[^\d.\s])"
		)
		regex = '|'.join(paterns)
		matches = re.finditer(regex, line)
		currentNumbers = []
		currentSymbols = []
		for match in matches:
			if match.group('number'):
				currentNumbers.append(match)
			elif match.group('symbol'):
				currentSymbols.append(match)
		# Check previous row numbers
		for number in lastNumbers:
			for symbol in currentSymbols:
				if symbol.end()-1 <= number.end() and symbol.start() >= number.start()-1:
					sum += int(number.group())
					break
		lastNumbers = []
		# Check previous row symbols
		for symbol in lastSymbols:
			for number in currentNumbers:
				if symbol.end()-1 <= number.end() and symbol.start() >= number.start()-1:
					sum += int(number.group())
		lastSymbols = currentSymbols
		# Check horizontally and update lastNumbers
		for number in currentNumbers:
			lastNumbers.append(number)
			for symbol in currentSymbols:
				if symbol.end() == number.start() or symbol.start() == number.end():
					sum += int(number.group())
					lastNumbers.pop() # Don't check number again
					break
	return sum

def solvePuzzle03B():
	inputFile = open(FILE_PATH, "r", encoding="UTF-8")
	numbers = []*3
	gears = []*3
	sum = 0
	while True:
		line = inputFile.readline()
		if line == "":
			break
		paterns = (
			"(?P<number>\d+)",
			"(?P<gear>*)"
		)
		regex = '|'.join(paterns)
		matches = re.finditer(regex, line)

		# Load matches into numbers and gears
		# First 2 lines not finished?
			# Skip to start of loop

		# Shift numbers and gears
		# Iterate through gears[1]
			# Check numbers[2]
			# Check numbers[1]
			# Check numbers[0]
			# If two numbers found -> calc product, add sum
	return sum


main()