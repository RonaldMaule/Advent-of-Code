depth = 0
position = 0

with open("input.txt", "r") as input:
	for line in input:
		command, distance = line.split(" ")

		distance = int(distance)

		match command:
			case "forward":
				position += distance
			case "down":
				depth += distance
			case "up":
				depth -= distance
		
print(f"Answer: {depth * position}")