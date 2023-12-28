import numpy as np

FILE_PATH = "input/input09.txt"

def main():
    solutionA = solvePuzzle09A()
    print("Solution A:", solutionA)
    solutionB = solvePuzzle09B()
    print("Solution B:", solutionB)

def solvePuzzle09A():
    inputSeqs = []
    with open(FILE_PATH, "r", encoding="UTF-8") as inputFile:
        inputLines = inputFile.readlines()
        for inputLine in inputLines:
            inputSeqs.append(np.asarray(inputLine.split(' '), dtype=int))

    sum = 0
    for inputSeq in inputSeqs:
        sum += recursiveSolverA(inputSeq)

    return sum

def recursiveSolverA(seq):
    diffSeq = np.diff(seq)
    if len(set(diffSeq)) > 1:
        return seq[-1] + recursiveSolverA(diffSeq)
    else:
        return seq[-1] + diffSeq[0]

def solvePuzzle09B():
    inputSeqs = []
    with open(FILE_PATH, "r", encoding="UTF-8") as inputFile:
        inputLines = inputFile.readlines()
        for inputLine in inputLines:
            inputSeqs.append(np.asarray(inputLine.split(' '), dtype=int))

    sum = 0
    for inputSeq in inputSeqs:
        sum += recursiveSolverB(inputSeq)

    return sum

def recursiveSolverB(seq):
    diffSeq = np.diff(seq)
    if len(set(diffSeq)) > 1:
        return seq[0] - recursiveSolverB(diffSeq)
    else:
        return seq[0] - diffSeq[0]

main()