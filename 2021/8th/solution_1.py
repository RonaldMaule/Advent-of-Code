FILE = "input.txt"

class Trial:
	def __init__(self, numbers, output):
		self.numbers = numbers
		self.output = output
	
	def __str__(self):
		return f"{self.numbers}, {self.output}"

	def count_easy(self):
		count = 0
		
		for num in self.output:
			n = len(num)
			if n == 2 or n == 3 or n == 4 or n == 7:
				count += 1
		
		return count

trials = []

with open(FILE, 'r') as input:
	for line in input:
		temp = [x.strip() for x in line.strip().split('|')]
		temp = [x.split(" ") for x in temp]
		trials.append(Trial(temp[0], temp[1]))

count = 0

for trial in trials:
	count += trial.count_easy()

print(f"Count: {count}")