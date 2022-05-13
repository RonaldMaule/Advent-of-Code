from AdjacencySet import AdjacencySet

FILE = 'input.txt'

class Graph(AdjacencySet):
	def dfs_iter(self, v):
		#tree = {} # child:parent
		to_visit = [(None, v, {})] # parent:child
		paths = 0

		while to_visit:
			a, b, c = to_visit.pop()

			if b == "end":
				paths += 1
				continue

			if b not in c:
				if b.islower():
					c[b] = a
				for n in self._neighbors(b):
					if n not in c:
						to_visit.append((b, n, c.copy()))
		return paths

g = Graph()
with open(FILE, 'r') as input:
	for line in input:
		left, right = line.strip().split('-')

		g.add_vertex(left)
		g.add_vertex(right)

		if left == "start":
			g.add_edge((left, right))
		elif right == "start":
			g.add_edge((right, left))
		elif left == "end":
			g.add_edge((right, left))
		elif right == "end":
			g.add_edge((left, right))
		else:
			g.add_edge((left, right))
			g.add_edge((right, left))

paths = g.dfs_iter("start")
print(f"Paths: {paths}")