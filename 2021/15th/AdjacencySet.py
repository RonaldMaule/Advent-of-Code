class AdjacencySet:
	def __init__(self):
		self.V = set()
		self.nbrs = dict()

	def add_vertex(self, v):
		self.V.add(v)
	def remove_vertex(self, v):
		self.V.remove(v)

	def add_edge(self, e):
		a, b = e # e = (x, y)
		if a not in self.nbrs:
			self.nbrs[a] = {b}
		else:
			self.nbrs[a].add(b)

	def remove_edge(self, e):
		a, b = e
		self.nbrs[a].remove[b]
		if len(self.nbrs[a]) == 0: self.nbrs.pop(a)

	def __iter__(self):
		return iter(self.V)

	def _neighbors(self, v):
		return iter(self.nbrs[v])

class Graph(AdjacencySet):
	pass

if __name__ == '__main__':
    # Store the following graph:
    # 1--4
    # |\ |
    # | \|
    # 2--3

    g = Graph()
    vs = {1, 3, 2, 4}
    es = {(1,2), (1,3), (1,4),
          (2,1), (2,3),
          (3,1), (3,2), (3,4),
          (4,1), (4,3)}

    for v in vs: g.add_vertex(v)
    for e in es: g.add_edge(e)

    for v in g:
        print("v = {}, neighbors:".format(v))
        for nbr in g._neighbors(v):
            print("\t{}".format(nbr))
        print()
