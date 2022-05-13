line_1 = None
line_2 = None
line_3 = None

tally = 0

with open("input.txt", "r") as input:
	line_1 = int(input.readline())
	line_2 = int(input.readline())
	line_3 = int(input.readline())

	for line in input:
		current_line = int(line)

		if line_2 + line_3 + current_line > line_1 + line_2 + line_3:
			tally += 1

		line_1 = line_2
		line_2 = line_3
		line_3 = current_line

print(f"Tally: {tally}")