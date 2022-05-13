FILE = "input.txt"
NUM_STEPS = 100

def print_cavern(cavern):
	for row in cavern:
		print(row)
	print()

cavern = []
with open(FILE, 'r') as input:
	for line in input:
		temp = [int(oct) for oct in line.strip()]
		cavern.append(temp)

def flash(i, j, cavern):
	temp = cavern
	for row in range(i-1, i+2):
		for col in range(j-1, j+2):
			if row == i and col == j:
				temp[i][j] = 0
				continue

			if row < 0 or row >= len(cavern) or col < 0 or col >= len(cavern[row]):
				continue
				
			if temp[row][col] == 0:
				continue

			temp[row][col] += 1
	
	return temp

flashes = 0
for _ in range(NUM_STEPS):
	for i, row in enumerate(cavern):
		for j in range(len(row)):
			cavern[i][j] += 1
	
	not_done = True
	while not_done:
		not_done = False
		for i, row in enumerate(cavern):
			for j, oct in enumerate(row):
				if oct > 9:
					not_done = True
					flashes += 1

					cavern = flash(i, j, cavern)

print(f"Flashes: {flashes}")