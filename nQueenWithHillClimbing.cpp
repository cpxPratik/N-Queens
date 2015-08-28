#include <iostream>
#include <ctime>
using namespace std;
const int N = 20;
inline void findConflicts(int queenStates[], int addValues[], int subtractValues[], int& conflicts) {
	//int conflicts = 0;
	conflicts = 0;
	static int i;
	static int j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (i == j) continue;
			if (queenStates[i] == queenStates[j])
				conflicts++;
			if (addValues[i] == addValues[j])
				conflicts++;
			if (subtractValues[i] == subtractValues[j])
				conflicts++;
		}
	}
	//return conflicts;
}


int main() {

	srand(time(NULL));
	int currentQueenStates[N], tempQueens[N];
	int currentConflicts, tempConflicts;
	int addValues[N];
	int subtractValues[N];
	int col, row;
	bool generateRandomState = true; // do we have to restart climbing with another randomly generated initial QueenPositions
	unsigned long count = 0;
	int i;
	while (generateRandomState) {
		count++;
		cout << count << "\t";
		for (col = 0; col < N; col++) {
			currentQueenStates[col] = rand() % N;
			addValues[col] = currentQueenStates[col] + col;
			subtractValues[col] = currentQueenStates[col] - col;
		}

		findConflicts(currentQueenStates, addValues, subtractValues, currentConflicts);
		for (i = 0; i < N; i++) {
			tempQueens[i] = currentQueenStates[i];
			addValues[i] = tempQueens[i] + i;
			subtractValues[i] = tempQueens[i] - i;
		}
		while (currentConflicts > 0) {
			bool newState = false;
			for (col = 0; col < N; col++) {
				for (row = 0; row < N; row++) {

					if (currentQueenStates[col] != row) {
						tempQueens[col] = row;
						addValues[col] = tempQueens[col] + col;
						subtractValues[col] = tempQueens[col] - col;
						findConflicts(tempQueens, addValues, subtractValues, tempConflicts);
						if (tempConflicts < currentConflicts) {
							//	for (i = 0; i < N; i++) {
							//	currentQueenStates[i] = tempQueens[i];
							//}
							currentQueenStates[col] = row;
							newState = true;
							break;
						}
						else {
							tempQueens[col] = currentQueenStates[col];
							addValues[col] = tempQueens[col] + col;
							subtractValues[col] = tempQueens[col] - col;
						}
					}
				}
				if (newState)
					break;
			}
			if (!newState) {
				//count++;
				//cout << count << "\t";
				//cout << "Stuck in Local minimum(for cost). Every move of a single queen increases conflicts.\n"
				//	<< "State space with local minimum is given below:" << endl;
				break;
			}
			findConflicts(currentQueenStates, addValues, subtractValues, currentConflicts);
		}
		if (currentConflicts == 0)
			generateRandomState = false;

	}
	
	//char *board[N] = { "----",  "----", "----", "----" };
	int queenPositions[N];
	for (col = 0; col < N; col++) {
		queenPositions[currentQueenStates[col]] = col;
	}
	cout << endl;
	for (row = 0; row < N; row++) {
		for (col = 0; col < queenPositions[row]; col++) {
			cout << "-";
		}
		cout << "+";
		for (col = queenPositions[row]+1; col < N; col++) {
			cout << "-";
		}
		cout << endl;
	}
	
	//cout << rand() % 10 << "  "<< rand() % 10 << endl;
	cout << endl;
	system("pause");
	return 0;
}