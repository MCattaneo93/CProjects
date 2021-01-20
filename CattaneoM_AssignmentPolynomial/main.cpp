/*
 * main.cpp
 *
 *  Created on: Oct 8, 2020
 *      Author: mcatt
 */

#include <iostream>

#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>

using namespace std;

class Polynomial {
public:

	vector<int> *polynomials;

	int size;

	Polynomial(ifstream &inFile, ofstream &outFile, int counter) {
		size = counter;

		polynomials = new vector<int> [size];

		for (int i = 0; i < size; i++) {
			polynomials[i].reserve(1000);
		}

		int index = 0;
		int coefficient;
		int exponent;

		istringstream ss;
		for (string s; getline(inFile, s);) {
			vector<int> result (vector<int>(1000000));
			ss.str("");
			ss.clear();
			ss.str(s);
			while (ss >> coefficient) {
				result.push_back(coefficient);
				ss >> exponent;
				result.push_back(exponent);
				sortAdd(coefficient, exponent, index);

			}
			printResult(result, outFile);
			index++;
		}

	}

	void sortAdd(int coefficient, int exponent, int index) {
		bool swap = false;
		vector<int>::iterator it = polynomials[index].begin() + 1;
		for (int i = 1; i < polynomials[index].size() && !swap;
				i += 2, it += 2) {
			if (exponent == polynomials[index][i]) {
				polynomials[index][i - 1] += coefficient;
				swap = true;
			}
			if (exponent > polynomials[index][i]) {

				polynomials[index].insert(it - 1, exponent);
				polynomials[index].insert(it - 1, coefficient);
				swap = true;
			}
		}

		if (!swap) {
			polynomials[index].push_back(coefficient);
			polynomials[index].push_back(exponent);
		}

	}
	void cannonicalPrint(ofstream &outFile) {
		outFile << "\nPolynomials in Canonical form \n";
		int coefficient;
		int exponent;
		for (int i = 0; i < size; i++) {

			for (int j = 0; j < polynomials[i].size(); j += 2) {
				coefficient = polynomials[i][j];
				exponent = polynomials[i][j + 1];
				bool negative;
				(coefficient < 0 ? negative = true : negative = false);
				if (!negative) {
					if (j != 0) {
						if (exponent == 0) {
							outFile << '+' << coefficient;
						} else {
							outFile << '+' << coefficient << "x^" << exponent;
						}

					} else {
						if (exponent == 0) {
							outFile << coefficient;
						} else {
							outFile << coefficient << "x^" << exponent;
						}

					}

				} else {
					if (exponent == 0) {
						outFile << coefficient;
					} else {
						outFile << coefficient << "x^" << exponent;
					}
				}
			}
			outFile << '\n';
		}
	}

	void addPolynomials(ofstream &outFile) {
		for (int i = 0; i < size; i += 2) {
			int polyIndex1 = 1;
			int polyIndex2 = 1;
			vector<int> result(
					polynomials[i].size() + polynomials[i + 1].size());
			while (polyIndex1 < polynomials[i].size()
					|| polyIndex2 < polynomials[i + 1].size()) {
				if (polynomials[i][polyIndex1]
						> polynomials[i + 1][polyIndex2]) {
					result.push_back(polynomials[i][polyIndex1]);
					result.push_back(polynomials[i][polyIndex1 - 1]);
					polyIndex1 += 2;
				} else if (polynomials[i + 1][polyIndex2]
						> polynomials[i][polyIndex1]) {
					result.push_back(polynomials[i + 1][polyIndex2]);
					result.push_back(polynomials[i + 1][polyIndex2 - 1]);
					polyIndex2 += 2;
				} else {
					result.push_back(polynomials[i][polyIndex1]);
					result.push_back(
							polynomials[i][polyIndex1 - 1]
									+ polynomials[i + 1][polyIndex2 - 1]);
					polyIndex1 += 2;
					polyIndex2 += 2;
				}
			}

			while (polyIndex1 < polynomials[i].size()) {
				result.push_back(polynomials[i][polyIndex1]);
				result.push_back(polynomials[i][polyIndex1 - 1]);
				polyIndex1 += 2;
			}

			while (polyIndex2 < polynomials[i + 1].size()) {
				result.push_back(polynomials[i + 1][polyIndex2]);
				result.push_back(polynomials[i + 1][polyIndex2 - 1]);
				polyIndex2 += 2;
			}
			printResult(result, outFile);
		}

	}

