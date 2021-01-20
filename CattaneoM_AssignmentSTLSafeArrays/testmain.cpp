/*
 * main.cpp
 *
 *  Created on: Dec 13, 2020
 *      Author: mcatt
 */

#include <iostream>
#include <memory>
#include <cstdlib>
#include <stdio.h>
#include <climits>
#include <algorithm>

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
	class iterator {

	public:
		typedef T value_type;
		typedef std::random_access_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;
		typedef T *pointer;
		typedef T &reference;
		friend class safeArray;
		iterator() :
				values(nullptr) {
			;
		}
		iterator(T *sa) :
				values(sa) {
			;
		}

		iterator(const iterator &it) :
				values(it.values) {
			;
		}

		T& operator*() const {
			return *values;
		}
		T* operator->() const {
			return values;
		}

		T& operator[](difference_type &val) const {
			return values[val];
		}

		iterator operator++() {
			++values;
			return *this;
		}

		iterator operator++(int val) const {
			iterator temp(this);
			++values;
			return temp;
		}

		iterator operator--() {
			--values;
			return *this;
		}
		iterator operator--(int val) const {
			iterator temp(this);
			++values;
			return temp;
		}

		iterator operator+(const iterator &it) {

			return iterator(values + it.values);
		}

		difference_type operator-(const iterator &it) const {
			return (values - it.values);
		}


		iterator operator+(difference_type size) {
			return iterator(values + size);
		}

		iterator operator-(difference_type size) {
			return iterator(values + size);
		}

		bool operator==(const iterator &it) const{
			return (values == it.values);
		}
		bool operator!=(const iterator &it) const{
			return !(values == it.values);
		}
		bool operator<(const iterator &it) const{
			return (values < it.values);
		}
		bool operator<=(const iterator &it) const{
			return (values <= it.values);
		}
		bool operator>(const iterator &it) const{
			return (values > it.values);
		}
		bool operator>=(const iterator &it) const{
			return (values >= it.values);
		}

	protected:
		T *values;

	};
	iterator begin() {
		return iterator(&values[0]);
	}
	iterator end() {
		return iterator(&values[size]);
	}

	template<typename Z>
	friend ostream& operator<<(ostream &os, const safeArray<Z> &sa);

}
;

template<class T>
ostream& operator<<(ostream &os, const safeArray<T> &sa) {

	for (int i = 0; i < sa.size; i++) {
		cout << sa.values[i] << " ";
	}

	cout << endl;

	return os;
}
;

int main() {

	safeArray<int> sa(51, 100);
	for (int i = 51; i < 100; i++) {
		sa[i] = rand() % 100 + 50;
	}

	for (int i = 51; i <= 100; i++) {
		cout << sa[i] << " ";
		if (i % 10 == 0) {
			cout << endl;
		}
	}

	cout << endl;
	auto it = sa.begin();
	auto result = sa.begin();
	for (int i = 0; i < 10; i++) {
		int random = rand() % 100 + 50;
		result = std::find(sa.begin(), sa.end(), random);
		if (result != sa.end()) {
			cout << "Found: " << random << "!!!" << endl;
		} else {
			cout << "Did not find: " << random << "!!!" << endl;
		}
	}

	std::sort(sa.begin(), sa.end());
	cout << endl << "Sorted Array: " << endl;
	for (int i = 51; i <= 100; i++) {
		cout << sa[i] << " ";
		if (i % 10 == 0) {
			cout << endl;
		}

	}

	cout << endl << "The safeArray is sorted: " << is_sorted(sa.begin(), sa.end());

}

