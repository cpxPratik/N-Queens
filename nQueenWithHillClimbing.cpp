#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

inline void findConflicts(int queenStates[], int addValues[], int subtractValues[], int& conflicts, int& noOfQueens) {
	//int conflicts = 0;
	conflicts = 0;
	static int i;
	static int j;
	for (i = 0; i < noOfQueens; i++) {
		for (j = 0; j < noOfQueens; j++) {
			if (i == j) continue;
			if (queenStates[i] == queenStates[j])
				conflicts++; // if same row
			if (addValues[i] == addValues[j])
				conflicts++; // if in same diagonal from left-bottom to right-top and vice-versa
			if (subtractValues[i] == subtractValues[j])
				conflicts++; // if in same diagonal from left-top to right-bottom and vice-versa
		}
	}
	//return conflicts;
}

int main() {
	int col, row;
	srand(time(NULL)); //seeds random-number generator rand() with system time
	bool generateRandomState = true; // do we have to restart climbing with another randomly generated initial QueenPositions
	unsigned long count = 0;
	int i;
	int currentConflicts, tempConflicts;
	int N = 0;
	bool newState = false;

	do {
		cout << "Enter No. of queen(n) for solution of n-queen problem: ";
		cin >> N;
		if (N < 4) {
			cout << "\nEnter value of N greater than 3." << endl;
		}
	} while (N < 4);
	
	int* currentQueenStates = new int[N];
	int* tempQueens = new int[N];
	int* addValues = new int[N];
	int* subtractValues = new int[N];
	
	cout << "\nInteger number shows counting of random restart of hill climbing.\n";

	while (generateRandomState) {
		count++;
		cout << count << "\t";

		for (col = 0; col < N; col++) {
			currentQueenStates[col] = rand() % N; // placing queens in random places
			addValues[col] = currentQueenStates[col] + col;
			subtractValues[col] = currentQueenStates[col] - col;
		}
		findConflicts(currentQueenStates, addValues, subtractValues, currentConflicts, N); //update currentConflicts value to be used later in while loop

		for (i = 0; i < N; i++) {
			tempQueens[i] = currentQueenStates[i];
			addValues[i] = tempQueens[i] + i;
			subtractValues[i] = tempQueens[i] - i;
		}

		while (currentConflicts > 0) { // tries all possible successors N*(N-1) untill cost(h) or conflicts is zero
			newState = false; //to find another successor state with low h

			for (col = 0; col < N; col++) {
				for (row = 0; row < N; row++) {

					if (currentQueenStates[col] != row) { //choose row other than current
						tempQueens[col] = row; //choose new or next row for the column
						addValues[col] = tempQueens[col] + col;
						subtractValues[col] = tempQueens[col] - col;
						findConflicts(tempQueens, addValues, subtractValues, tempConflicts, N);

						if (tempConflicts < currentConflicts) {	// here sideways moves are set to false and first-choice climb
							//	for (i = 0; i < N; i++) {
							//	currentQueenStates[i] = tempQueens[i];
							//}
							currentQueenStates[col] = row; //assign new row value
							newState = true;
							break;
						}
						else {
							tempQueens[col] = currentQueenStates[col]; //revert back to current states ro value
							addValues[col] = tempQueens[col] + col;
							subtractValues[col] = tempQueens[col] - col;
						}
					}
				} // --- inner for loop
				if (newState)
					break;
			} // --- outer for loop

			if (!newState) {// since cannot break from inner and outer loop with one break statement
				//count++;
				//cout << count << "\t";
				//cout << "Stuck in Local minimum(for cost). Every move of a single queen increases conflicts.\n"
				//	<< "State space with local minimum is given below:" << endl;
				break; // skip infinite loop
			}
			findConflicts(currentQueenStates, addValues, subtractValues, currentConflicts, N);
		} // --- inner while looop

		if (currentConflicts == 0)
			generateRandomState = false;

	} // --- outer while loop
	
	int* queenPositions = new int[N];
	for (col = 0; col < N; col++) {
		queenPositions[currentQueenStates[col]] = col; // setting column value corresponding to queen's position for each row
	}												// random row value comes according to value of currentQueenStates[col]
	
	cout << "\n\n'+' is Queen's position and '-' is empty position." << endl<<endl;

	for (row = 0; row < N; row++) {
		cout << " ";
		for (col = 0; col < queenPositions[row]; col++) {
			cout << "-";
		}
		cout << "+";
		for (col = queenPositions[row]+1; col < N; col++) {
			cout << "-";
		}
		cout << endl;
	}
	
	cout << endl;
	system("pause");
	delete[] currentQueenStates;
	delete[] tempQueens;
	delete[] addValues;
	delete[] subtractValues;
	delete[] queenPositions;
	return 0;
}