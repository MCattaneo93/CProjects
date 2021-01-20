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
#include <map>
#include <iterator>
using namespace std;

class Polynomial {
public:

	int size;

	Polynomial(ifstream &inFile, ofstream &outFile, int counter) {
		size = counter;

		int coefficient;
		int exponent;

		istringstream ss;
		istringstream ss1;
		ss.clear();
		ss1.clear();
		int pair = 0;

		map<int, int> result1;
		map<int, int> result2;
		//vector<map<int, int>> polynomials(2);
		string s;
		string s1;
		for (; getline(inFile, s); pair++) {
			getline(inFile, s1);
			//polynomials.clear();
			ss.str("");
			ss.clear();
			ss.str(s);

			ss1.str("");
			ss1.clear();
			ss1.str(s1);

			result1.clear();
			result2.clear();

			outFile << "initial input" << endl;

			while (ss >> coefficient) {

				ss >> exponent;
				outFile << coefficient << " " << exponent << " ";
				if (coefficient == 0) {
					continue;
				}
				std::map<int, int>::iterator it;
				it = result1.map::find(exponent);
				if (it != result1.end()) {
					it->second += coefficient;
				} else {
					//temp.map::insert( { exponent, coefficient });
					result1.map::insert( { exponent, coefficient });
				}

			}
			outFile << endl;
			while (ss1 >> coefficient) {

				ss1 >> exponent;
				outFile << coefficient << " " << exponent << " ";
				if (coefficient == 0) {
					continue;
				}
				std::map<int, int>::iterator it;
				it = result2.map::find(exponent);
				if (it != result2.end()) {
					it->second += coefficient;
				} else {
					//temp.map::insert( { exponent, coefficient });
					result2.map::insert( { exponent, coefficient });
				}

			}
			outFile << endl;

			std::map<int, int>::reverse_iterator myit;

			outFile << endl << "Canonincal Print1: ";
			printResult(result1, outFile);
			outFile << endl << "Canonincal Print2: ";
			printResult(result2, outFile);
			polyAdd(result1, result2, outFile);
			polySub(result1, result2, outFile);
			polyMulti(result1, result2, outFile);
			outFile << endl << endl;

		}

	}

	void polyAdd(map<int, int> &operand1, map<int, int> &operand2,
			ofstream &outFile) {

		std::map<int, int>::reverse_iterator it1;
		std::map<int, int>::reverse_iterator it2;
		map<int, int> temp;
		for (it1 = operand1.rbegin(), it2 = operand2.rbegin();
				it1 != operand1.rend() && it2 != operand2.rend();) {


			if (it1->first > it2->first) {

				temp.map::insert( { it1->first, it1->second });
				it1++;
			} else if (it1->first < it2->first) {

				temp.map::insert( { it2->first, it2->second });
				it2++;
			} else {
				if (it1->second + it2->second == 0) {
					it1++;
					it2++;

					continue;
				} else {
					temp.map::insert(
							{ it1->first, it1->second + it2->second });

					it1++;
					it2++;
				}

			}

		}

		for (; it1 != operand1.rend(); it1++) {
			temp.map::insert( { it1->first, it1->second });


		}
		it1 = temp.rbegin();

		for (; it1 != temp.rend(); it1++) {
			//cout << it1->first << " " << it1->second << " ";
		}

		for (; it2 != operand2.rend(); it2++) {
			temp.map::insert( { it2->first, it2->second });


		}

		outFile << endl << "Add Result: ";

		//result.map::insert(temp.begin(), temp.end());
		printResult(temp, outFile);
	}

	void polySub(map<int, int> &operand1, map<int, int> &operand2,
			ofstream &outFile) {

		std::map<int, int>::reverse_iterator it1;
		std::map<int, int>::reverse_iterator it2;
		map<int, int> temp;
		for (it1 = operand1.rbegin(), it2 = operand2.rbegin();
				it1 != operand1.rend() && it2 != operand2.rend();) {


			if (it1->first > it2->first) {

				temp.map::insert( { it1->first, it1->second });
				it1++;
			} else if (it1->first < it2->first) {

				temp.map::insert( { it2->first, it2->second });
				it2++;
			} else {
				if (it1->second + it2->second == 0) {
					it1++;
					it2++;

					continue;
				} else {
					temp.map::insert(
							{ it1->first, it1->second - it2->second });

					it1++;
					it2++;
				}

			}

		}

		for (; it1 != operand1.rend(); it1++) {
			temp.map::insert( { it1->first, it1->second });


		}
		it1 = temp.rbegin();

		for (; it1 != temp.rend(); it1++) {
			//cout << it1->first << " " << it1->second << " ";
		}

		for (; it2 != operand2.rend(); it2++) {
			temp.map::insert( { it2->first, (it2->second) * -1 });


		}

		outFile << endl << "Sub Result: ";

		//result.map::insert(temp.begin(), temp.end());
		printResult(temp, outFile);
	}

	void polyMulti(map<int, int> &operand1, map<int, int> &operand2,
			ofstream &outFile) {

		std::map<int, int>::reverse_iterator it1;
		std::map<int, int>::reverse_iterator it2;
		map<int, int> result;
		for (it1 = operand1.rbegin(); it1 != operand1.rend(); it1++) {
			for(it2 = operand2.rbegin(); it2 != operand2.rend(); it2++){
				int exponent = it1->first + it2 -> first;
				int coefficient = it1 ->second * it2 ->second;
				if (coefficient == 0) {
					continue;
				}
				std::map<int, int>::iterator it;
				it = result.map::find(exponent);
				if (it != result.end()) {
					it->second += coefficient;
				} else {
					//temp.map::insert( { exponent, coefficient });
					result.map::insert( { exponent, coefficient });
				}
			}

		}



		outFile << endl << "Multi Result: ";

		//result.map::insert(temp.begin(), temp.end());
		printResult(result, outFile);
	}

	void printResult(map<int, int> &result, ofstream &outFile) {
		bool print_zero = true;
		std::map<int, int>::reverse_iterator it;
		int counter = 0;
		for (it = result.rbegin(); it != result.rend(); ++it, counter++) {
			if(it->second == 0){
				continue;
			}else{
				outFile << (counter == 0 || it->second < 0 ? "" : "+")
													<< it->second;
				if (it->first != 0) {
					outFile << "x^" << it->first;
				}
				print_zero = false;
			}

		}
		if(print_zero){
			outFile << '0';
		}

	}
	/*
	 void printResult(int index, ofstream &outFile) {

	 std::map<int, int>::iterator it;
	 int counter = 0;
	 for (it = (*polynomials)[index].begin(); it != (*polynomials)[index].end(); ++it, counter++) {

	 outFile << (counter == 0 || it->second < 0 ? "" : "+")
	 << it->second;
	 if (it->first != 0) {
	 outFile << "x^" << it->first;
	 }
	 }
	 outFile << endl;
	 }

	 ~Polynomial() {
	 delete polynomials;
	 }
	 */
};

int main(int argc, char *argv[]) {

	ifstream inFile;
	ofstream outFile;

	inFile.open("input.txt");
	outFile.open("output.txt");

	string temp;
	int counter;

	while (getline(inFile, temp)) {
		counter++;

	}

	inFile.close();
	inFile.open("input.txt");
	//outFile << "Polynomials(Non-Canonical Form)\n";
	Polynomial poly(inFile, outFile, counter);
	//poly.cannonicalPrint(outFile);

	inFile.close();
	outFile.close();

	return 0;

}
