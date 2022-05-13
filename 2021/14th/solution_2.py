FILE = "input.txt"
STEPS = 40

def polymer_to_dict(polymer):
	ret = {}
	for i, letter in enumerate(polymer):
		try: next_letter = polymer[i+1]
		except IndexError: break

		key = letter + next_letter
		if key in ret:
			ret[key] += 1
		else:
			ret[key] = 1
	
	return ret

def step(polymer_dict: dict):
	new_dict = {}

	for key, value in polymer_dict.items():
		new = table[key]
		first = key[0] + new
		second = new + key[1]

		if first in new_dict:
			new_dict[first] += value
		else:
			new_dict[first] = value
		
		if second in new_dict:
			new_dict[second] += value
		else:
			new_dict[second] = value
	
	return new_dict

def calculate_value(polymer_dict: dict, ends: tuple):
	count = {}
	for key, value in polymer_dict.items():
		for letter in key:
			if letter in count:
				count[letter] += value
			else:
				count[letter] = value
	
	for key in count:
		if key in ends:
			count[key] += 1
		count[key] /= 2
	
	values = count.values()
	return int(max(values) - min(values))

table = {}
with open(FILE, 'r') as input:
	polymer = input.readline().strip()
	ends = (polymer[0], polymer[-1])
	polymer_dict = polymer_to_dict(polymer)

	input.readline()
	for line in input:
		left, right = line.split('->')
		table[left.strip()] = right.strip()

for _ in range(STEPS):
	polymer_dict = step(polymer_dict)

value = calculate_value(polymer_dict, ends)
print(f"Value: {value}")