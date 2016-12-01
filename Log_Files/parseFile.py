def readFile(fileName):
	# Open file
	original = open(fileName, 'r')
	newName = fileName[:-4] + "_condensed.txt"
	output = open(newName, 'w')
	serverMsg = "Server sent: "

	# Loop over file
	for line in original:
		if "NEW CHALLENGE" in line:
			output.write(line.replace(serverMsg, ""))
			output.write("\n")
		elif "YOUR OPPONENT" in line:
			output.write(line.replace(serverMsg, ""))
			opponent = line.split()[6]
		elif "BEGIN ROUND" in line:
			output.write(line.replace(serverMsg, ""))
		elif "FORFEITED" in line or "OVER PLAYER" in line:
			output.write(line.replace(serverMsg, ""))
		elif "END OF ROUND " in line and len(line) > 40:
			output.write(line.replace(serverMsg, "")[:-32])
			output.write("\n\n")
		elif "END OF ROUND " in line and len(line) < 40:
			output.write(line.replace(serverMsg, ""))
			output.write('\n')

	original.close()
	output.close()

def countWinsAndLosses(fileName, losses):
	wins = 0
	file = open(fileName, 'r+')

	for line in file:
		if "TEAMJ WIN" in line:
			wins += 1
		elif "TEAMJ WIN" not in line and "TEAMJ FORFEIT" not in line and "R PLAYER TEAMJ" in line:
			ourScore = int(line.split()[5])
			oppScore = int(line.split()[8])
			if ourScore > oppScore:
				wins += 1
			else:
				losses += 1

	file.close()
	
	return wins, losses

def countForfeits(fileName, losses):
	forfeits = 0
	with open(fileName, 'r') as f:
		for line in f:
			if "TEAMJ FORFEITED:" in line:
				forfeits += 1
				losses += 1

	return forfeits, losses

def main():
	# Get file name
	fileName = raw_input("Enter file name: ")
	readFile(fileName)
	newName = fileName[:-4] + "_condensed.txt"
	losses = 0
	wins, lossesUpdated = countWinsAndLosses(newName, losses)
	forfeits, losses = countForfeits(newName, lossesUpdated)

	with open(newName, "a") as f:
		f.write("Number of wins: " + str(wins) + '\n')
		f.write("Number of losses: " + str(losses) + '\n')
		f.write("Number of forfeits: " + str(forfeits) + '\n')

main()