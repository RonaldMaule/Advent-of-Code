FILE = "mine.txt"
NUM_DAYS = 80

class LanternFish:
	def __init__(self, state=8):
		self.state = state
	
	def next_day(self):
		self.state -= 1
		if self.state == -1:
			self.state = 6
			return True
		else:
			return False

class School:
	def __init__(self, initial_state):
		self.school = []

		for state in initial_state:
			self.school.append(LanternFish(state))
		
	def simulate(self, num_days):
		for _ in range(num_days):
			new_fish = []

			for fish in self.school:
				if fish.next_day():
					new_fish.append(LanternFish())
			
			self.school.extend(new_fish)
			
		return len(self.school)
	
	def print_school(self):
		temp_school = []
		for fish in self.school:
			temp_school.append(fish.state)
		
		print(temp_school)

with open(FILE, "r") as input:
	initial = input.readline().split(',')
	for i, entry in enumerate(initial):
		initial[i] = int(entry)

lantern_school = School(initial)
print(f"Num Fish: {lantern_school.simulate(NUM_DAYS)}")