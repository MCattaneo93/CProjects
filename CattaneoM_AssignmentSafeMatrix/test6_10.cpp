/*
 * main.cpp
 *
 *  Created on: Dec 16, 2020
 *      Author: mcatt
 */
#include <iostream>
#include <cstdlib>
#include <stdio.h>


using namespace std;

template<typename T>
class safeArray {
private:
	int low, high;
	int size;
	T *values;
public:
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
			cout << endl << "Attempting to access index out of scope" << endl
					<< endl;
			exit(-1);
		} else {
			return values[index - low];
		}

	}

	~safeArray() {
		delete[] values;
	}
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
private:
	int lowR, lowC, highR, highC;
	int numrows, numcols;
	safeArray<T> *values;
public:
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
		highR = numR;
		highC = numC;
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
		if(index < lowR || index > highR){
			cout << "Attempting to access index out of scope..." << endl << endl;
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

int main() {

	//NOTE:
	//m is an arbitrary letter used to signify a safe matrix SM
	//mrlow = lowest indexed row of matrix m
	//mrhigh = highest indexed row of matrix m
	//mclow = lowest indexed column of matrix m
	//mchigh = highest indexed column of matrix m
	//so mrhigh - mrlow + 1 is the NUMBER OF ROWS in matrix m
	//while the LENGTH of a row would actually be mchigh - mclow + 1
	//These are generally used when the matrix is constructed with 4 inputs

	//mnumr is the number of rows in a matrix main
	//mnumc is the number of columns in a matric m
	//These are generally used when the matrix is constructed with 2 inputs


/*
 Test 6
 Testing 4 input constructor with bad (invalid bounds) input
 */
cout<<endl<<"-----TEST 6 : bad 4-input constructor input-----"<<endl;
int nrlow = 4;
int nrhigh = 0;
int nclow = 8;
int nchigh = 10;
cout<<"Now to construct safeMatrix n with invalid bounds(should not work):"<<endl;
safeMatrix<int> n(nrlow, nrhigh, nclow, nchigh);

/*
 Test 7
 Testing 2 input constructor with bad (invalid bounds) input
 */
cout<<endl<<"-----TEST 7 : bad 2-input constructor input-----"<<endl;
int pnumr = -2;
int pnumc = 4;
cout<<"Now to construct safeMatrix p with invalid bounds(should not work):"<<endl;
safeMatrix<int> p(pnumr, pnumc);

/*
 Test 8
 Testing row bounds checking for matrix construted with 4 input constructor
 */
cout<<endl<<"-----TEST 8 : Tessting row bounds  checking for 4 input matrix q-----"<<endl;
int qrlow = 2;
int qrhigh = 4;
int qclow = 5;
int qchigh = 6;
safeMatrix<int> q(qrlow, qrhigh, qclow, qchigh);
cout<<"Now we will assign a number to a place out of the row bounds of the matrix:"<<endl;
q[qrhigh + 1][qclow] = 10;

/*
 Test 9
 Testing column bounds checking for matrix construted with 4 input constructor
 */
cout<<endl<<"-----TEST 9 : Tessting column bounds  checking for 4 input matrix s-----"<<endl;
int srlow = 2;
int srhigh = 4;
int sclow = 5;
int schigh = 6;
safeMatrix<int> s(srlow, srhigh, sclow, schigh);
cout<<"Now we will assign a number to a place out of the row bounds of the matrix:"<<endl;
s[srhigh][sclow - 1] = 10;

/*
 Test 10
 Testing row bounds checking for matrix construted with 2 input constructor
 */
cout<<endl<<"-----TEST 10 : Tessting row bounds  checking for 2 input matrix t-----"<<endl;
int tnumr = 3;
int tnumc = 4;
safeMatrix<int> t(tnumr, tnumc);
cout<<"Now we will assign a number to a place out of the row bounds of the matrix:"<<endl;
t[tnumr][0];

return 0;

}
