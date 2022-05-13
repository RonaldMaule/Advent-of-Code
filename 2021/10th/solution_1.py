FILE = "input.txt"
SCORES = {
	")": 3,
	"]": 57,
	"}": 1197,
	">": 25137
}
OPEN = ("(", "[", "{", "<")
CLOSED = (")", "]", "}", ">")

def is_match(left, right):
	match left:
		case "(":
			return right == ")"
		case "[":
			return right == "]"
		case "{":
			return right == "}"
		case "<":
			return right == ">"
		case _:
			raise ValueError(f"Incorrect left character entered: {left}")

def get_corrupted(line):
	chars = []

	for char in line:
		if char in OPEN:
			chars.append(char)
		elif char in CLOSED:
			if is_match(chars[-1], char):
				chars.pop()
			else:
				return char
	
	return ""

incorrect = []
with open(FILE, 'r') as input:
	for line in input:
		if (char := get_corrupted(line)):
			incorrect.append(char)

score = 0
for char in incorrect:
	score += SCORES[char]

print(f"Score: {score}")