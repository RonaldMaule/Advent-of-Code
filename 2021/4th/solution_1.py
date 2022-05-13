guesses = []
boards = []

def display_boards():
	for board in boards:
		for row in board:
			print(row)
		print()

def display_board(board):
	for row in board:
		print(row)
	print()

# Reads and stores guesses and boards
with open("input.txt", "r") as input:
	guesses = input.readline().split(",")
	for i, guess in enumerate(guesses):
		guesses[i] = int(guess.strip())

	while line:= input.readline():
		board = []

		for i in range(5):
			line = input.readline()
			row = line.split(" ")

			for num in row:
				if num == "":
					row.remove(num)
			for j, num in enumerate(row):
				row[j] = int(num.strip())
			
			board.append(row)
		
		boards.append(board)

# An unmarked number is type int
# A marked number is type str
def check_board(board, row, i):
	bingo_row = True
	for num in row:
		if isinstance(num, int):
			bingo_row = False
			break

	bingo_col = True
	for row in board:
		if isinstance(row[i], int):
			bingo_col = False
			break
	
	return bingo_row or bingo_col

def find_winner(boards):
	for guess in guesses:
		for board in boards:
			for row in board:
				for i, num in enumerate(row):
					if isinstance(num, int) and num == guess:
						row[i] = str(num)
						if check_board(board, row, i):
							return board, guess

def calculate_score(board, guess):
	sum = 0
	for row in board:
		for num in row:
			if isinstance(num, int):
				sum += num
	
	return sum * guess

board, guess = find_winner(boards)

print(f"Score: {calculate_score(board, guess)}")