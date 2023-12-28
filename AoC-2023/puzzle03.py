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
    numbers = [[]]*3
    gears = [[]]*3
    sum = 0
    while True:
        line = inputFile.readline()
        if line == "":
            # Iterate through gears[0]
            for gear in gears[0]:
                adjNum = []
                # Check numbers[1]
                for number in numbers[1]:
                    if gear.start()+1 == number.start() or gear.end()-1 == number.end():
                        adjNum.append(number)
                # Check numbers[0]
                for number in numbers[0]:
                    if gear.start()+1 >= number.start() and gear.end()-1 <= number.end():
                        adjNum.append(number)
                # If two numbers found -> calc product, add sum
                if len(adjNum) == 2:
                    sum += int(adjNum[0].group('number')) * int(adjNum[1].group('number'))
            break
        paterns = (
            "(?P<number>\d+)",
            "(?P<gear>[*])"
        )
        regex = '|'.join(paterns)
        matches = re.finditer(regex, line)

        # Shift numbers and gears
        numbers[2] = numbers[1]
        numbers[1] = numbers[0]
        gears[2] = gears[1]
        gears[1] = gears[0]

        # Load matches into numbers and gears
        numbers[0] = []
        gears[0] = []
        for match in matches:
            if match.group('number'):
                numbers[0].append(match)
            elif match.group('gear'):
                gears[0].append(match)

        # First 2 lines not finished?
        if numbers[2] == [] and gears[2] == []:
            # Skip to start of loop
            continue

        # Iterate through gears[1]
        for gear in gears[1]:
            adjNum = []
            # Check numbers[2]
            for number in numbers[2]:
                if gear.start()+1 >= number.start() and gear.end()-1 <= number.end():
                    adjNum.append(number)
            # Check numbers[1]
            for number in numbers[1]:
                if gear.start()+1 == number.start() or gear.end()-1 == number.end():
                    adjNum.append(number)
            # Check numbers[0]
            for number in numbers[0]:
                if gear.start()+1 >= number.start() and gear.end()-1 <= number.end():
                    adjNum.append(number)
            # If two numbers found -> calc product, add sum
            if len(adjNum) == 2:
                sum += int(adjNum[0].group('number')) * int(adjNum[1].group('number'))
    return sum


main()