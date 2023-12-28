import numpy as np

FILE_PATH = "input/input10.txt"

def main():
	solutionA = solvePuzzle10A()
	print("Solution A:", solutionA)
	solutionB = solvePuzzle10B()
	print("Solution B:", solutionB)

def solvePuzzle10A():
	with open(FILE_PATH, "r", encoding="UTF-8") as inputFile:
		grid = inputFile.readlines()

	# Find start position
	startRow = [grid.index(row) for row in grid if 'S' in row][0]
	startCol = grid[startRow].index('S')

	# Find a tile connected to S
	if startRow > 0 and grid[startRow-1][startCol] in ('|', 'F', '7'):
		currentX, currentY = startCol, startRow-1
	elif startRow < len(grid)-1 and grid[startRow+1][startCol] in ('|', 'J', 'L'):
		currentX, currentY = startCol, startRow+1
	elif startCol > 0 and grid[startRow][startCol-1] in ('-', 'F', 'L'):
		currentX, currentY = startCol-1, startRow
	else:
		currentX, currentY = startCol+1, startRow

	loopLength = 1
	prevX, prevY = startCol, startRow
	while grid[currentY][currentX] != 'S':
		xIncr, yIncr = 0, 0
		# Enter next tile
		match grid[currentY][currentX]:
			case '|':
				yIncr = 1 if currentY > prevY else -1
			case '-':
				xIncr = 1 if currentX > prevX else -1
			case 'L':
				if currentX == prevX:
					xIncr = 1
				else:
					yIncr = -1
			case 'J':
				if currentX == prevX:
					xIncr = -1
				else:
					yIncr = -1
			case '7':
				if currentX == prevX:
					xIncr = -1
				else:
					yIncr = 1
			case 'F':
				if currentX == prevX:
					xIncr = 1
				else:
					yIncr = 1
		# Increment loopLength
		prevX, prevY = currentX, currentY
		currentX += xIncr
		currentY += yIncr
		loopLength += 1

	return loopLength//2

def solvePuzzle10B():
	with open(FILE_PATH, "r", encoding="UTF-8") as inputFile:
		grid = inputFile.readlines()

	# Locate start
	currentY = [grid.index(row) for row in grid if 'S' in row][0]
	currentX = grid[currentY].index('S')

	# Collect every corner in loop
	cornerPointList = []

	prevX, prevY = currentX, currentY
	if currentY > 0 and grid[currentY-1][currentX] in ('|', 'F', '7'):
		if currentX > 0 and grid[currentY][currentX-1] in ('-', 'F', 'L'):
			cornerPointList.append([currentX, currentY])
		elif currentX < len(grid[currentY])-1 and grid[currentY][currentX+1] in ('-', 'J', '7'):
			cornerPointList.append([currentX, currentY])
		currentX, currentY = currentX, currentY-1
	elif currentY < len(grid)-1 and grid[currentY+1][currentX] in ('|', 'J', 'L'):
		if currentX > 0 and grid[currentY][currentX-1] in ('-', 'F', 'L'):
			cornerPointList.append([currentX, currentY])
		elif currentX < len(grid[currentY])-1 and grid[currentY][currentX+1] in ('-', 'J', '7'):
			cornerPointList.append([currentX, currentY])
		currentX, currentY = currentX, currentY+1
	elif currentX > 0 and grid[currentY][currentX-1] in ('-', 'F', 'L'):
		if currentY > 0 and grid[currentY-1][currentX] in ('|', 'F', '7'):
			cornerPointList.append([currentX, currentY])
		elif currentY < len(grid)-1 and grid[currentY+1][currentX] in ('|', 'J', 'L'):
			cornerPointList.append([currentX, currentY])
		currentX, currentY = currentX-1, currentY
	else:
		if currentY > 0 and grid[currentY-1][currentX] in ('|', 'F', '7'):
			cornerPointList.append([currentX, currentY])
		elif currentY < len(grid)-1 and grid[currentY+1][currentX] in ('|', 'J', 'L'):
			cornerPointList.append([currentX, currentY])
		currentX, currentY = currentX+1, currentY

	while grid[currentY][currentX] != 'S':
		if grid[currentY][currentX] in ('F', '7', 'J', 'L'):
			cornerPointList.append([currentX, currentY])
		# Go to next tile
		xIncr, yIncr = 0, 0
		match grid[currentY][currentX]:
			case '|':
				yIncr = 1 if currentY > prevY else -1
			case '-':
				xIncr = 1 if currentX > prevX else -1
			case 'L':
				if currentX == prevX:
					xIncr = 1
				else:
					yIncr = -1
			case 'J':
				if currentX == prevX:
					xIncr = -1
				else:
					yIncr = -1
			case '7':
				if currentX == prevX:
					xIncr = -1
				else:
					yIncr = 1
			case 'F':
				if currentX == prevX:
					xIncr = 1
				else:
					yIncr = 1
		prevX, prevY = currentX, currentY
		currentX += xIncr
		currentY += yIncr

	# Implement shoelace formula
	cornerPointArray = np.array(cornerPointList, dtype=np.int32)

	cornerPointX = np.array(cornerPointArray[:,0])
	cornerPointY = np.array(cornerPointArray[:,1])

	x_y = cornerPointX*np.roll(cornerPointY, -1)
	y_x = cornerPointY*np.roll(cornerPointX, -1)
	area = abs((np.sum(x_y)-np.sum(y_x))//2)

	# Get loop circumference
	boundaryPoints = solvePuzzle10A()*2

	# Implement Pick's theorem
	internalPoints = int(area-boundaryPoints/2+1)

	return internalPoints

if __name__ == "__main__":
	main()