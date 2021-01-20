/*
 * main.cpp
 *
 *  Created on: Dec 10, 2020
 *      Author: mcatt
 */

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <climits>
#include "safeAM.cpp"

class VNT {
public:
	safeMatrix<int> *sm;
	int m, n;

	VNT() {
		m = n = 0;
		sm = nullptr;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				(*sm)[i][j] = INT_MAX;
			}
		}
	}

	VNT(int m1, int n1) {

		m = m1;
		n = n1;

		sm = new safeMatrix<int>(m, n);

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				(*sm)[i][j] = INT_MAX;
			}
		}

	}

	void add(int val) {
		if (isFull()) {
			cout << "Table is full...";
			return;
		}
		if (isEmpty()) {
			(*sm)[0][0] = val;
			return;
		}
		int row = m - 1;
		int col = n - 1;

		int top_val;
		int left_val;
		(*sm)[m - 1][n - 1] = val;


		while (true) {
			bool valid_top = false;
			bool valid_left = false;
			if (row - 1 >= 0 && col >= 0) {

				top_val = (*sm)[row - 1][col];
				//cout << "first if statement" << endl << endl;
				valid_top = true;
			}

			if (row >= 0 && col - 1>= 0) {

				left_val = (*sm)[row][col - 1];
				//cout << "first if statement" << endl << endl;
				valid_left = true;
			}

			//cout << "BOOL EXPR 1: " << ( (left_val > val) && valid_left && (left_val > top_val)) << endl << "BOOL EXPR 2: " << (!(valid_top) && ((left_val == INT_MAX) && valid_left)) << endl << endl;
			if (( (left_val > val) && valid_left && (left_val > top_val))
					|| (!(valid_top) && ((left_val > val) && valid_left)) ) {
				/*
				cout << "Called first swap: " << val << " Valid_TOP: " << valid_top << " Row: "
						<< row << " Col: " << col << " Bool Expr: "
						<< (left_val > val && valid_left && left_val > top_val)
						<< " Top_Val: " << top_val << " Valid_Left: " << valid_left <<" Left_Val: " << left_val << endl << endl;
				 */
				swap(row, col, row, col - 1);
				//cout << "First swap successful: " << left_val << " " << val << endl << endl;
				col--;
			} else if ( (top_val > val) && valid_top) {
				/*
				cout << "Called second swap: " << val << " Valid_TOP: " << valid_top << " Row: "
						<< row << " Col: " << col << " Bool Expr: "
						<< (left_val > val && valid_left && left_val > top_val)
						<< " Top_Val: " << top_val << " Valid_Left: " << valid_left <<" Left_Val: " << left_val << endl << endl;
				 */
				swap(row, col, row - 1, col);
				//cout << "Second swap successful: "<< top_val << " " << val << endl << endl;
				row--;
			} else {
				break;
			}
		}

	}

	void swap(int row, int col, int row1, int col1) {
		int temp = (*sm)[row1][col1];
		(*sm)[row1][col1] = (*sm)[row][col];
		(*sm)[row][col] = temp;
	}

	bool isEmpty() {
		return ((*sm)[0][0] == INT_MAX);
	}

	bool isFull() {
		return ((*sm)[m - 1][n - 1] < INT_MAX);
	}
	int getMin() {
		if (isEmpty()) {
			return INT_MAX;
		}
		VNT temp(m, n);
		int min = (*sm)[0][0];

		(*sm)[0][0] = INT_MAX;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				temp.add((*sm)[i][j]);
			}
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				(*sm)[i][j] = (*temp.sm)[i][j];
			}
		}

		/*
		int row = 0;
		int col = 0;
		int right_val;
		int down_val;
		int val;
		while(row < m && col < n){
			bool valid_right = false;
			bool valid_down = false;
			val = (*sm)[row][col];
			if(row + 1 < m && col < n){
				valid_down = true;
				down_val = (*sm)[row+1][col];
			}
			if(row < m && col + 1 < n){
				valid_right = true;
				right_val = (*sm)[row][col+1];
			}

			if(valid_down && down_val <= val && (valid_right && right_val >= val) ){
				swap(row, col, row + 1, col);
				row++;
			}else if(valid_right && right_val <= val && (valid_down && down_val >= val)){
				swap(row, col, row, col+ 1);
				col++;
			}else{
				break;
			}

		}
*/
		return min;

	}

	int getMax() {
		if (isEmpty()) {
			return (*sm)[0][0];
		}

		int row = 0;
		int col = n - 1;
		int max = INT_MAX;
		while (row < m && col > -1) {

			if(max != INT_MAX){
				break;
			}
			else if ((*sm)[row][col] == INT_MAX) {
				//cout << "Col: " << col;
				col--;
			} else {
				max = (*sm)[row][col];
				row++;

			}
		}
		(*sm)[row][col] = INT_MAX;
		return max;

	}

	bool find(int searchTerm) {
		bool found = false;
		int row = 0;
		int col = n - 1;
		int val;
		for (; (row < m || col > 0) && !found;) {

			val = (*sm)[row][col];
			//cout << "BOOL EXPR 1: " << (val != INT_MAX) << " BOOL EXPR 2: " << (val > searchTerm) << endl << endl;
			if (val == searchTerm) {

				found = true;
				break;
			} else if ((val != INT_MAX) && (val < searchTerm)) {

				if (row < m) {

					row++;
				} else {
					break;
				}

			} else {

				if (col > 0) {
					col--;
				} else {
					break;
				}

			}
		}

		return found;
	}

	void printOutVNT() {
		cout << *sm;
	}

	~VNT() {
		delete sm;
	}

};

