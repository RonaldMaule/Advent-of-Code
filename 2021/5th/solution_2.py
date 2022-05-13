FILE = "input.txt"
GRID_WIDTH = 1000

class Point:
	def __init__(self, x, y):
		self.x = x
		self.y = y
		self.count = 1
	
	def __eq__(self, other):
		return self.x == other.x and self.y == other.y
	
	def __lt__(self, other):
		return self.y < other.y

class Grid:
	def __init__(self):
		self.grid = []
		self.dangerous = 0
		self.setup()
	
	def setup(self):
		for _ in range(GRID_WIDTH):
			self.grid.append([])
	
	def print_grid(self):
		for i in range(len(self.grid)):
			for j in range(len(self.grid[i])):
				print(i, self.grid[i][j].y)

def point_to_list(point):
	lst = point.strip().split(",")
	lst[0] = int(lst[0])
	lst[1] = int(lst[1])
	return lst

def is_diagonal(left, right):
	return left[0] != right[0] and left[1] != right[1]

def is_horizontal(left, right):
	return left[1] == right[1]

def create_horizontal(lower, upper, y):
	global points

	for i in range(lower, upper+1):
		point = Point(i, y)

		exists = False
		for j, entry in enumerate(points.grid[i]):
			if point < entry:
				points.grid[i].insert(j, point)
				exists = True
				break
			elif entry == point:
				points.grid[i][j].count += 1
				exists = True
				if points.grid[i][j].count == 2:
					points.dangerous += 1
				break

		if not exists:
			points.grid[i].append(point)

def create_vertical(lower, upper, x):
	global points

	index = 0
	found = False
	for i, entry in enumerate(points.grid[x]):
		if lower <= entry.y:
			index = i
			found = True
			break
	
	if found:
		for i in range(lower, upper+1):
			point = Point(x, i)
			try:
				if point == points.grid[x][index]:
					points.grid[x][index].count += 1
					if points.grid[x][index].count == 2:
						points.dangerous += 1
				else:
					points.grid[x].insert(index, point)
			except IndexError:
				points.grid[x].append(point)
			index += 1

	else:
		for i in range(lower, upper+1):
			points.grid[x].append(Point(x, i))

def find_smaller_x(left, right):
	if left[0] < right[0]:
		return left, right
	else:
		return right, left

def create_diagonal_down(smaller, larger):
	global points

	y = smaller[1]
	for i in range(smaller[0], larger[0]+1):
		point = Point(i, y)

		exists = False
		for j, entry in enumerate(points.grid[i]):
			if point < entry:
				points.grid[i].insert(j, point)
				exists = True
				break
			elif entry == point:
				points.grid[i][j].count += 1
				exists = True
				if points.grid[i][j].count == 2:
					points.dangerous += 1
				break

		if not exists:
			points.grid[i].append(point)

		y += 1

def create_diagonal_up(smaller, larger):
	global points

	y = smaller[1]
	for i in range(smaller[0], larger[0]+1):
		point = Point(i, y)

		exists = False
		for j, entry in enumerate(points.grid[i]):
			if point < entry:
				points.grid[i].insert(j, point)
				exists = True
				break
			elif entry == point:
				points.grid[i][j].count += 1
				exists = True
				if points.grid[i][j].count == 2:
					points.dangerous += 1
				break

		if not exists:
			points.grid[i].append(point)

		y -= 1

points = Grid()

with open(FILE, "r") as input:
	for line in input:
		point = line.split("->")
		left = point_to_list(point[0])
		right = point_to_list(point[1])
		
		if is_diagonal(left, right):
			smaller, larger = find_smaller_x(left, right)
			if smaller[1] < larger[1]:
				create_diagonal_down(smaller, larger)
			else:
				create_diagonal_up(smaller, larger)
		elif is_horizontal(left, right):
			if left[0] < right[0]:
				create_horizontal(left[0], right[0], left[1])
			else:
				create_horizontal(right[0], left[0], left[1])
		else:
			if left[1] < right[1]:
				create_vertical(left[1], right[1], left[0])
			else:
				create_vertical(right[1], left[1], left[0])

print(f"Number of points: {points.dangerous}")