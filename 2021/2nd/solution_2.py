depth = 0
position = 0
aim = 0

with open("input.txt", "r") as input:
	for line in input:
		command, distance = line.split(" ")

		distance = int(distance)

		match command:
			case "forward":
				position += distance
				depth += distance * aim
			case "down":
				aim += distance
			case "up":
				aim -= distance
		
print(f"Answer: {depth * position}")