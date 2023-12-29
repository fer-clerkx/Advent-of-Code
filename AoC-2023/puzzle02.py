import re

FILE_PATH = f"input/input{__file__[-5:-3]}.txt"
NUM_RED_CUBES = 12
NUM_GREEN_CUBES = 13
NUM_BLUE_CUBES = 14

def main():
    solutionA = solvePuzzle02A()
    print("Solution A:", solutionA)
    solutionB = solvePuzzle02B()
    print("Solution B:", solutionB)

def solvePuzzle02A():
    inputFile = open(FILE_PATH, "r", encoding="UTF-8")
    sum = 0
    while True:
        line = inputFile.readline()
        if line == "":
            break
        Paterns = (
            "^Game (?P<ID>\d+):",
            "(?P<red>\d+) red",
            "(?P<green>\d+) green",
            "(?P<blue>\d+) blue"
        )
        matches = re.finditer('|'.join(Paterns), line)
        gamePosible = True
        gameID = int(next(matches).group('ID'))
        for match in matches:
            if match.group('red') and int(match.group('red')) > NUM_RED_CUBES:
                gamePosible = False
            elif match.group('green') and int(match.group('green')) > NUM_GREEN_CUBES:
                gamePosible = False
            elif match.group('blue') and int(match.group('blue')) > NUM_BLUE_CUBES:
                gamePosible = False
        if gamePosible:
            sum += gameID
    return sum

def solvePuzzle02B():
    inputFile = open(FILE_PATH, "r", encoding="UTF-8")
    sum = 0
    while True:
        line = inputFile.readline()
        if line == "":
            break
        Paterns = (
            "(?P<red>\d+) red",
            "(?P<green>\d+) green",
            "(?P<blue>\d+) blue"
        )
        matches = re.finditer('|'.join(Paterns), line)
        redMax = greenMax = blueMax = 0
        for match in matches:
            if match.group('red') and int(match.group('red')) > redMax:
                redMax = int(match.group('red'))
            elif match.group('green') and int(match.group('green')) > greenMax:
                greenMax = int(match.group('green'))
            elif match.group('blue') and int(match.group('blue')) > blueMax:
                blueMax = int(match.group('blue'))
        sum += redMax*greenMax*blueMax
    return sum

main()