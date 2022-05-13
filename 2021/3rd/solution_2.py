NUMBER_LENGTH = 12
FILE = "input.txt"

oxygen = []
co2 = []

with open(FILE, "r") as input:
	tally = []
	for i in range(NUMBER_LENGTH):
		input.seek(0)
		tally.append(0)

		for line in input:
			Match = True
			for j in range(len(oxygen)):
				if int(line[j]) != oxygen[j]:
					Match = False
					break
			
			if Match is False: continue

			match line[i]:
				case "0":
					tally[i] -= 1
				case "1":
					tally[i] += 1
		
		if tally[i] >= 0:
			oxygen.append(1)
		else:
			oxygen.append(0)

with open(FILE, "r") as input:
	tally = []
	for i in range(NUMBER_LENGTH):
		input.seek(0)
		tally.append(0)
		matching_numbers = 0

		for line in input:
			Match = True
			for j in range(len(co2)):
				if int(line[j]) != co2[j]:
					Match = False
					break
			
			if Match is False: continue

			matching_numbers += 1

			match line[i]:
				case "0":
					tally[i] -= 1
				case "1":
					tally[i] += 1
		if matching_numbers == 1:
			if tally[i] == 1:
				co2.append(1)
			else:
				co2.append(0)
		else:
			if tally[i] >= 0:
				co2.append(0)
			elif tally[i] < 0:
				co2.append(1)

oxygen = int("".join(str(i) for i in oxygen), 2)
co2 = int("".join(str(i) for i in co2), 2)

print(f"Life Support Rating: {oxygen * co2}")