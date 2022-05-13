FILE = "input.txt"

def find_cost_position(x, positions):
	cost = 0

	for pos in positions:
		n = 1 + abs(pos - x)
		cost += n * (n - 1) / 2
	
	return cost

with open(FILE, 'r') as input:
	positions = [int(n) for n in input.read().strip().split(",")]

small = min(positions)
large = max(positions)

fuel_costs = []
for position in range(small, large+1):
	fuel_costs.append(find_cost_position(position, positions))

print(f"Minumum: {min(fuel_costs)}")