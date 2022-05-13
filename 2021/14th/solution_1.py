FILE = "test.txt"
STEPS = 10

def step(polymer):
	temp = polymer

	for i, current in enumerate(polymer):
		try: next = polymer[i+1]
		except IndexError: break
		
		key = current + next
		value = table[key]
		temp = temp[:2*i+1] + value + temp[2*i+1:]

	return temp

def calculate_value(polymer):
	count = {}
	for letter in polymer:
		if letter in count:
			count[letter] += 1
		else:
			count[letter] = 1
	
	values = count.values()
	return max(values) - min(values)

table = {}
with open(FILE, 'r') as input:
	polymer = input.readline().strip()
	input.readline()

	for line in input:
		left, right = line.split('->')
		table[left.strip()] = right.strip()

for _ in range(STEPS):
	polymer = step(polymer)

value = calculate_value(polymer)
print(f"Value: {value}")