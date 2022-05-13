FILE = "input.txt"

def is_lowpoint(row, col, heatmap):
	point = heatmap[row][col]

	left = (row, col - 1)
	if left[1] < 0:
		left = True
	elif point < heatmap[left[0]][left[1]]:
		left = True
	else:
		left = False

	right = (row, col + 1)
	if right[1] >= len(heatmap[row]):
		right = True
	elif point < heatmap[right[0]][right[1]]:
		right = True
	else:
		right = False

	up = (row - 1, col)
	if up[0] < 0:
		up = True
	elif point < heatmap[up[0]][up[1]]:
		up = True
	else:
		up = False

	down = (row + 1, col)
	if down[0] >= len(heatmap):
		down = True
	elif point < heatmap[down[0]][down[1]]:
		down = True
	else:
		down = False

	return left and right and up and down

def calculate_risk_level(point):
	return 1 + point

heatmap = []

with open(FILE, 'r') as input:
	for line in input:
		heatmap.append([int(x) for x in line.strip()])

lowpoints = []

for i, row in enumerate(heatmap):
	for j, point in enumerate(row):
		if is_lowpoint(i, j, heatmap):
			lowpoints.append(point)

risk_levels = []

for point in lowpoints:
	risk_levels.append(calculate_risk_level(point))

print(f"Risk Sum: {sum(risk_levels)}")