	void subtractPolynomials(ofstream &outFile) {
		for (int i = 0; i < size; i += 2) {
			int polyIndex1 = 1;
			int polyIndex2 = 1;
			vector<int> result(
					polynomials[i].size() + polynomials[i + 1].size());
			while (polyIndex1 < polynomials[i].size()
					|| polyIndex2 < polynomials[i + 1].size()) {
				if (polynomials[i][polyIndex1]
						> polynomials[i + 1][polyIndex2]) {
					result.push_back(polynomials[i][polyIndex1]);
					result.push_back(polynomials[i][polyIndex1 - 1]);
					polyIndex1 += 2;
				} else if (polynomials[i + 1][polyIndex2]
						> polynomials[i][polyIndex1]) {
					result.push_back(polynomials[i + 1][polyIndex2]);
					result.push_back(0 - polynomials[i + 1][polyIndex2 - 1]);
					polyIndex2 += 2;
				} else {
					result.push_back(polynomials[i][polyIndex1]);
					result.push_back(
							polynomials[i][polyIndex1 - 1]
									- polynomials[i + 1][polyIndex2 - 1]);
					polyIndex1 += 2;
					polyIndex2 += 2;
				}
			}

			while (polyIndex1 < polynomials[i].size()) {
				result.push_back(polynomials[i][polyIndex1]);
				result.push_back(polynomials[i][polyIndex1 - 1]);
				polyIndex1 += 2;
			}

			while (polyIndex2 < polynomials[i + 1].size()) {
				result.push_back(polynomials[i + 1][polyIndex2]);
				result.push_back(polynomials[i + 1][polyIndex2 - 1]);
				polyIndex2 += 2;
			}
			printResult(result, outFile);
		}

	}

	void multiAdd(vector<int> &result, int coefficient, int exponent) {

		bool swap = false;

		for (int i = 0; i < result.size() && !swap; i += 2) {

			if (exponent == result[i]) {
				result[i + 1] += coefficient;
				swap = true;
			}
		}

		if (!swap) {
			result.push_back(exponent);
			result.push_back(coefficient);
		}

	}

	void multiplyPolynomials(ofstream &outFile) {

		for (int i = 0; i < size; i += 2) {
			int polyIndex1 = 1;
			int polyIndex2 = 1;
			vector<int> result(
					polynomials[i].size() + polynomials[i + 1].size());
			for (; polyIndex1 < polynomials[i].size(); polyIndex1 += 2) {
				polyIndex2 = 1;

				for (; polyIndex2 < polynomials[i + 1].size(); polyIndex2 +=
						2) {
					int coefficient = polynomials[i][polyIndex1 - 1]
							* polynomials[i + 1][polyIndex2 - 1];
					int exponent = polynomials[i][polyIndex1]
							+ polynomials[i + 1][polyIndex2];

						multiAdd(result, coefficient, exponent);

				}

			}

			printResult(result, outFile);
		}

	}

	void printResult(vector<int> result, ofstream &outFile) {
		int exponent;
		int coefficient;
		int i = 0;
		while (result[i + 1] == 0) {
			i += 2;
		}
		for (int j = 0; i < result.size(); i += 2, j++) {
			coefficient = result[i + 1];
			if (coefficient == 0) {
				continue;
			}

			exponent = result[i];

			outFile << (coefficient < 0 || j == 0 ? "" : "+") << coefficient;

			if (exponent != 0) {
				outFile << "x^" << exponent;
			}
		}
		outFile << '\n';
	}

	~Polynomial() {
		delete[] polynomials;
	}

};

int main(int argc, char *argv[]) {

	ifstream inFile;
	ofstream outFile;

	inFile.open(argv[1]);
	outFile.open("output.txt");

	string temp;
	int counter;

	while (getline(inFile, temp)) {
		counter++;
	}

	inFile.close();
	inFile.open(argv[1]);
	outFile << "Polynomials(Non-Canonical Form)\n";
	Polynomial poly(inFile, outFile, counter);
	poly.cannonicalPrint(outFile);

	outFile << "\nResult of Addition\n";
	poly.addPolynomials(outFile);

	outFile << "\nResult of Subtraction\n";
	poly.subtractPolynomials(outFile);

	outFile << "\nResult of Multiplication\n";
	poly.multiplyPolynomials(outFile);

	inFile.close();
	outFile.close();

	return 0;

}
