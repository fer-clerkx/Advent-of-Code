import re
from collections import namedtuple

FILE_PATH = "input/input08.txt"

nodeTuple = namedtuple("nodeTuple", "name left right")

def main():
	# solutionA = solvePuzzle08A()
	# print("Solution A:", solutionA)
	solutionB = solvePuzzle08B()
	print("Solution B:", solutionB)

def solvePuzzle08A():
	with open(FILE_PATH, 'r', encoding="UTF-8") as inputFile:
		inputStrings = inputFile.readlines()

	instructions = re.findall("\w", inputStrings[0])

	nodes = {}
	for inputString in inputStrings[2:]:
		match = re.fullmatch("(?P<name>\w+) = \((?P<left>\w+), (?P<right>\w+)\)\s?", inputString)
		nodes[match.group("name")] = nodeTuple._make(match.group("name", "left", "right"))

	currentNode = nodes["AAA"]
	step = 0
	while True:
		for instruction in instructions:
			if currentNode.name == "ZZZ":
				break
			elif instruction == 'L':
				currentNode = nodes[currentNode.left]
			else:
				currentNode = nodes[currentNode.right]
			step += 1
		if currentNode.name == "ZZZ":
			break

	return step

def solvePuzzle08B():
	with open(FILE_PATH, 'r', encoding="UTF-8") as inputFile:
		inputStrings = inputFile.readlines()

	instructions = re.findall("\w", inputStrings[0])

	nodes = {}
	for inputString in inputStrings[2:]:
		match = re.fullmatch("(?P<name>\w+) = \((?P<left>\w+), (?P<right>\w+)\)\s?", inputString)
		nodes[match.group("name")] = nodeTuple._make(match.group("name", "left", "right"))

	currentNodes = []
	for node in iter(nodes.values()):
		if node.name[2] == 'A':
			currentNodes.append(node)

	step = 0
	while True:
		for instruction in instructions:
			for i, currentNode in enumerate(currentNodes):
				print(step)
				if instruction == 'L':
					currentNodes[i] = nodes[currentNode.left]
				else:
					currentNodes[i] = nodes[currentNode.right]
			step += 1
			if all(name[2] == 'Z' for name in list(zip(*currentNodes))[0]):
				break
		if all(name[2] == 'Z' for name in list(zip(*currentNodes))[0]):
			break

	return step

main()