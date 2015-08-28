#include <iostream>
#include <ctime>
using namespace std;
const int N = 4;
inline int findConflicts(int queenStates[], int addValues[], int subtractValues[]) {
	int conflicts = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			if (queenStates[i] == queenStates[j])
				conflicts++;
			if (addValues[i] == addValues[j])
				conflicts++;
			if (subtractValues[i] == subtractValues[j])
				conflicts++;
		}
	}
	return conflicts;
}


int main() {
	
	srand(time(NULL));
	int currentQueenStates[N], tempQueens[N];
	int currentConflicts, tempConflicts;
	int addValues[N];
	int subtractValues[N];
	int col, row;
	
	for (col = 0; col < N; col++) {
		currentQueenStates[col] = rand() % N;
		addValues[col] = currentQueenStates[col] + col;
		subtractValues[col] = currentQueenStates[col] - col;
	}
	
	currentConflicts = findConflicts(currentQueenStates, addValues, subtractValues);
	unsigned long count = 0;
	while (currentConflicts > 0) {
		bool newState = false;
		for (col = 0; col < N; col++) {
			for (row = 0; row < N; row++) {
				for (int i = 0; i < N; i++) {
					tempQueens[i] = currentQueenStates[i];
					addValues[i] = tempQueens[i] + i;
					subtractValues[i] = tempQueens[i] - i;
				}
				if (currentQueenStates[col] != row) {
					tempQueens[col] = row;
					addValues[col] = tempQueens[col] + col;
					subtractValues[col] = tempQueens[col] - col;
				}
				tempConflicts = findConflicts(tempQueens, addValues, subtractValues);
				if (tempConflicts < currentConflicts) {
					for (int i = 0; i < N; i++) {
						currentQueenStates[i] = tempQueens[i];
					}
					newState = true;
					break;
				}
			}
			if (newState)
				break;
		}
		if (!newState) {
			//count++;
			cout << "Stuck in Local minimum(for cost). Every move of a single queen increases conflicts.\n"
				<<"State space with local minimum is given below:"<<endl;
			break;
		}
		currentConflicts = findConflicts(currentQueenStates, addValues, subtractValues);
	}
	//char *board[N] = { "----",  "----", "----", "----" };
	int queenPositions[N];
	for (col = 0; col < N; col++) {
		queenPositions[currentQueenStates[col]] = col;
	}

	for (row = 0; row < N; row++) {
		for (col = 0; col < queenPositions[row]; col++) {
			cout << "-";
		}
		cout << "Q";
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