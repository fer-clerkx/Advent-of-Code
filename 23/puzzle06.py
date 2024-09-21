import re, math

FILE_PATH = f"input/input{__file__[-5:-3]}.txt"

def main():
    solutionA = solvePuzzle06A()
    print("Solution A:", solutionA)
    solutionB = solvePuzzle06B()
    print("Solution B:", solutionB)

def solvePuzzle06A():
    with open(FILE_PATH, "r", encoding="UTF-8") as inputFile:
        inputStrings = inputFile.readlines()

    times = list(map(int, re.findall("\d+", inputStrings[0])))
    distances = list(map(int, re.findall("\d+", inputStrings[1])))

    # Solve equations
    product = 1
    for time, distance in zip(times, distances):
        D = time**2-4*distance
        lowerTime = math.ceil(math.nextafter((time-math.sqrt(D))/2, float("inf")))
        upperTime = math.floor(math.nextafter((time+math.sqrt(D))/2, 0))
        product *= upperTime-lowerTime+1

    return product

def solvePuzzle06B():
    with open(FILE_PATH, "r", encoding="UTF-8") as inputFile:
        inputStrings = inputFile.readlines()

    times = re.findall("\d+", inputStrings[0])
    distances = re.findall("\d+", inputStrings[1])

    time = int(''.join(times))
    distance = int(''.join(distances))

    # Solve equations
    D = time**2-4*distance
    lowerTime = math.ceil(math.nextafter((time-math.sqrt(D))/2, float("inf")))
    upperTime = math.floor(math.nextafter((time+math.sqrt(D))/2, 0))

    return upperTime-lowerTime+1

main()