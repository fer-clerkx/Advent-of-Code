import regex as re

FILE_NAME = "input/input01.txt"
NUMBER_DICT = {
	"one": 1,
	"two": 2,
	"three": 3,
	"four": 4,
	"five": 5,
	"six": 6,
	"seven": 7,
	"eight": 8,
	"nine": 9
}

def main():
	solutionA = solvePuzzle01A()
	print("Solution A:", solutionA)
	solutionB = solvePuzzle01B()
	print("Solution B:", solutionB)

def solvePuzzle01A():
	inputFile = open(FILE_NAME, "r", encoding="UTF-8")
	sum = 0
	while True:
		line = inputFile.readline()
		if line == '':
			break
		digits = re.findall('\d', line)
		sum += int(digits[0])*10+int(digits[-1])
	return sum

def solvePuzzle01B():
	inputFile = open(FILE_NAME, "r", encoding="UTF-8")
	sum = 0
	while True:
		line = inputFile.readline()
		if line == '':
			break
		patern = '\d|' + '|'.join(NUMBER_DICT.keys())
		digits = re.findall(patern, line, overlapped=True)
		if NUMBER_DICT.get(digits[0]):
			digitFirst = NUMBER_DICT.get(digits[0])
		else:
			digitFirst = int(digits[0])
		if NUMBER_DICT.get(digits[-1]):
			digitLast = NUMBER_DICT.get(digits[-1])
		else:
			digitLast = int(digits[-1])
		sum += digitFirst*10+digitLast
	return sum

main()