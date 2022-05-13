previous_line = None
tally = 0

with open("input.txt", "r") as input:
	previous_line = int(input.readline())

	for line in input:
		line = int(line)
		
		if line > previous_line:
			tally += 1

		previous_line = line

print(f"Tally: {tally}")