FILE = "input1.txt"

class Point:
	def __init__(self, x, y):
		self.x = x
		self.y = y
	
	def __eq__(self, other):
		return self.x == other.x and self.y == other.y
	
	def __hash__(self):
		return hash((self.x, self.y))
	
	def __str__(self):
		return f"{self.x, self.y}"

def flip_up(y):
	global points
	temp = points.copy()
	for point in temp:
		if point.y > y:
			points.add(Point(point.x, point.y - (2 * (point.y - y))))
			points.remove(point)

def flip_left(x):
	global points
	temp = points.copy()
	for point in temp:
		if point.x > x:
			points.add(Point(point.x - (2 * (point.x - x)), point.y))
			points.remove(point)

def print_points(x, y):
	out = []
	for i in range(x+1):
		temp = []
		for j in range(y+1):
			temp.append('.')
		out.append(temp)
	
	for point in points:
		out[point.y][point.x] = "X"
	
	for row in out:
		print(row)

def out():
	with open("output_1.txt", 'w') as f:
		for point in points:
			f.write(f"{point}\n")

points = set()
with open(FILE, 'r') as input:
	for line in input:
		if line == '\n':
			break

		x, y = line.strip().split(',')
		points.add(Point(int(x), int(y)))
	
	for line in input:
		axis, val = line.split(' ')[2].split('=')
		if axis == 'x':
			flip_left(int(val))
		else:
			flip_up(int(val))

print(f"Num points: {len(points)}")