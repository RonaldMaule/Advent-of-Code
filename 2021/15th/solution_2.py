import math
from AdjacencySet import AdjacencySet

FILE_IN = "input.txt"

class Node:
	def __init__(self, row, col, risk):
		self.row = row
		self.col = col
		self.risk = risk
	
	def __hash__(self):
		return hash((self.row, self.col, self.risk))
	
	def __str__(self):
		return f"{self.row}, {self.col}, {self.risk}"
	
	def __eq__(self, other):
		return self.row == other.row and self.col == other.col and self.risk == other.risk
	
	def __lt__(self, other):
		return self.risk < other.risk

class Graph(AdjacencySet):
	def __init__(self, start, end, width, height):
		self.start = start
		self.end = end
		self.width = width
		self.height = height
		super(Graph, self).__init__()
	
	def __contains__(self, other):
		return other in self.V
	
	def print_graph(self):
		for v in self.V:
			print(v)
	
	def reconstruct_path(self, cameFrom, current: list):
		total_path = [current]
		while current in cameFrom.keys():
			current = cameFrom[current]
			total_path.insert(0, current)
		return total_path
	
	def h(self, node):
		x_sqr = (node.col - self.end.col) ** 2
		y_sqr = (node.row - self.end.row) ** 2
		return math.sqrt(x_sqr + y_sqr)
	
	def d(self, node):
		return node.risk

	def get_path(self):
		openSet = {self.start}

		cameFrom = {}

		gScore = {}
		gScore[self.start] = 0

		fScore = {}
		fScore[self.start] = self.h(self.start)

		while openSet:
			current = min(openSet, key=fScore.get)
			if current == self.end:
				return self.reconstruct_path(cameFrom, current)
			print(fScore[current])
			openSet.remove(current)
			for n in self._neighbors(current):
				temp_gScore = gScore[current] + self.d(n)

				gScore.setdefault(n, float('inf'))
				fScore.setdefault(n, float('inf'))

				if temp_gScore < gScore[n]:
					cameFrom[n] = current
					gScore[n] = temp_gScore
					fScore[n] = temp_gScore + self.h(n)
					
					if n not in openSet:
						openSet.add(n)
		
		raise RuntimeError("No path found")

def get_cost(path):
	sum = 0
	for node in path:
		sum += node.risk
	sum -= path[0].risk
	return sum
		
def list_to_graph(cave_list):
	width = len(cave_list[0]) - 1
	height = len(cave_list) - 1
	cavern = Graph(cave_list[0][0], cave_list[height][width], width, height)
	for row, lst in enumerate(cave_list):
		for col, node in enumerate(lst):
			cavern.add_vertex(node)

			if (up := row - 1) >= 0:
				cavern.add_edge((node, cave_list[up][col]))
			
			if (down := row + 1) < len(cave_list):
				cavern.add_edge((node, cave_list[down][col]))
			
			if (left := col - 1) >= 0:
				cavern.add_edge((node, cave_list[row][left]))
			
			if (right := col + 1) < len(cave_list[row]):
				cavern.add_edge((node, cave_list[row][right]))
	
	return cavern

def increment_cave(cave_list, i):
	ret = []
	for row in cave_list:
		temp = []
		for risk in row:
			new = risk + i
			if new > 9: new -= 9
			temp.append(new)
		ret.append(temp)
	
	return ret

with open(FILE_IN, 'r') as input:
	start_cave = []
	for line in input:
		temp = []
		for risk in line.strip():
			temp.append(int(risk))
		
		start_cave.append(temp)

cave_list = []
for i in range(5):
	for j in range(5):
		cave_list.append(increment_cave(start_cave, i+j))

new_cave = []
for i in range(5):
	for j in range(len(start_cave)):
		temp = []
		for k in range(5):
			temp.extend(cave_list[i*5+k][j])
		new_cave.append(temp)

for row, lst in enumerate(new_cave):
	for col, risk in enumerate(lst):
		new_cave[row][col] = Node(row, col, risk)

cavern = list_to_graph(new_cave)
path = cavern.get_path()
cost = get_cost(path)

print(f"Cost: {cost}")