ostream& operator <<(ostream &os, const VNT &vnt) {
	os << (*vnt.sm) << endl;
	return os;
}
;

bool static sort(int* k[], int size) {
	VNT myvnt(size, size);
	for (int i = 0; i < size; i++) {
		myvnt.add( (*k)[i]);
	}
	for (int i = 0; i < size; i++) {
		(*k)[i] = myvnt.getMin();
	}
	return true;
}
;

int main() {

	VNT a(5, 6);

	int addedNumber = 0;
	for (int i = 0; i <= 15; i++) {
		addedNumber = (i * 31) % 50;
		a.add(addedNumber);
		cout << addedNumber << endl;

	}

	//a.printOutVNT();

	cout << endl << "After adding all items: " << endl << a << endl << endl;

	a.getMin();
	cout << "After calling getMin: " << endl << a << endl << endl;
	a.getMax();

	cout << "After getMax: " << endl << a << endl << endl;

	//a.printOutVNT();

	int firstSearched = 100;
	int secondSearched = 0;
	int thirdSearched = 31;

	cout << firstSearched << " is in VNT is: " << a.find(firstSearched) << endl;
	cout << secondSearched << " is in VNT is: " << a.find(secondSearched)
							<< endl;
	cout << thirdSearched << " is in VNT is: " << a.find(thirdSearched) << endl;

	firstSearched = 15;
	secondSearched = 34;
	thirdSearched = 24;

	cout << firstSearched << " is in VNT is: " << a.find(firstSearched) << endl;
	cout << secondSearched << " is in VNT is: " << a.find(secondSearched)
									<< endl;
	cout << thirdSearched << " is in VNT is: " << a.find(thirdSearched) << endl;

	int arraySize = 50;
	int *k = new int[arraySize];
	cout << "The array initially is:" << endl;
	for (int i = 0; i < arraySize; i++) {
		addedNumber = (i * 31) % 50;
		k[i] = addedNumber;
		cout << addedNumber << " ";
	}
	cout << endl << endl;

	sort(&k, arraySize);

	cout << "The array, now sorted by VNT, is:" << endl;
	for (int i = 0; i < arraySize; i++) {
		cout << k[i] << " ";
	}
	cout << endl;

	return 0;

}


