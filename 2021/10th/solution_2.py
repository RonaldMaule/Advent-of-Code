FILE = "input.txt"
SCORES = {
	")": 1,
	"]": 2,
	"}": 3,
	">": 4
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

def get_sequence(line):
	chars = []

	for char in line:
		if char in OPEN:
			chars.append(char)
		elif char in CLOSED:
			if is_match(chars[-1], char):
				chars.pop()
			else:
				return ""
	
	return chars

def get_right_sequence(sequence):
	right = []

	for char in sequence:
		match char:
			case "(":
				right.append(")")
			case "[":
				right.append("]")
			case "{":
				right.append("}")
			case "<":
				right.append(">")
			case _:
				raise ValueError(f"Invalid char in sequnece {char}")
	
	right.reverse()
	return right

def get_score(sequence):
	score = 0

	for char in sequence:
		score = 5 * score + SCORES[char]
	
	return score

incomplete = []
with open(FILE, 'r') as input:
	for line in input:
		if (chars := get_sequence(line)):
			incomplete.append(chars)

right_sequences = []
for sequence in incomplete:
	right_sequences.append(get_right_sequence(sequence))

scores = []
for sequence in right_sequences:
	scores.append(get_score(sequence))

scores.sort()
score = scores[len(scores) // 2]

print(f"Score: {score}")