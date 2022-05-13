FILE = "input.txt"

def is_found(row, col, found):
	return (row, col) in found

def get_neighbors(point, basin):
	row, col = point
	neighbors = set()

	left = (row, col - 1)
	if left[1] < 0:
		pass
	elif heatmap[left[0]][left[1]] < 9 and left not in basin:
		neighbors.add(left)
	
	right = (row, col + 1)
	if right[1] >= len(heatmap[row]):
		pass
	elif heatmap[right[0]][right[1]] < 9 and right not in basin:
		neighbors.add(right)
	
	up = (row - 1, col)
	if up[0] < 0:
		pass
	elif heatmap[up[0]][up[1]] < 9 and up not in basin:
		neighbors.add(up)
	
	down = (row + 1, col)
	if down[0] >= len(heatmap):
		pass
	elif heatmap[down[0]][down[1]] < 9 and down not in basin:
		neighbors.add(down)
	
	return neighbors

def calculate_basin(i, j):
	global found
	basin = set()
	
	search = [(i,j)]
	while search:
		temp = []
		found.update(search)
		basin.update(search)

		for point in search:
			temp.extend(get_neighbors(point, basin))
		
		search = temp
	
	return len(basin)

heatmap = []
with open(FILE, 'r') as input:
	for line in input:
		heatmap.append([int(x) for x in line.strip()])

basins = []
found = set()
for i, row in enumerate(heatmap):
	for j, point in enumerate(row):
		if (not is_found(i, j, found)) and point != 9:
			basins.append(calculate_basin(i, j))

basins.sort(reverse=True)
answer = basins[0] * basins[1] * basins[2]

print(f"Answer: {answer}")