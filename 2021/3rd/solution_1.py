NUMBER_LENGTH = 12

gamma = []
epsilon = []
tally = []

for i in range(NUMBER_LENGTH):
	gamma.append(0)
	epsilon.append(0)
	tally.append(0)

with open("input.txt", "r") as input:
	for line in input:
		for i in range(NUMBER_LENGTH):
			match line[i]:
				case "0":
					tally[i] -= 1
				case "1":
					tally[i] += 1

for i in range(NUMBER_LENGTH):
	if tally[i] > 0:
		gamma[i] = 1
		epsilon[i] = 0
	elif tally[i] < 0:
		gamma[i] = 0
		epsilon[i] = 1
	else:
		raise ValueError("Equal number of ones and zeroes")

gamma = int("".join(str(i) for i in gamma), 2)
epsilon = int("".join(str(i) for i in epsilon), 2)

print(f"Power Consumption: {gamma * epsilon}")