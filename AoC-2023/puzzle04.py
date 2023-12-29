import re

FILE_PATH = f"input/input{__file__[-5:-3]}.txt"

def main():
    solutionA = solvePuzzle04A()
    print("Solution A:", solutionA)
    solutionB = solvePuzzle04B()
    print("Solution B:", solutionB)

def solvePuzzle04A():
    inputFile = open(FILE_PATH, "r", encoding="UTF-8")
    sum = 0
    while True:
        cardCount = 0
        line = inputFile.readline()
        if line == "":
            break

        # Split line into numbers
        subStrings = re.split("[:|]", line)
        leftNumberStrings = re.split("\s+", subStrings[1])
        rightNumberStrings = re.split("\s+", subStrings[2])
        # Filter out empty strings
        leftNumberStrings = list(filter(None, leftNumberStrings))
        rightNumberStrings = list(filter(None, rightNumberStrings))

        # Put left numbers in list
        leftNumbers = []
        for numberString in leftNumberStrings:
            leftNumbers.append(int(numberString))

        # Put right numbers in dictionary as key
        rightNumbers = {}
        for numberString in rightNumberStrings:
            rightNumbers[int(numberString)] = True

        # Iterate through left numbers
        for leftNumber in leftNumbers:
            # Check if leftNumber is key in dictionary
            if rightNumbers.get(leftNumber, False):
                cardCount += 1

        sum += 2**(cardCount-1) if cardCount > 0 else 0
    return sum

def solvePuzzle04B():
    with open(FILE_PATH, "r", encoding="UTF-8") as inputFile:
        inputFileSize = sum(1 for _ in inputFile)
    inputFile = open(FILE_PATH, "r", encoding="UTF-8")
    score = 0
    numCards = [1]*inputFileSize
    while True:
        line = inputFile.readline()
        if line == "":
            break

        # Split line into numbers
        subStrings = re.split("[:|]", line)
        # Get card number
        cardNumberMatch = re.search("\d+", subStrings[0])
        cardNumber = int(cardNumberMatch.group())
        # Get numbers
        leftNumberStrings = re.split("\s+", subStrings[1])
        rightNumberStrings = re.split("\s+", subStrings[2])
        # Filter out empty strings
        leftNumberStrings = list(filter(None, leftNumberStrings))
        rightNumberStrings = list(filter(None, rightNumberStrings))

        # Calculate matching numbers
        numMatches = 0
        # Put left numbers in list
        leftNumbers = []
        for numberString in leftNumberStrings:
            leftNumbers.append(int(numberString))

        # Put right numbers in dictionary as key
        rightNumbers = {}
        for numberString in rightNumberStrings:
            rightNumbers[int(numberString)] = True

        # Iterate through left numbers
        for leftNumber in leftNumbers:
            # Check if leftNumber is key in dictionary
            if rightNumbers.get(leftNumber, False):
                numMatches += 1

        # Increment range of matches values by number of current card coppies
        for i in range(cardNumber, cardNumber+numMatches):
            numCards[i] += numCards[cardNumber-1]
        # Increment score with corresponding numCards value
        score += numCards[cardNumber-1]
    inputFile.close()
    return score

main()