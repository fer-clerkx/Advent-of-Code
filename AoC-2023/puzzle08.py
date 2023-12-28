import re,itertools
import numpy as np
from collections import namedtuple

FILE_PATH = "input/input08.txt"

nodeTuple = namedtuple("nodeTuple", "name left right")

def main():
    solutionA = solvePuzzle08A()
    print("Solution A:", solutionA)
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
            if instruction == 'L':
                currentNode = nodes[currentNode.left]
            else:
                currentNode = nodes[currentNode.right]
            step += 1
            if currentNode.name == "ZZZ":
                break
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

    loopLengths = []
    for i, currentNode in enumerate(currentNodes):
        step = 0
        states = {}
        for j, instruction in enumerate(itertools.cycle(instructions)):
            # Check if state is in map
            if (currentNode, j%len(instructions)) in states:
                break
            states[(currentNode, j%len(instructions))] = step
            if instruction == 'L':
                currentNode = nodes[currentNode.left]
            else:
                currentNode = nodes[currentNode.right]
            step += 1
        loopEntryStep = states[(currentNode, j%len(instructions))]
        loopLengths.append(step-loopEntryStep)
    return np.lcm.reduce(loopLengths)

main()