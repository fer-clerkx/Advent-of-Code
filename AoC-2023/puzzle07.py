import re
from enum import Enum
from collections import Counter

FILE_PATH = "input/input07.txt"

class Types(Enum):
    HIGH = 0
    ONE = 1
    TWO = 2
    THREE = 3
    HOUSE = 4
    FOUR = 5
    FIVE = 6

LABELS_A = {
    '2': 2,
    '3': 3,
    '4': 4,
    '5': 5,
    '6': 6,
    '7': 7,
    '8': 8,
    '9': 9,
    'T': 10,
    'J': 11,
    'Q': 12,
    'K': 13,
    'A': 14
}

LABELS_B = {
    'J': 1,
    '2': 2,
    '3': 3,
    '4': 4,
    '5': 5,
    '6': 6,
    '7': 7,
    '8': 8,
    '9': 9,
    'T': 10,
    'Q': 12,
    'K': 13,
    'A': 14
}

def main():
    solutionA = solvePuzzle07A()
    print("Solution A:", solutionA)
    solutionB = solvePuzzle07B()
    print("Solution B:", solutionB)

def solvePuzzle07A():
    with open(FILE_PATH, "r", encoding="UTF-8") as inputFile:
        inputStrings = inputFile.readlines()

    hands = []
    bids = []
    for inputString in inputStrings:
        hands.append(re.split(" ", inputString)[0])
        bids.append(int(re.split(" ", inputString)[1]))

    types = []
    for hand in hands:
        cards = Counter(hand)
        numCards = sorted(cards.values(), reverse=True)
        if numCards[0] == 5:
            types.append(Types.FIVE)
        elif numCards[0] == 4:
            types.append(Types.FOUR)
        elif numCards[0:2] == [3, 2]:
            types.append(Types.HOUSE)
        elif numCards[0] == 3:
            types.append(Types.THREE)
        elif numCards[0:2] == [2, 2]:
            types.append(Types.TWO)
        elif numCards[0] == 2:
            types.append(Types.ONE)
        else:
            types.append(Types.HIGH)

    sortedList = list(zip(types, hands, bids))
    sortedList.sort(key=lambda x: (x[0].value, [LABELS_A[i] for i in x[1]]))

    sum = 0
    for i, hand in enumerate(sortedList):
        sum += (i+1)*hand[2]

    return sum

def solvePuzzle07B():
    with open(FILE_PATH, "r", encoding="UTF-8") as inputFile:
        inputStrings = inputFile.readlines()

    hands = []
    bids = []
    for inputString in inputStrings:
        hands.append(re.split(" ", inputString)[0])
        bids.append(int(re.split(" ", inputString)[1]))

    types = []
    for hand in hands:
        numJokers = 0
        cards = Counter()
        for card in hand:
            if card == 'J':
                numJokers += 1
            else:
                cards.update(card)
        numCards = sorted(cards.values(), reverse=True)
        if numJokers == 5 or numCards[0] == 5:
            types.append(Types.FIVE)
        elif numCards[0] == 4:
            types.append(Types.FOUR)
        elif numCards[0:2] == [3, 2]:
            types.append(Types.HOUSE)
        elif numCards[0] == 3:
            types.append(Types.THREE)
        elif numCards[0:2] == [2, 2]:
            types.append(Types.TWO)
        elif numCards[0] == 2:
            types.append(Types.ONE)
        else:
            types.append(Types.HIGH)

        match types[-1]:
            case Types.FOUR:
                if numJokers == 1:
                    types[-1] = Types.FIVE
            case Types.THREE:
                if numJokers == 2:
                    types[-1] = Types.FIVE
                elif numJokers == 1:
                    types[-1] = Types.FOUR
            case Types.TWO:
                if numJokers == 1:
                    types[-1] = Types.HOUSE
            case Types.ONE:
                if numJokers == 3:
                    types[-1] = Types.FIVE
                elif numJokers == 2:
                    types[-1] = Types.FOUR
                elif numJokers == 1:
                    types[-1] = Types.THREE
            case Types.HIGH:
                if numJokers == 4:
                    types[-1] = Types.FIVE
                elif numJokers == 3:
                    types[-1] = Types.FOUR
                elif numJokers == 2:
                    types[-1] = Types.THREE
                elif numJokers == 1:
                    types[-1] = Types.ONE

    sortedList = list(zip(types, hands, bids))
    sortedList.sort(key=lambda x: (x[0].value, [LABELS_B[i] for i in x[1]]))

    sum = 0
    for i, hand in enumerate(sortedList):
        sum += (i+1)*hand[2]

    return sum

main()