from collections import defaultdict

FILE = "input.txt"
NUM_DAYS = 256

class School:
	def __init__(self, initial_state, print=False):
		self.school = defaultdict(int)
		self.print = print

		for state in initial_state:
			if state not in self.school:
				self.school[state] = 0
			self.school[state] += 1
		
	def simulate(self):
		for _ in range(NUM_DAYS):
			new_school = defaultdict(int)
			for state, count in self.school.items():
				if state == 0:
					new_school[6] += count
					new_school[8] += count
				else:
					new_school[state-1] += count
			self.school = new_school
			
		return sum(self.school.values())

	def print_school(self):
		for state, count in self.school.items():
			print(state, count)

with open(FILE, "r") as input:
	initial = input.readline().split(',')
	for i, entry in enumerate(initial):
		initial[i] = int(entry)

lantern_school = School(initial, False)
print(f"Num Fish: {lantern_school.simulate()}")