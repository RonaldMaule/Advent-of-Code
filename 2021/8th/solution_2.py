FILE = "input.txt"

class Trial:
	def __init__(self, input, output):
		self.input = input
		self.output = output
		self.numbers = [None for _ in range(10)]
		self.mapping = dict()
		self.number = None

	def __add__(self, other):
		return self.number + other.number
	
	def __radd__(self, other):
		return self.number + other
	
	def __str__(self):
		return f"{self.input} | {self.output}"
	
	def find_mappings(self):
		self.find_easy()

		self.find_a_c_f()

		fives, sixes = self.find_hard()

		self.find_2_3_5(fives)

		self.find_e()

		self.find_0_6_9(sixes)

		self.get_num()
	
	def find_easy(self):
		for num in self.input:
			n = len(num)
			if not(n == 2 or n == 3 or n == 4 or n == 7):
				continue

			temp = set()

			for digit in num:
				temp.add(digit)
			
			match n:
				case 2:
					self.numbers[1] = temp
				case 3:
					self.numbers[7] = temp
				case 4:
					self.numbers[4] = temp
				case 7:
					self.numbers[8] = temp
	
	def find_a_c_f(self):
		nums = self.numbers

		self.mapping[nums[1].symmetric_difference(nums[7]).pop()] = 'a'

		for digit in nums[1]:
			count = 0
			for num in self.input:
				if digit in num:
					count += 1
			
			if count == 8:
				self.mapping[digit] = 'c'
			elif count == 9:
				self.mapping[digit] = 'f'
	
	def find_hard(self):
		fives = []
		sixes = []

		for num in self.input:
			if len(num) == 5:
				fives.append(num)
			elif len(num) == 6:
				sixes.append(num)
		
		return fives, sixes

	def find_2_3_5(self, fives):
		for num in fives:
			if self.translate('c') not in num:
				self.numbers[5] = set(num)
			elif self.translate('f') not in num:
				self.numbers[2] = set(num)
			elif self.translate('c') in num and self.translate('f') in num:
				self.numbers[3] = set(num)
			else:
				raise Exception(f"{num} was not found in fives")
	
	def find_e(self):
		num_2 = self.numbers[2]
		num_3 = self.numbers[3]

		diff = num_2.symmetric_difference(num_3)

		for num in diff:
			if num != self.translate('f'):
				self.mapping[num] = 'e'
				return
		
		raise Exception("e not found")
	
	def find_0_6_9(self, sixes):
		for num in sixes:
			if self.translate('c') not in num:
				self.numbers[6] = set(num)
			elif self.translate('e') not in num:
				self.numbers[9] = set(num)
			elif self.translate('c') in num and self.translate('e') in num:
				self.numbers[0] = set(num)
			else:
				raise Exception(f"{num} not found in sixes")
	
	def get_num(self):
		output = []
		for num in self.output:
			output.append(self.numbers.index(set(num)))
		
		output = [str(num) for num in output]
		self.number = int("".join(output))
	
	def translate(self, letter):
		for key, value in self.mapping.items():
			if value == letter:
				return key
		
		raise ValueError(f"Value not found in mapping for trial: {self}")

trials = []

with open(FILE, 'r') as input:
	for line in input:
		temp = [x.strip() for x in line.strip().split('|')]
		temp = [x.split(" ") for x in temp]
		trials.append(Trial(temp[0], temp[1]))

for trial in trials:
	trial.find_mappings()

print(f"Count: {sum(trials)}")
