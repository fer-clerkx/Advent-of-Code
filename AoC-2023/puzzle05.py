import re
from collections import namedtuple

FILE_PATH = "input05.txt"

def main():
    solutionA = solvePuzzle05A()
    print("Solution A:", solutionA)
    solutionB = solvePuzzle05B()
    print("Solution B:", solutionB)

def solvePuzzle05A():
    # Read input file
    inputFile = open(FILE_PATH, "r", encoding="UTF-8")
    inputLines = inputFile.readlines()
    inputFile.close()

    # Parse numbers from seeds
    numbers = list(map(int, re.findall("\d+", inputLines[0])))

    # Filter out map section headers
    inputMapsString = []
    for line in inputLines[1:]:
        if re.findall("^\d+[\d\s]+$", line):
            inputMapsString[-1].append(line)
        elif re.findall("map:", line):
            inputMapsString.append([])

    # Parse numbers from maps
    inputMaps = []
    mapTuple = namedtuple('mapTuple', 'destination source range')
    for inputMapStrings in inputMapsString:
        inputMaps.append([])
        for inputMapString in inputMapStrings:
            # Parse numbers into tuple and append to map
            inputMapList = map(int, re.findall("\d+", inputMapString))
            inputMaps[-1].append(mapTuple._make(inputMapList))

    # Iterate through numbers
    for i in range(len(numbers)):
        # Iterate through maps
        for inputMap in inputMaps:
            for mapLine in inputMap:
                # If number is in source range
                if numbers[i] >= mapLine.source and numbers[i] < mapLine.source+mapLine.range:
                    # Update number
                    numbers[i] = numbers[i]-mapLine.source+mapLine.destination
                    # Each number only mapped once
                    break
    # Return smallest number
    return min(numbers)

def solvePuzzle05B():
    # Read input file
    inputFile = open(FILE_PATH, "r", encoding="UTF-8")
    inputLines = inputFile.readlines()
    inputFile.close()

    # Parse number ranges from seeds
    numberRanges = []
    numberRangesRaw = list(map(int, re.findall("\d+", inputLines[0])))
    for i in range(0, len(numberRangesRaw), 2):
        numberRanges.append(range(numberRangesRaw[i], numberRangesRaw[i]+numberRangesRaw[i+1]))

    # Filter out map section headers
    inputMapsString = []
    for line in inputLines[1:]:
        if re.findall("^\d+[\d\s]+$", line):
            inputMapsString[-1].append(line)
        elif re.findall("map:", line):
            inputMapsString.append([])

    # Parse numbers from maps
    inputMaps = []
    mapTuple = namedtuple('mapTuple', 'destination source range')
    for inputMapStrings in inputMapsString:
        inputMaps.append([])
        for inputMapString in inputMapStrings:
            # Parse numbers into tuple and append to map
            inputMapList = map(int, re.findall("\d+", inputMapString))
            inputMaps[-1].append(mapTuple._make(inputMapList))

    # Sort maps by source
    def mapSorting(e):
        return e.source
    for i in range(len(inputMaps)):
        inputMaps[i].sort(key=mapSorting)

    # Convert maps to ranges
    mapRanges = []
    rangeTuple = namedtuple('rangeTuple', 'source destination')
    for inputMap in inputMaps:
        mapRanges.append([])
        if inputMap[0].source > 0:
            sourceMapRange = range(0, inputMap[0].source)
            mapRanges[-1].append(rangeTuple._make([sourceMapRange, sourceMapRange]))
        for mapLine in inputMap:
            # if mapRanges[-1][-1][-1]+1 < mapLine.source:
            # 	mapRanges[-1].append(range(mapRanges[-1][-1][1], mapLine.source))
            sourceMapRange = range(mapLine.source, mapLine.source+mapLine.range)
            destinationMapRange = range(mapLine.destination, mapLine.destination+mapLine.range)
            mapRanges[-1].append(rangeTuple._make([sourceMapRange, destinationMapRange]))

    # Iterate through mapRanges
    for mapRange in mapRanges:
        # Iterate through number ranges
        newNumberRange = []
        for numberRange in numberRanges:
            # Iterate through single map ranges
            for mapLine in mapRange:
                # numberRange and mapLine overlap?
                if numberRange.start < mapLine.source.stop and numberRange.stop > mapLine.source.start:
                    numberSubRange = range(max(numberRange.start, mapLine.source.start), min(numberRange.stop, mapLine.source.stop))
                    numberDestinationStart = mapLine.destination[numberSubRange.start-mapLine.source.start]
                    numberDestinationStop = mapLine.destination[numberSubRange.stop-mapLine.source.start-1]+1
                    newNumberRange.append(range(numberDestinationStart, numberDestinationStop))
            if numberRange.stop > mapRange[-1].source.stop:
                numberSubRange = range(max(numberRange.start, mapRange[-1].source.stop), numberRange.stop)
                newNumberRange.append(numberSubRange)
        numberRanges = newNumberRange

    # Return smallest number
    return min(numberRanges, key=lambda x: x.start).start

main()