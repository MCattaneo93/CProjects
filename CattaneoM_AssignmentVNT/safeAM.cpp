/*
 * safeAM.cpp
 *
 *  Created on: Dec 10, 2020
 *      Author: mcatt
 */




#include <iostream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

template<typename T>
class safeArray {
public:
	int low, high;
	int size;
	T *values;

	safeArray() {
		low = 0;
		high = 0;
		size = 0;
		values = nullptr;
	}

	safeArray(int upper) {
		high = upper - 1;
		low = 0;
		size = high - low + 1;
		values = new T[size];
		for (int i = 0; i < size; i++) {
			values[i] = 0;
		}
	}

	safeArray(int lower, int upper) {
		low = lower;
		high = upper;
		size = high - low + 1;
		values = new T[size];
		for (int i = 0; i < size; i++) {
			values[i] = 0;
		}
	}

	safeArray(const safeArray<T> &sa) {

		size = sa.size;
		low = sa.low;
		high = sa.high;
		values = new T[size];
		for (int i = 0; i < size; i++) {
			values[i] = sa.values[i];
		}

	}

	safeArray& operator=(const safeArray<T> &sa) {
		if (this == &sa) {
			return *this;
		}
		if (values != nullptr) {
			delete[] values;
		}

		size = sa.size;
		low = sa.low;
		high = sa.high;
		values = new T[size];
		for (int i = 0; i < size; i++) {
			values[i] = sa.values[i];
		}

		return *this;

	}

	T& operator[](int index) {
		if (index < low || index > high) {

			cout << endl << "Array: Attempting to access index out of scope: " <<index  << endl
					<< endl;
			exit(-1);
		} else {
			return values[index - low];
		}

	}

	~safeArray() {
		delete[] values;
	}
	friend class VNT;
	template<typename Z>
	friend ostream& operator<<(ostream &os, const safeArray<Z> &sa);

};

template<class T>
ostream& operator<<(ostream &os, const safeArray<T> &sa) {

	for (int i = 0; i < sa.size; i++) {
		cout << sa.values[i] << " ";
	}

	cout << endl;

	return os;
}
;

template<typename T>
class safeMatrix {
public:
	int lowR, lowC, highR, highC;
	int numrows, numcols;
	safeArray<T> *values;

	safeMatrix() {
		lowR = 0;
		lowC = 0;
		highR = -1;
		highC = -1;
		numrows = numcols = 0;
		values = nullptr;
	}

	safeMatrix(int lowerx, int upperx, int lowery, int uppery) {
		if (lowerx > upperx || lowery > uppery) {
			cout << "Bounds are incorrect, please double check";
			exit(-1);
		}
		lowR = lowerx;
		lowC = lowery;
		highR = upperx;
		highC = uppery;
		numrows = highR - lowR + 1;
		numcols = highC - lowC + 1;

		values = new safeArray<T> [numrows];
		for (int i = 0; i < numrows; i++) {
			values[i] = safeArray<T>(lowC, highC);
		}
	}

	safeMatrix(int numR, int numC) {
		if (numR < 0 || numC < 0) {
			cout
					<< "One of the numbers provided is negative, please double check..."
					<< endl << endl;
			exit(-1);
		}
		numrows = numR;
		numcols = numC;
		lowR = lowC = 0;
		highR = numR - 1;
		highC = numC - 1;
		values = new safeArray<T> [numrows];
		for (int i = 0; i < numrows; i++) {
			values[i] = safeArray<T>(lowC, highC);
		}
	}

	safeMatrix(const safeMatrix<T> &sm) {
		lowR = sm.lowR;
		lowC = sm.lowC;
		highR = sm.highR;
		highC = sm.highC;
		numrows = sm.numrows;
		numcols = sm.numcols;

		values = new safeArray<T> [numrows];
		for (int i = 0; i < numrows; i++) {
			values[i] = sm.values[i];
		}
	}

	safeMatrix<T>& operator=(safeMatrix<T> &sm) {
		if (this == &sm) {
			return *this;
		}
		if (values != nullptr) {
			delete[] values;
		}
		lowR = sm.lowR;
		lowC = sm.lowC;
		highR = sm.highR;
		highC = sm.highC;
		numrows = sm.numrows;
		numcols = sm.numcols;

		values = new safeArray<T> [numrows];
		for (int i = 0; i < numrows; i++) {
			values[i] = sm.values[i];
		}

		return *this;

	}

	safeArray<T>& operator[](int index) {
		if (index < lowR || index > highR) {

			cout << "Matrix: Attempting to access index out of scope: " << index  << endl
					<< endl;
			exit(-1);
		}
		return values[index - lowR];
	}

	safeMatrix<T> operator*(int operand) {
		safeMatrix<T> result(numrows, numcols);
		for (int i = 0; i < numrows; i++) {
			for (int j = 0; j < numcols; j++) {
				result[i][j] = values[i][j + lowC] * operand;
			}
		}

		return result;
	}

	safeMatrix<T> operator*(const safeMatrix<T> &sm) {
		if (numcols != sm.numrows) {
			cout << endl
					<< "Number of Matrix1 Columns != Number of Matrix2 Rows"
					<< endl << endl;
			exit(-1);
		}

		safeMatrix<T> result(numrows, sm.numcols);
		for (int i = 0; i < numrows; i++) {
			for (int j = 0; j < sm.numcols; j++) {
				for (int k = 0; k < numcols; k++) {
					result[i][j] += values[i][k + lowC]
							* sm.values[k][j + sm.lowC];
				}

			}
		}

		return result;
	}

	~safeMatrix() {
		delete[] values;
	}
	friend class VNT;
	template<typename Z>
	friend ostream& operator<<(ostream &os, const safeMatrix<Z> &sm);
};

template<typename T>
ostream& operator<<(ostream &os, const safeMatrix<T> &sm) {

	for (int i = 0; i < sm.numrows; i++) {

		cout << sm.values[i];
	}
	cout << endl;
	return os;
}
;
